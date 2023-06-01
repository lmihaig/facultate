
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <iostream>

using namespace std;

const double TWO_PI = 6.2831853;
double i = 0.;
// unde se va opri masina pe axa x, cand face schimbarea de benzi
double xFinal = 20;
double j = 1.0;
double k = 0;
double vitezaTrafic = 0.15;
GLsizei winWidth = 500, winHeight = 500;
GLuint traficID;
static GLfloat rotTheta = 0.0;

class scrPt
{
public:
	GLfloat x, y, z;
	void print(const char* text = " ") {
		cout << text << ' ' << x << ' ' << y << ' ' << z << endl;
	}
	scrPt operator + (scrPt const& a) {
		scrPt res;
		res.x = x + a.x;
		res.y = y + a.y;
		res.z = z + a.z;
		return res;
	}
	scrPt operator - (scrPt const& a) {
		scrPt res;
		res.x = x - a.x;
		res.y = y - a.y;
		res.z = z - a.z;
		return res;
	}
};



void miscareGirofar(void) {
	// pentru girofar
	j += 0.05;
	if (j > 360) {
		j = 0;
	}
	if (j < 0) {
		j = 360;
	}

	// pentru schimbarea benzii
	if (i > xFinal && i > -120) {
		i -= 0.15;
	}
	if (i < xFinal && i < 20) {
		i += 0.15;
	}

	
	glutPostRedisplay();
}

static void init(void)
{
	scrPt cerc;
	GLdouble theta;
	GLint aux;
	GLint n = 2000;

	// 159 / 255 , 61 / 255 , 0 , 1
	glClearColor(0.6235294, 0.239215, 0, 1);
	gluOrtho2D(-100, 100, -100, 100);


	traficID = glGenLists(1);
	


	for (aux = 0; aux < 20; aux++)
	{
		glColor3f(0, 1, 0);
		glRectf(20, 100 + aux * 20, 60, 160 + aux * 20);

		glColor3f(0.5, 0, 0.5);
		glRectf(-120, 250 + aux * 20, -80, 310 + aux * 20);
	}
	glEndList();

	// pentru opacitatea culorilor
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			xFinal = -120;
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			xFinal = 20;
		break;
	default:
		break;
	}
}

void desenDrum(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();


	// DRUMUL
	glColor3f(0.2, 0.2, 0.2);
	glRectf(-200., -1000., 200., 1000.);
	// Linia ce separa benzile
	glColor3f(1, 1, 1);
	glRectf(-10., -1000., 10., 1000.);

	// initializare pentru tranzitii
	glPushMatrix();
	glTranslated(i, 0, 0);

	// MASINA DE POLITIE
	// sasiu
	glColor3f(0, 0, 0);
	glRectf(20, -180, 80, -155);
	glColor3f(1, 1, 1);
	glRectf(20, -155, 80, -115);
	glColor3f(0, 0, 0);
	glRectf(20, -115, 80, -90);


	// stopuri
	glColor3f(1, 0, 0);
	glRectf(25, -185, 35, -180);
	glColor3f(1, 0, 0);
	glRectf(65, -185, 75, -180);

	// faruri
	glColor3f(0.8, 0.5, 0);
	glRectf(25, -90, 35, -85);
	glColor3f(0.8, 0.5, 0);
	glRectf(65, -90, 75, -85);

	
	glColor3f(1, 1, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(30, -85);
	glVertex2f(0, 0);
	glVertex2f(60, 0);

	glVertex2f(40, 0);
	glVertex2f(100, 0);
	glVertex2f(70, -85);

	glEnd();


	// GIROFAR
	

	glTranslated(50, -135, 0);
	glRotated(j, 0, 0, 1);
	glTranslated(-50, 135, 0);

	//girofar
	glColor4f(1, 0, 0, 0.5);
	glBegin(GL_TRIANGLES);
	glVertex2f(10, -115);
	glVertex2f(50, -135);
	glVertex2f(10, -155);
	glEnd();


	glColor4f(0, 0, 1, 0.5);
	glBegin(GL_TRIANGLES);
	glVertex2f(50, -135);
	glVertex2f(90, -115);
	glVertex2f(90, -155);
	glEnd();

	glPopMatrix();

	glPopMatrix();
	// incrementare pentru girofar si alte translatii
	glutIdleFunc(miscareGirofar);

	glutSwapBuffers();
	glFlush();
}


void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, (GLsizei)newWidth, (GLsizei)newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-250.0, 250.0, -250.0, 250.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Trafic - Masina de politie");

	init();

	glutDisplayFunc(desenDrum);
	glutReshapeFunc(winReshapeFcn);

	
	glutMouseFunc(mouse);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();

}

