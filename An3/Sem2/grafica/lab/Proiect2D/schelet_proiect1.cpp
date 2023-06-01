#include<windows.h>
#include <gl/freeglut.h>



double k = 0.0;
double i = 0.0;
double alpha = 1.0;


void init(void)
{

	glClearColor(0.001, 0.53, 0.98, 0.0);
	//glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);

}
void deseneazaScena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//---------------------------------------------barca 
	glPushMatrix();
	
	glTranslated(420, 80, 0);
	glTranslated(k, 100.0, 0.0);
	glTranslated(-420, -80, 0);
	glColor3f(0.015, 0.007, 0.58);
	glBegin(GL_POLYGON); //barca 
	glVertex2f(300, 100);
	glVertex2f(500, 100);
	glVertex2f(450, 70);
	glVertex2f(350, 70);
	glEnd();

	glColor3f(0.67, 0.05, 0.001);
	glBegin(GL_TRIANGLES);
	glVertex2f(300, 105);
	glVertex2f(400, 105);
	glVertex2f(400, 160);
	glEnd();

	glLineWidth(5);
	glColor3f(0.33, 0.33, 0.34);
	glBegin(GL_LINES);
	glVertex2f(420, 100);
	glVertex2f(420, 155);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2f(440, 100);
	glVertex2f(440, 155);
	glEnd();
	glPopMatrix();

	
	glColor3f(0.53, 0.74, 0.96); // cer
	glBegin(GL_TRIANGLES);
	glVertex2i(-30, 600);
	glVertex2i(-30, 900);
	glVertex2i(1200, 900);
	glEnd();



	glColor3f(0.03, 0.61, 0.16);
	glBegin(GL_POLYGON); //iarba
	glVertex2i(-30, 600);
	glVertex2i(-30, 300);
	glVertex2i(1500, 900);
	glVertex2i(1200, 900);
	glEnd();
	//-----------------------------------copac
	glLineWidth(7);
	glColor3f(0.4, 0.27, 0.11);
	glBegin(GL_LINES);
	glVertex2f(1300, 830);
	glVertex2f(1300, 850);
	glEnd();

	glColor3f(0.07, 0.36, 0.12);
	glBegin(GL_TRIANGLES);
	glVertex2i(1280, 850);
	glVertex2i(1320, 850);
	glVertex2i(1300, 895);
	glEnd();

	

	//-----------------------------------casa 
	glColor3f(0.0, 0.4, 0.4);
	glBegin(GL_POLYGON);
	glVertex2i(1200, 820); //colt stanga jos
	glVertex2i(1230, 820); //colt dreapta jos
	glVertex2i(1230, 850); //colt dreapta sus
	glVertex2i(1200, 850); //colt stanga sus
	glEnd();
	glColor3f(0.6, 0.29, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2i(1200, 850);
	glVertex2i(1230, 850);
	glVertex2i(1215, 870);
	glEnd();
	glColor3f(0.0, 0.8, 0.4);
	glBegin(GL_POLYGON); // usa casa
	glVertex2i(1212, 820); //colt stanga jos + 12
	glVertex2i(1218, 820); //colt dreapta jos + 18
	glVertex2i(1218, 840); //colt dreapta sus + h= 20
	glVertex2i(1212, 840); //colt stanga sus + h = 20
	glEnd();
	//-------------------------------------


	
	glutSwapBuffers();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 1500, 0.0, 900.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void miscad(void)
{
	//miscare barci
	k = k + alpha;
	if (k > 1000.0)
		alpha = -1.0;
	else if (k < 0.0)
		alpha = 1.0;


	glutPostRedisplay();
}

void miscas(void)
{
	//miscare barci
	k = k + alpha;
	if (k < 0.0)
		alpha = 1.0;
	else if (k > 1000.0)
		alpha = -1.0;


	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = -1.0; glutIdleFunc(miscas);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			alpha = 1.0; glutIdleFunc(miscad);
		break;
	default:
		break;
	}
}


void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Lac cu barcute");
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(deseneazaScena);
	glutReshapeFunc(reshape);

	glutMainLoop();
}