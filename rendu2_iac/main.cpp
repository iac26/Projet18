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

extern "C" {
	#include "read.h"
	#include "robot.h"
	#include "particle.h"
	#include "model.h"
	#include "graphic.h"
	#include "constantes.h"
}

#define WIDTH 800
#define HEIGHT 800

static void quit(void);
static void open(void);
static void save(void);
static void start(void);
static void step(void);
static void control(void);
static void idle(void);

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
	int step_val = 0;
	int ctrl_mode = 0;
}


int main(int argc, char ** argv) {
	
	if (argc > 1) {
		if(read_file(argv[1])) {
			robot_print();
			particle_print();
			initial_collisions();
		}
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200,200);
	glutInitWindowSize(WIDTH,HEIGHT);
	g_window = glutCreateWindow("ROBOTS");
	glViewport(0, 0, WIDTH, HEIGHT);
	glOrtho(-DMAX, DMAX, -DMAX, DMAX, -1, 1);
	glutDisplayFunc(graphic_affichage);
	glClearColor(1.0, 1.0, 1.0, 0.0);
	
	//GLUI_Master.set_glutDisplayFunc(graphic_affichage); 
	GLUI_Master.set_glutReshapeFunc(graphic_reshape);  
	GLUI_Master.set_glutIdleFunc(idle);
	
	//GLUI GUI
	
	glui = GLUI_Master.create_glui("CONTROL", 0, 900, 200);
	
	GLUI_Panel * open_panel = new GLUI_Panel(glui, "Open");
	new GLUI_EditText(open_panel, "File Name:", o_filename);
	new GLUI_Button(open_panel, "OPEN", 0, (GLUI_Update_CB)open);
	
	GLUI_Panel * save_panel = new GLUI_Panel(glui, "Save");
	new GLUI_EditText(save_panel, "File Name:", s_filename);
	new GLUI_Button(save_panel, "SAVE", 0, (GLUI_Update_CB)save);
	
	new GLUI_Column(glui, false);
	
	GLUI_Panel * sim_panel = new GLUI_Panel(glui, "Simulation");
	start_btn = new GLUI_Button(sim_panel, "START", 0, (GLUI_Update_CB)start);
	new GLUI_Button(sim_panel, "STEP", 0, (GLUI_Update_CB)step);
	
	GLUI_Panel * rec_panel = new GLUI_Panel(glui, "Record");
	new GLUI_Checkbox(rec_panel, "Record", &record);
	rate_text = new GLUI_StaticText(rec_panel, "Rate: 0.000");
	step_text = new GLUI_StaticText(rec_panel, "Step: 0");
	
	new GLUI_Column(glui, false);
	
	GLUI_Panel * control_panel = new GLUI_Panel(glui, "Control Mode");
	GLUI_RadioGroup * ctrl_r = new GLUI_RadioGroup(control_panel, &ctrl_mode, 0, (GLUI_Update_CB)control);
	new GLUI_RadioButton(ctrl_r, "Automatic");
	new GLUI_RadioButton(ctrl_r, "Manual"); 

	GLUI_Panel * r_control_panel = new GLUI_Panel(glui, "Robot Control");
	trans_text = new GLUI_StaticText(r_control_panel, "Translation: 0.000");
	rot_text = new GLUI_StaticText(r_control_panel, "Rotation:     0.000");
	
	new GLUI_Button(glui, "EXIT", 0, (GLUI_Update_CB)quit);
	
	glui->set_main_gfx_window(g_window);
	
	glutMainLoop();
	
	
	return EXIT_SUCCESS;
}

static void open(void) {
	const char * fn = o_filename.c_str();
	printf("Open: %s\n", fn);
	robot_delete_all();
	particle_delete_all();
	read_file((char *) fn);
	glutPostRedisplay();
}

static void save(void) {
	const char * fn = s_filename.c_str();
	printf("Save: %s\n", fn);
}

static void start(void) {
	start_stop_v = !start_stop_v;
	if(start_stop_v) {
		start_btn->name = "STOP";
	} else {
		start_btn->name = "START";
	}
}

static void step(void) {
	step_val++;
	printf("step\n");
}

static void control(void) {
	printf("ctrl\n");
}

static void quit(void) {
	glutDestroyWindow(g_window);
	exit(0);
}

static void idle(void) { 
	glutSetWindow(g_window);
	char str[20];
	sprintf(str, "rate: %1.3lf", rate_val);
	rate_text->set_text((const char *)str);
	sprintf(str, "step: %d", step_val);
	step_text->set_text((const char *)str);
}



