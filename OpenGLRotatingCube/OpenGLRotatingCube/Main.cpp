#include <stdio.h>
#include <math.h>

// While 0 check if they are in source file
#ifdef __Danae__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Mouse Enumerations 
enum {
	UP = 1,
	DOWN,
};

//Vector
typedef float vec3_t[3];

//Window width and height
int wndWidth = 300;
int wndHeight = 500;

//Old mouse position 
int oldX = -13;
int oldY = -13;

//Mouse state
int mState = UP;

//Global rotation, for use with the mouse
vec3_t gRot = { 0,0,0 };

//Initialize Graphics 
void Init_Graphics()
{
	//Front
	glBegin(GL_POLYGON);

	glColor3f(1.0, 0.0, 0.0);		glVertex3f(0.5, -0.5, -0.5);     //Red
	glColor3f(0.0, 1.0, 0.0);		glVertex3f(0.5, 0.5, -0.5);      //Green
	glColor3f(0.0, 0.0, 1.0);		glVertex3f(-0.5, 0.5, -0.5);     //Blue
	glColor3f(1.0, 1.0, 0.0);		glVertex3f(-0.5, -0.5, -0.5);    //Yellow

	glEnd();

	//Back
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);		glVertex3f(0.5, -0.5, 0.5);
	glColor3f(0.0, 0.0, 1.0);		glVertex3f(0.5, 0.5, 0.5);
	glColor3f(0.0, 1.0, 0.0);		glVertex3f(-0.5, 0.5, 0.5);
	glColor3f(1.0, 0.0, 0.0);		glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	//Right
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 1.0);		glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();

	//Left
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0);		glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();

	//Up
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);		glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	//Down
	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 1.0);		glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
}
//Display Function
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Move our eye position 2 units away
	glTranslatef(0, 0, -2);
	//Apply the rotation from the mouse
	glRotatef(gRot[0], 1.0, 0.0, 0.0);
	glRotatef(gRot[1], 0.0, 1.0, 0.0);

	Init_Graphics();

	glutSwapBuffers();
}
//Resize Function
void Resize(int w, int h)
{
	if (!h)
		return;

	wndWidth = w;
	wndHeight = h;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear screen and buffer
	glViewport(0, 0, wndWidth, wndHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //Reset transformations

	gluPerspective(90, wndWidth / wndHeight, 1, 9999);

	glutPostRedisplay();//Refresh screen
}
//Motion Function
void Motion(int x, int y)
{
	if (mState == DOWN)
	{
		gRot[0] -= ((oldY - y) * 180.0f) / 100.0f;
		gRot[1] -= ((oldX - x) * 180.0f) / 100.0f;
	
		glutPostRedisplay();
	}
	oldX = x;
	oldY = y;
}
//Mouse Function
void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
		case GLUT_RIGHT_BUTTON:
			mState = DOWN;
			oldX = x;
			oldY = y;
			break;
		}
	}
	else if (state == GLUT_UP)
		mState = UP;
}
//OpenGL Init
void Init(void)
{
	glEnable(GL_DEPTH_TEST);
}
//Main Function
int main(int argc, char* argv[]) 
{
	//Initialize GLUT and process user parameters
	glutInit(&argc, argv);

	//Request double buffered true color window with Z-buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Create Presentation Window
	glutCreateWindow("OpenGL Cube");

	//Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);

	//Callback functions
	glutDisplayFunc(Display);
	glutReshapeFunc(Resize);
	glutMotionFunc(Motion);
	glutMouseFunc(Mouse);

	//Display Everythin and wait
	Init();
	glutMainLoop();

	//Return to OS
	return 0;
}