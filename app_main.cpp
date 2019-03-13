#include <iostream>
#include <cmath>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include <string>
#include "board.h"
#include "dot.h"


using namespace std;

// Store the width and height of the window
int width = 640, height = 640;
Board board;

void draw_toolbar(){
	glColor3f(0.2,0.2,0.2);
	glBegin(GL_QUADS);
	glVertex2f(-1, -0.88);
	glVertex2f(-1, -1);
	glVertex2f(1, -1);
	glVertex2f(1, -0.88);
	glEnd();
}

//draws a box of scene size 0.1  downwards and to the right of coords
void draw_butt(float x, float y, string color){ //lol
//use windowtoscene() to translate to -1 >> 1 coords
	if(color == "black") glColor3f(0,0,0);
	if(color == "white") glColor3f(1,1,1);
	if(color == "red") glColor3f(1,0,0);
	if(color == "green") glColor3f(0,1,0);
	if(color == "blue") glColor3f(0,0,1);
	glBegin(GL_QUADS);
	glVertex3f(x, y, 1);
	glVertex3f(x, y-0.1, 1);
	glVertex3f(x+0.1, y-0.1, -1);
	glVertex3f(x+0.1, y, 1);
	glEnd();
	
}	


//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    


	glColor3f(1,1,1);
	glRasterPos3f(-0.97,-0.955,2);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'P');
	glRasterPos3f(-0.87,-0.955,2);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'E');
    // Draw stuff here
	draw_toolbar();
    draw_butt(-0.995,-0.89,"black");
	draw_butt(-0.885,-0.89,"black");
	draw_butt(-0.775,-0.89,"red");
	draw_butt(-0.665,-0.89,"green");
	draw_butt(-0.555,-0.89,"blue");
	draw_butt(-0.445,-0.89,"black");
	board.draw_dots();
    
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	//cout << "original coords: " << x << ", " << y << endl;
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
	//cout << "new coords: " << x << ", " << y << endl; 
}

void sceneToWindow(float& x, float& y){ //validated
	//cout << "original coords: " << x << ", " << y << endl;
	x = ((x+1.0f)/2.0f) * float(width);
	y = ((y-1.0f)/2.0f) * float(height);
	//cout << "new coords: " << x << ", " << y << endl; 
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -2, 2);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	
	float mx = (float)x;
	float my = (float)y;
	

	windowToScene(mx, my);
	board.set_mode(mx, my);
	//sceneToWindow(mx, my); //test if the reverse function works

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {

	// Again, we redraw the scene 
	/*
	float newx = (float) x;
	float newy = (float) y;
	windowToScene(newx,newy);
	cout << "scene coords: " << newx << ", " << newy << endl;
	*/
	float newx = (float) x;
	float newy = (float) y;
	windowToScene(newx,newy);
	int color = board.get_color();
	if(board.get_mode() == 1){
		board.add_dot(newx,newy,color);
	} else {
		board.erase_at(newx,newy, height);
	}
	
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	
    switch (key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


void idle() {

}



int main(int argc, char** argv) {

		// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("CSE165 OpenGL Demo");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
    glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);
    
    glutIdleFunc(idle);

	// Start the main loop
	glutMainLoop();
}



