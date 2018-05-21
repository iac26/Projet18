/**
 * \file 	main.cpp
 * \brief 	handle everything linked to glui and the control of the program
 * \authors	Lianyi Ni & Iacopo Sprenger
 * \version 1.2
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <GL/glui.h>

#define GLUI_POSX 900
#define GLUI_POSY 200
#define STRLEN 20



extern "C" {
	#include "read.h"
	#include "simulation.h"
	#include "graphic.h"
	#include "constantes.h"
}

enum{OPEN, SAVE, START, STEP, REC, CTRL, QUIT};

/**
 * \brief	quite the program
 **/
static void quit(void);

/**
 * \brief	open a file
 **/
static void open(void);

/**
 * \brief	save a file
 **/
static void save(void);

/**
 * \brief	start/stop the simulation
 **/
static void start(void);

/**
 * \brief	increment the simulation one step
 **/
static void step(void);

/**
 * \brief	start/stop recording
 **/
static void rec(void);

/**
 * \brief	handle the control mode selection
 **/
static void ctrl(void);

/**
 * \brief	control callback
 **/
static void control(unsigned short type);

/**
 * \brief	idle function
 **/
static void idle(void);

/**
 * \brief	draw the glui window
 **/
static void GUI(void);

/**
 * \brief	checks if the opened file is correct
 **/
static int check_file(char * filename);

/**
 * \brief	keyboard callback
 * \brief	key 	key indentifier
 * \brief	x		mouse x pos when key pressed
 * \brief	y		mouse y pos when key pressed
 **/
static void keys(unsigned char key, int x, int y);

/**
 * \brief	mouse callback
 * \param	button	button identifier
 * \param	state	state identifier
 * \param	x		mouse x pos when button pressed
 * \param	y		mouse y pos when button pressed
 **/
static void mouse(int button, int state, int x, int y);

/**
 * \brief	special keys callback
 * \brief	key 	key indentifier
 * \brief	x		mouse x pos when key pressed
 * \brief	y		mouse y pos when key pressed
 **/
static void special_keys(int key, int x, int y);

namespace {
	std::string o_filename;
	std::string s_filename;
	int g_window;
	GLUI * glui;
	char * start_stop;
	GLUI_Button * start_btn;
	int start_stop_v = 0;
	int record = 0;
	GLUI_Checkbox * rec_box;
	GLUI_StaticText * rate_text, * step_text, * trans_text, * rot_text;
	double rate_val = 0.0;
	unsigned int step_val = 0;
	int ctrl_mode = 0;
	FILE * f_rec = NULL;
}


int main(int argc, char ** argv){
	srand(time(NULL));
	if(argc > 2){
		if(!strcmp(argv[1],"Error")){
			if(check_file(argv[2])) {
				read_file_ok();
			}
			exit(0);
		} else if(!strcmp(argv[1],"Draw")){
			check_file(argv[2]);
		} else {
			printf("Usage: ./projet.x [Error|Draw] <Filename>\n");
			return EXIT_FAILURE;
		}
	} else if(argc > 1){
		printf("Usage: ./projet.x [Error|Draw] <Filename>\n");
		return EXIT_FAILURE;
	}
	g_window = graphic_init_glut(&argc, argv);
	GUI();
	glutMainLoop();
	return EXIT_SUCCESS;
}

static void GUI(void){
	GLUI_Master.set_glutReshapeFunc(graphic_reshape);  
	GLUI_Master.set_glutDisplayFunc(simulation_print_everything);  
	GLUI_Master.set_glutIdleFunc(idle);
	GLUI_Master.set_glutMouseFunc(mouse);
	GLUI_Master.set_glutSpecialFunc(special_keys);
	GLUI_Master.set_glutKeyboardFunc(keys);
	
	glui = GLUI_Master.create_glui("CONTROL", 0, GLUI_POSX, GLUI_POSY);
	
	GLUI_Panel * open_panel = new GLUI_Panel(glui, "Open");
	GLUI_EditText * open_box = new GLUI_EditText(open_panel, "File Name:", o_filename);
	open_box->set_text("D03.txt");
	new GLUI_Button(open_panel, "OPEN", OPEN, (GLUI_Update_CB)control);
	GLUI_Panel * save_panel = new GLUI_Panel(glui, "Save");
	new GLUI_EditText(save_panel, "File Name:", s_filename);
	new GLUI_Button(save_panel, "SAVE", SAVE, (GLUI_Update_CB)control);
	new GLUI_Column(glui, false);
	
	GLUI_Panel * sim_panel = new GLUI_Panel(glui, "Simulation");
	start_btn = new GLUI_Button(sim_panel, "START", START, (GLUI_Update_CB)control);
	new GLUI_Button(sim_panel, "STEP", STEP, (GLUI_Update_CB)control);
	GLUI_Panel * rec_panel = new GLUI_Panel(glui, "Record");
	rec_box = new GLUI_Checkbox(	rec_panel, "Record", &record, REC, 
								(GLUI_Update_CB)control);
	rate_text = new GLUI_StaticText(rec_panel, "Rate: 0.000");
	step_text = new GLUI_StaticText(rec_panel, "Step: 0");
	new GLUI_Column(glui, false);
	
	GLUI_Panel * control_panel = new GLUI_Panel(glui, "Control Mode");
	GLUI_RadioGroup * ctrl_r = new GLUI_RadioGroup(	control_panel, &ctrl_mode, CTRL, 
													(GLUI_Update_CB)control);
	new GLUI_RadioButton(ctrl_r, "Automatic");
	new GLUI_RadioButton(ctrl_r, "Manual"); 
	GLUI_Panel * r_control_panel = new GLUI_Panel(glui, "Robot Control");
	trans_text = new GLUI_StaticText(r_control_panel, "Translation: 0.000");
	rot_text = new GLUI_StaticText(r_control_panel, "Rotation:     0.000");
	new GLUI_Button(glui, "EXIT", QUIT, (GLUI_Update_CB)control);
 
	glui->set_main_gfx_window(g_window);
}

static void open(void){
	const char * fn = o_filename.c_str();
	#ifdef DEBUG
	printf("Open: %s\n", fn);
	#endif
	simulation_init();
	step_val = 0;
	start_stop_v = 0;
	start_btn->name = "START";
	check_file((char *) fn);
	glutPostRedisplay();
}

static int check_file(char * filename){
	if(!(read_file(filename) && simulation_initial_collisions())){
		simulation_init();
		return 0;
	}
	return 1;
}

static void save(void){
	const char * fn = s_filename.c_str();
	#ifdef DEBUG
	printf("Save: %s\n", fn);
	#endif
	read_save((char *) fn);
}

static void start(void){
	start_stop_v = !start_stop_v;
	if(start_stop_v){
		#ifdef DEBUG
		printf("start\n");
		#endif
		start_btn->name = "STOP";
	} else {
		#ifdef DEBUG
		printf("stop\n");
		#endif
		start_btn->name = "START";
		if(record) {
			fclose(f_rec);
			record = 0;
			rec_box->set_int_val(0);
		}
	}
}

static void step(void){
	if(!simulation_get_finished()) {
		step_val++;
		#ifdef DEBUG
		printf("step\n");
		#endif
		simulation_update();
		if(record) {
			fprintf(f_rec, "\t%d %1.5lf\n", step_val, rate_val);
		}
	} else {
		start_stop_v = 0;
		start_btn->name = "START";
		if(record) {
			fclose(f_rec);
			record = 0;
			rec_box->set_int_val(0);
		}
	}
}

static void rec(void){
	if(record) {
		#ifdef DEBUG
		printf("recording started\n");
		#endif
		f_rec = fopen("out.dat", "w");
		fprintf(f_rec, "# output file from the vacum cleaner simulator\n");
	} else {
		#ifdef DEBUG
		printf("recording stopped\n");
		#endif
		fclose(f_rec);
	}
}

static void ctrl(void){
	if(ctrl_mode) {
		#ifdef DEBUG
		printf("control mode set to manual\n");
		#endif
		simulation_set_manual_control();
	} else {
		#ifdef DEBUG
		printf("control mode set to automatic\n");
		#endif
		simulation_set_auto_control();
		simulation_reset_man();
	}
}

static void control(unsigned short type){
	switch (type) {
		case OPEN:
			open();
			break;
		case SAVE:
			save();
			break;
		case START:
			start();
			break;
		case STEP:
			step();
			break;
		case REC:
			rec();
			break;
		case CTRL:
			ctrl();
			break;
		case QUIT:
			quit();
			break;
	}
}

static void quit(void){
	printf("bye\n");
	glutDestroyWindow(g_window);
	exit(0);
}

static void idle(void){ 
	glutSetWindow(g_window);
	char str[STRLEN];
	rate_val = simulation_get_rate();
	sprintf(str, "rate: %1.3lf", rate_val);
	rate_text->set_text((const char *)str);
	sprintf(str, "step: %d", step_val);
	step_text->set_text((const char *)str);
	sprintf(str, "translation: %1.3lf", simulation_get_man_vtran());
	trans_text->set_text((const char *)str);
	sprintf(str, "rotation:    %1.3lf", simulation_get_man_vrot());
	rot_text->set_text((const char *)str);
	
	if(start_stop_v && !simulation_get_finished()) {
		simulation_update();
		step_val++;
		if(record) {
			fprintf(f_rec, "\t%d %1.5lf\n", step_val, rate_val);
		}
		if(simulation_get_finished()) {
			start_stop_v = 0;
			start_btn->name = "START";
			if(record) {
				fclose(f_rec);
				record = 0;
				rec_box->set_int_val(0);
			}
		}
	}
	glutPostRedisplay();
}

static void mouse(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		S2D p;
		p.x = (double)x;
		p.y = (double)y;
		graphic_convert_mouse(&(p.x), &(p.y));
		simulation_select(p);
	}
}

static void keys(unsigned char key, int x, int y) {
	if(key == 'P') {
		graphic_toggle_p();
	}
}

static void special_keys(int key, int x, int y) {
	if(key == GLUT_KEY_UP) {
		simulation_man_for();
	}
	if(key == GLUT_KEY_DOWN) {
		simulation_man_back();
	}
	if(key == GLUT_KEY_LEFT) {
		simulation_man_left();
	}
	if(key == GLUT_KEY_RIGHT) {
		simulation_man_right();
	}
}



