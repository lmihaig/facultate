#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <iostream>

using namespace std;

const double TWO_PI = 6.2831853;
const double PI = 3.1415926;

GLsizei winWidth = 1000, winHeight = 1000;
GLuint regHexiii, regHexiv, regHexv, regHexvi, cerc, cercII, cercIII, cercIV;
static GLfloat rotTheta = 0.0;
int dif = 1;
//FACTORI TRANSFORMARI
double j = 0.0, i = 5.0, l = -6.0, m = -6.0;

class scrPt
{
public:
	GLint x, y;
};


static void init(void)
{

	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	
	//ROTITE (regHex pt exterior, cerc pt inteior)
	regHexiii = glGenLists(1);
	glNewList(regHexiii, GL_COMPILE);
	int copie = 0;
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.4, 0.4, 0.45);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(55, 80);
	for (k = 1; k <= 81; k++)
	{
		hexTheta = TWO_PI * k / 80;
		if (k - copie == 4 && dif == 0) {
			dif = 1;
			copie = k;
		}
		if (k - copie == 4 && dif == 1) {
			dif = 0;
			copie = k;
		}
		if (dif) {
			hexVertex.x = 55 + 25 * cos(hexTheta);
			hexVertex.y = 80 + 25 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}
		else {
			hexVertex.x = 55 + 20 * cos(hexTheta);
			hexVertex.y = 80 + 20 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}

	}
	glEnd();
	glEndList();

	cerc = glGenLists(1);
	glNewList(cerc, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.105, 0.1, 0.1);
	glBegin(GL_POLYGON);
	for (k = 0; k < 80; k++)
	{
		hexTheta = TWO_PI * k / 80;
		hexVertex.x = 55 + 13 * cos(hexTheta);
		hexVertex.y = 80 + 13 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}
	glEnd();
	glEndList();

	dif = 0;

	regHexiv = glGenLists(1);
	glNewList(regHexiv, GL_COMPILE);
	copie = 0;
	glPolygonMode(GL_FRONT, GL_FILL);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(16, 99);
	for (k = 0; k <= 81; k++)
	{
		hexTheta = TWO_PI * k / 80;
		if (k - copie == 4 && dif == 0) {
			dif = 1;
			copie = k;

		}
		if (k - copie == 4 && dif == 1) {
			dif = 0;
			copie = k;
		}
		if (dif) {
			hexVertex.x = 16 + 22 * cos(hexTheta);
			hexVertex.y = 99 + 22 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}
		else {
			hexVertex.x = 16 + 17 * cos(hexTheta);
			hexVertex.y = 99 + 17 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}

	}
	glEnd();
	glEndList();

	cercII = glGenLists(1);
	glNewList(cercII, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.105, 0.1, 0.1);
	glBegin(GL_POLYGON);
	for (k = 0; k < 80; k++)
	{
		hexTheta = TWO_PI * k / 80;
		hexVertex.x = 16 + 10 * cos(hexTheta);
		hexVertex.y = 99 + 10 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}
	glEnd();
	glEndList();

	dif = 1;

	regHexv = glGenLists(1);
	glNewList(regHexv, GL_COMPILE);
	copie = 0;
	glPolygonMode(GL_FRONT, GL_FILL);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(-27, 109);
	for (k = 0; k <= 81; k++)
	{
		hexTheta = TWO_PI * k / 80;
		if (k - copie == 4 && dif == 0) {
			dif = 1;
			copie = k;

		}
		if (k - copie == 4 && dif == 1) {
			dif = 0;
			copie = k;
		}
		if (dif) {
			hexVertex.x = -27 + 26.4 * cos(hexTheta);
			hexVertex.y = 109 + 26.4 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}
		else {
			hexVertex.x = -27 + 20.4 * cos(hexTheta);
			hexVertex.y = 109 + 20.4 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}

	}
	glEnd();
	glEndList();

	cercIII = glGenLists(1);
	glNewList(cercIII, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.105, 0.1, 0.1);
	glBegin(GL_POLYGON);
	for (k = 0; k < 80; k++)
	{
		hexTheta = TWO_PI * k / 80;
		hexVertex.x = -27 + 12 * cos(hexTheta);
		hexVertex.y = 109 + 12 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}
	glEnd();
	glEndList();

	dif = 0;

	regHexvi = glGenLists(1);
	glNewList(regHexvi, GL_COMPILE);
	copie = 0;
	glPolygonMode(GL_FRONT, GL_FILL);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2i(-11, 157);
	for (k = 0; k <= 81; k++)
	{
		hexTheta = TWO_PI * k / 80;
		if (k - copie == 4 && dif == 0) {
			dif = 1;
			copie = k;
		}
		if (k - copie == 4 && dif == 1) {
			dif = 0;
			copie = k;
		}
		if (dif) {
			hexVertex.x = -11 + 30 * cos(hexTheta);
			hexVertex.y = 157 + 30 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}
		else {
			hexVertex.x = -11 + 24 * cos(hexTheta);
			hexVertex.y = 157 + 24 * sin(hexTheta);
			glVertex2i(hexVertex.x, hexVertex.y);
		}

	}
	glEnd();
	glEndList();

	cercIV = glGenLists(1);
	glNewList(cercIV, GL_COMPILE);
	glPolygonMode(GL_FRONT, GL_FILL);
	glColor3f(0.105, 0.1, 0.1);
	glBegin(GL_POLYGON);
	for (k = 0; k < 80; k++)
	{
		hexTheta = TWO_PI * k / 80;
		hexVertex.x = -11 + 15 * cos(hexTheta);
		hexVertex.y = 157 + 15 * sin(hexTheta);
		glVertex2i(hexVertex.x, hexVertex.y);

	}
	glEnd();
	glEndList();


}

void displayHex(void)
{
	glClear(GL_COLOR_BUFFER_BIT);


	//ROTITE (au rotatie pe loc, fiecare cu factori diferiti)
	glPushMatrix();
	glTranslated(55, 80, 0.0);
	glRotated(j, 0.0, 0.0, 1.0);
	glTranslated(-55, -80, 0.0);
	glCallList(regHexiii);
	glPopMatrix();

	glColor3f(0.4, 0.4, 0.45);
	glPushMatrix();
	glTranslated(16, 99, 0);
	glRotated(i, 0, 0, 1);
	glTranslated(-16, -99, 0);
	glCallList(regHexiv);
	glPopMatrix();


	glPushMatrix();
	glTranslated(-27, 109, 0);
	glRotated(l, 0.0, 0.0, 1.0);
	glTranslated(27, -109, 0);
	glCallList(regHexv);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-11, 157, 0);
	glRotated(m, 0.0, 0.0, 1.0);
	glTranslated(11, -157, 0);
	glCallList(regHexvi);
	glPopMatrix();

	//MIJLOCUL ROITITELOR
	glCallList(cerc);
	glCallList(cercII);
	glCallList(cercIII);
	glCallList(cercIV);

	glutSwapBuffers();
	glFlush();
}

void miscad(void)
{
	//FACTORI ROTATIE ROTITE
	j += 0.01;
	i -= 0.013;
	l += 0.0096;
	m -= 0.0066;
	

	glutPostRedisplay();

}


void miscas(void)
{
	//FACTORI ROTATIE ROTITE
	j -= 0.01;
	i += 0.015;
	l -= 0.0096;
	m += 0.0066;
	

	glutPostRedisplay();

}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {

			glutIdleFunc(miscas);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {

			glutIdleFunc(miscad);
		}
		break;
	case GLUT_MIDDLE_BUTTON:

	default:
		break;
	}
}

void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0, 320.0, -250.0, 340.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Hexagon - utilizarea listelor de display");

	init();
	glutDisplayFunc(displayHex);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouse);
	glutMainLoop();
}