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
	#include "robot.h"
	#include "particle.h"
	#include "model.h"
	#include "graphic.h"
	#include "constantes.h"
	#include "error.h"
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

namespace {
	std::string o_filename;
	std::string s_filename;
	int g_window;
	GLUI * glui;
	char * start_stop;
	GLUI_Button * start_btn;
	int start_stop_v = 0;
	int record = 0;
	GLUI_StaticText * rate_text, * step_text, * trans_text, * rot_text;
	double rate_val = 0.0;
	unsigned int step_val = 0;
	int ctrl_mode = 0;
}


int main(int argc, char ** argv){
	if(argc > 2){
		if(!strcmp(argv[1],"Error")){
			if(check_file(argv[2])) {
				error_no_error_in_this_file();
			}
			exit(0);
		} else if(!strcmp(argv[1],"Draw")){
			check_file(argv[2]);
		} else {
			printf("Usage: [Error|Draw] <Filename>\n");
			return EXIT_FAILURE;
		}
	} else if(argc > 1){
		printf("Usage: [Error|Draw] <Filename>\n");
		return EXIT_FAILURE;
	}
	g_window = graphic_init_glut(&argc, argv);
	GUI();
	glutMainLoop();
	return EXIT_SUCCESS;
}

static void GUI(void){
	GLUI_Master.set_glutReshapeFunc(graphic_reshape);  
	GLUI_Master.set_glutIdleFunc(idle);
	
	glui = GLUI_Master.create_glui("CONTROL", 0, GLUI_POSX, GLUI_POSY);
	
	GLUI_Panel * open_panel = new GLUI_Panel(glui, "Open");
	new GLUI_EditText(open_panel, "File Name:", o_filename);
	new GLUI_Button(open_panel, "OPEN", OPEN, (GLUI_Update_CB)control);
	GLUI_Panel * save_panel = new GLUI_Panel(glui, "Save");
	new GLUI_EditText(save_panel, "File Name:", s_filename);
	new GLUI_Button(save_panel, "SAVE", SAVE, (GLUI_Update_CB)control);
	new GLUI_Column(glui, false);
	
	GLUI_Panel * sim_panel = new GLUI_Panel(glui, "Simulation");
	start_btn = new GLUI_Button(sim_panel, "START", START, (GLUI_Update_CB)control);
	new GLUI_Button(sim_panel, "STEP", STEP, (GLUI_Update_CB)control);
	GLUI_Panel * rec_panel = new GLUI_Panel(glui, "Record");
	new GLUI_Checkbox(rec_panel, "Record", &record, REC, (GLUI_Update_CB)control);
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
	printf("Open: %s\n", fn);
	robot_delete_all();
	particle_delete_all();
	check_file((char *) fn);
	//~ robot_print();
	//~ particle_print();
	glutPostRedisplay();
}

static int check_file(char * filename){
	if(!(read_file(filename) && initial_collisions())){
		robot_delete_all();
		particle_delete_all();
		return 0;
	}
	return 1;
}

static void save(void){
	const char * fn = s_filename.c_str();
	printf("Save: %s\n", fn);
	read_save((char *) fn);
}

static void start(void){
	start_stop_v = !start_stop_v;
	if(start_stop_v){
		printf("start\n");
		start_btn->name = "STOP";
	} else {
		printf("stop\n");
		start_btn->name = "START";
	}
}

static void step(void){
	update();
	step_val++;
	graphic_affichage();
	printf("step\n");
}

static void rec(void){
	if(record) {
		printf("recording started\n");
	} else {
		printf("recording stopped\n");
	}
}

static void ctrl(void){
	if(ctrl_mode) {
		printf("control mode set to manual\n");
	} else {
		printf("control mode set to automatic\n");
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
	sprintf(str, "rate: %1.3lf", rate_val);
	rate_text->set_text((const char *)str);
	sprintf(str, "step: %d", step_val);
	step_text->set_text((const char *)str);
}



