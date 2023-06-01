#include <windows.h>
#include <mmsystem.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>
#include <time.h>  
#define MAX_OBJ 10

using namespace std;
const double TWO_PI = 6.2831853;

GLsizei winWidth = 1000, winHeight = 500;
GLuint regHex;
GLuint bubbles;

//GLuint icra;
static GLfloat rotTheta = 0.0;
float Xg, Yg;
double i = 800.0;
double j = 0.0;
double alpha = 0.01;
double viteza_peste1 = 0.1;

double peste1X = 0.4;
double peste1Y = 1.0;
float timp = 0;

int pos_x[MAX_OBJ], pos_y[MAX_OBJ];
int k = 0;
int next_i = 0;

float* R = new float[10];
float* G = new float[10];
float* B = new float[10];


int raspuns = 0;

void Initialize(int key)
{


	switch (key)
	{

	case 1:
		raspuns = 0;
		break;
	case 2:
		raspuns = 1;
		break;
	}


}


float* generare_R(float* R)
{
	R = new float[10];
	for (int kt = 0; kt < 10; kt++)
		R[kt] = (float)rand() / RAND_MAX;

	return R;
}

float* generare_G(float* G)
{
	G = new float[10];
	for (int kt = 0; kt < 10; kt++)
		G[kt] = (float)rand() / RAND_MAX;

	return G;

}

float* generare_B(float* B)
{
	B = new float[10];
	for (int kt = 0; kt < 10; kt++)
		B[kt] = (float)rand() / RAND_MAX;

	return B;
}

void callback_Main(int key)
{
	if (key == 0)
	{
		exit(0);
	}
}

class scrPt
{
public:
	GLint x, y;
};


void miscas(void)
{
	i = i + alpha;
	if (i < -400.0)
		alpha = viteza_peste1;
	else if (i > 1500.0)
		alpha = -viteza_peste1;


	glutPostRedisplay();
}




void merge()
{
	alpha = -viteza_peste1;
	glutIdleFunc(miscas);
}

static void init(void)
{
	glClearColor(0.1, 0.5, 0.7, 0.0);
	if (raspuns == 0)
	{
		R = generare_R(R);
		G = generare_G(G);
		B = generare_B(B);
	}
}

void deseneaza_peste(int initX, int initY, float R, float G, float B) {
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);

	srand((unsigned)time(NULL));

	glColor3f(R, G, B);
	glBegin(GL_POLYGON);
	for (k = 0; k < 50; k++)
	{
		hexTheta = TWO_PI * k / 50;
		hexVertex.x = initX + 70 * cos(hexTheta);
		hexVertex.y = initY + 30 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);
		Xg = Xg + hexVertex.x;
		Yg = Yg + hexVertex.y;
	}
	Xg = Xg / 10;
	Yg = Yg / 10;
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(R, G, B);
	glVertex2f(initX + 50, initY);
	glVertex2f(initX + 100, initY + 50);
	glVertex2f(initX + 100, initY - 50);


	glEnd();

	glPointSize(5);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(0.0, 0.0, 0.0); 
	glVertex2i(initX - 50, initY + 5);
	glEnd();

	glEndList();
}

void onClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		pos_x[next_i] = x;
		pos_y[next_i] = abs(y - 500);
		next_i++;
		if (next_i == MAX_OBJ)
			next_i = 0;
		if (k < MAX_OBJ)
			k++;
	}
}

void drawCaviar(int x, int y)
{
	glColor3f(1.0, 0.5, 0.0);

	glPointSize(15);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.7, 1.0); 
	glVertex2i(x, y);
	glEnd();
	glEndList();
}


void displayCaviar(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	if (timp <= 10) {
		for (int i = 0; i < MAX_OBJ; ++i)
		{
			drawCaviar(pos_x[i], pos_y[i]);
			
		}
	
		timp += 1;
		
	}
}

void displayHex(void)
{
	if (raspuns == 1)
	{
		R = generare_R(R);
		G = generare_G(G);
		B = generare_B(B);
	}

	if (peste1X < 0.80000)
		peste1X += 0.00001;


	glClear(GL_COLOR_BUFFER_BIT);

	if (timp < 5000)
	{
		timp += 1;
		for (int i = 0; i < MAX_OBJ; ++i)
		{
			drawCaviar(pos_x[i], pos_y[i]);

		}
		
	}
	
	if (timp >= 5000)
	{
		
		for (int itr = 0; itr < 10; itr++)
		{
			if (pos_x[itr] != 0 && pos_y[itr] != 0)
			{
				deseneaza_peste(pos_x[itr], pos_y[itr], R[itr], G[itr], B[itr]);
				
				glPushMatrix();
				glTranslated(i, 0.0, 0.0);

				glCallList(regHex);

				glPopMatrix();
			}
		}


	}

	glFlush();
}


void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1000.0, 0.0, 500.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Acvariu cu pesti");
	Initialize(raspuns);
	init();
	
	glutDisplayFunc(displayHex);
	glutReshapeFunc(winReshapeFcn);
	
	glutMouseFunc(onClick);
	merge();

	int menuMain, menuFish;

	menuFish = glutCreateMenu(Initialize);
	glutAddMenuEntry("Normal", 1);
	glutAddMenuEntry("Carnaval", 2);

	menuMain = glutCreateMenu(callback_Main);

	glutAddSubMenu("Culoare pesti ", 1);
	glutAddMenuEntry("Iesire ", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();

}


