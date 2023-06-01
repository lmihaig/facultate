#include <windows.h>
#include <gl/freeglut.h>
#include <stdio.h> 
#include <stdlib.h>
#include <math.h> 

#define PI 3.14159265

GLint winWidth = 600, winHeight = 600;
GLdouble xx0 = 6.0, yy0 = 9.0, zz0 = 10.0;
GLdouble xref = 0.0, yref = 0.0, zref = 0.0;
GLfloat Vx = 1.0, Vy = -1.0, Vz = 0.0;

GLfloat xwMin = -30.0, ywMin = -30.0, xwMax = 30.0, ywMax = 30.0;

GLfloat dnear = 1.0, dfar = 40.0;

static GLdouble theta;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(xx0, yy0, zz0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void desen(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// sursa de lumina 0
	glEnable(GL_LIGHT0);
	GLfloat pozitial0[] = { 1.0, 5.0, 3.0, 0.0 };
	GLfloat rosu[] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat alb[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, alb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, negru);
	//glLightfv (GL_LIGHT0, GL_DIFFUSE, alb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, negru);
	//glLightfv (GL_LIGHT0, GL_SPECULAR, rosu);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

	// sursa de lumina 1
	//glEnable (GL_LIGHT1);
	GLfloat pozitial1[] = { 0.0, 5.0, 0.0, 1.0 };
	GLfloat albastru [ ] = {0.0, 0.0, 1.0, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, pozitial1);
	glLightfv (GL_LIGHT1, GL_SPECULAR, albastru);
	glLightfv (GL_LIGHT1, GL_DIFFUSE, albastru);
	glLightfv (GL_LIGHT1, GL_AMBIENT, albastru);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// roteste corpurile geometrice 
	glRotated(theta, 1.0, 0.0, 0.0);
	glLineWidth(1.0);

	//cub mare
	GLfloat diffuseCoeffb[] = { 0.0, 0.4, 1.0, 0.0 };
	GLfloat diffuseCoeffvariabil[] = { 1.0, 0.0, 0.0, 0.0 };
	//glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseCoeffvariabil);
    //glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, diffuseCoeffb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, rosu);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(6.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);

	// cub mic 
	GLfloat diffuseCoeffv[] = { 0.9, 0.4, 0.9, 0.0 };
	//glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseCoeffv);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, diffuseCoeffv);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
	glColor3f(1.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 8.0);
	glutSolidCube(2.0);
	glPopMatrix();

	//con
	GLfloat diffuseCoeffr[] = { 0.9, 0.2, 0.0, 1.0 };
	//glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseCoeffr);
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(5.0, 3.0, 2.0);
	glutWireCone(6.0, 5.0, 150, 150);
	glPopMatrix();

	//sfera 
	GLfloat diffuseCoeffve[] = { 0.0, 0.9, 0.2, 1.0 };
	GLfloat specularCoeffalb[] = { 0.0, 0.0, 0.9, 1.0 };
	//glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseCoeffve);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specularCoeffalb);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 26.0);
	glColor3f(0.0, 1.0, 0.0);
	glutWireSphere(4.0, 50, 50);

	glPopMatrix();

	//axele de coordonate
	GLfloat diffuseCoeffn[] = { 0.0, 0.0, 0.0, 1.0 };
	//glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuseCoeffn);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.5);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(20, 0, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 20, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 19);
	glEnd();
	//literele 
	glRasterPos3i(21, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'x');
	glRasterPos3i(0, 21, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'y');
	glRasterPos3i(0, 0, 20);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, 'z');

	glutSwapBuffers();
	glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
}

void mutarep(void)
{
	theta = theta + 1.0;
	glutPostRedisplay();
}
void mutarem(void)
{
	theta = theta - 1.0;
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(mutarep);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Efecte de iluminare");
	init();
	glutDisplayFunc(desen);
	glutReshapeFunc(reshapeFcn);
	glutMouseFunc(mouse);
	glutMainLoop();
}


