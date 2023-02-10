//Bilal Akbar
//Roll No 21i-1174
//Section Q
//Final project
#include "util.h"
#include <iostream>
#include <string>
#include "classes.h"
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;


void Timer(int m)
{

	// implement your functionality here
	Game::moveshapes();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000 / 60, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y)
{
	// cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y)
{
	// cout << x << " " << y << endl;
	glutPostRedisplay();
}

void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		cout << "Right Button Pressed" << endl;
	}
	glutPostRedisplay();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 200, 0, 200); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
/*
 * our gateway main function
 * */

int main(int argc, char *argv[]) // these commands are used to initilize glut variables
{
	int width = 900, height = 600;				 // i have set my window size to be 800 x 600
	InitRandomizer();							 // seed the random number generator...
	glutInit(&argc, argv);						 // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // we will be using color display mode
	glutInitWindowPosition(250, 100);			 // set the initial position of our window
	glutInitWindowSize(width, height);			 // set the size of our window

	glutCreateWindow("i211174 OOP Project"); // set the title of our game window
	// SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	// glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutReshapeFunc(reshape);	  // setting cartesian plane for the window
	glutDisplayFunc(Game::GameDisplay); // tell library which function to call for drawing Canvas.

	glutSpecialFunc(Game::NonPrintableKeys); // tell library which function to call for non-printable ASCII characters

	glutKeyboardFunc(Game:: PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);	  // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
