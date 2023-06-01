#include<windows.h>
#include<gl/freeglut.h>
#include<math.h>
#include <stdlib.h>  
#include <cstdlib> 

// pozitia observatorului 
float x = 0.0f, y = -5.0f, z = 3.0f;
// pozitia sursei
float xs = -2.0, ys = -1.0, zs = 5.0, ts = 1.0;
// directia camerei (in lungul axei Oy)
float lx = 0.0f, ly = 1.0f, lz=0;
float fraction = 0.1f;
float alpha = 0.3; 


enum {
	NONE, DIR, UNU, ZERO_SASE, ZERO_PATRU, ZERO_DOI, ZERO_UNU, ZERO, ROSU, VERDE, ALBASTRU, NOUAZECI, TREIZECI,
	FUNDAL1, FUNDAL2, CUB1, CUB2, CUB3, CUB4, CUB5, CUB6,
};

int rendermode1 = NONE, rendermode1a = NONE, rendermode1b=UNU, rendermode1c=UNU, rendermode1d=NONE,
rendermode2a=FUNDAL1, rendermode2b=CUB1;

void menu1Events(int selection)
{
	rendermode1 = selection;
	glutPostRedisplay();
}
void menu1aEvents(int selection)
{
	rendermode1a = selection;
	glutPostRedisplay();
}
void menu1bEvents(int selection)
{
	rendermode1b = selection;
	glutPostRedisplay();
}
void menu1cEvents(int selection)
{
	rendermode1c = selection;
	glutPostRedisplay();
}
void menu1dEvents(int selection)
{
	rendermode1d = selection;
	glutPostRedisplay();
}

void menu2Events(int selection)
{
	rendermode1 = selection;
	glutPostRedisplay();
}
void menu2aEvents(int selection)
{
	rendermode2a = selection;
	glutPostRedisplay();
}
void menu2bEvents(int selection)
{
	rendermode2b = selection;
	glutPostRedisplay();
}
void createMenu1() {
	int menu1, menu1a, menu1b, menu1c, menu1d;
	// creaza
	
	menu1a = glutCreateMenu(menu1aEvents);
	//adauga itemi
	glutAddMenuEntry("Sursa punctuala", NONE);
	glutAddMenuEntry("Sursa directionala", DIR);

	menu1b = glutCreateMenu(menu1bEvents);
	//adauga itemi
	glutAddMenuEntry("1.0", UNU);
	glutAddMenuEntry("0.6", ZERO_SASE);
	glutAddMenuEntry("0.4", ZERO_PATRU);
	glutAddMenuEntry("0.2", ZERO_DOI);
	glutAddMenuEntry("0.1", ZERO_UNU);
	glutAddMenuEntry("0.0", ZERO);

	menu1c = glutCreateMenu(menu1cEvents);
	//adauga itemi
	glutAddMenuEntry("1.0", UNU);
	glutAddMenuEntry("0.6", ZERO_SASE);
	glutAddMenuEntry("0.4", ZERO_PATRU);
	glutAddMenuEntry("0.2", ZERO_DOI);
	glutAddMenuEntry("0.1", ZERO_UNU);
	glutAddMenuEntry("0.0", ZERO);
	glutAddMenuEntry("Rosu", ROSU);
	glutAddMenuEntry("Verde", VERDE);
	glutAddMenuEntry("Albastru", ALBASTRU);

	menu1d = glutCreateMenu(menu1dEvents);
	//adauga itemi
	glutAddMenuEntry("Implicit (180)", NONE);
	glutAddMenuEntry("Unghi 90 grade", NOUAZECI);
	glutAddMenuEntry("Unghi 30 grade", TREIZECI);

	menu1 = glutCreateMenu(menu1Events);
	glutAddSubMenu("Tipul", menu1a);
	glutAddSubMenu("Ambiental", menu1b);
	glutAddSubMenu("Difuz", menu1c);
	glutAddSubMenu("Efect spot", menu1d);
	// butonul stang
	glutAttachMenu(GLUT_LEFT_BUTTON);
}

void createMenu2() {
	int menu2, menu2a, menu2b;
	// creaza

	menu2a = glutCreateMenu(menu2aEvents);
	//adauga itemi
	glutAddMenuEntry("Amb=Difuz", FUNDAL1);
	glutAddMenuEntry("Difuz=0", FUNDAL2);

	menu2b = glutCreateMenu(menu2bEvents);
	//adauga itemi
	glutAddMenuEntry("Amb=Difuz", CUB1);
	glutAddMenuEntry("Difuz=A; NoAmb", CUB2);
	glutAddMenuEntry("Difuz=N; NoAmb", CUB3);
	glutAddMenuEntry("Difuz=N; AmbW", CUB4);
	glutAddMenuEntry("Difuz=W; NoAmb", CUB5);
	glutAddMenuEntry("Difuz=W; Amb0.2", CUB6);
	
 
	menu2 = glutCreateMenu(menu2Events);
	glutAddSubMenu("Fundal", menu2a);
	glutAddSubMenu("Cub", menu2b);

	// butonul drept
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void reshapeAndProjection(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void lumina(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	// initializari si proprietatile universale
	GLfloat alphaAmb = 1.0;
	GLfloat alphaDifuz=1.0;
	GLfloat difuzLumina[4];
	GLfloat unghiCutOff=180.0;

	GLfloat alb[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
	switch (rendermode1a) {
	case NONE:
		ts = 1.0;
		break;
	case DIR:
		ts = 0.0;
		break;
	};
	switch (rendermode1b) {
	case UNU:
		alphaAmb=1.0;
		break;
	case ZERO_SASE:
		alphaAmb = 0.6;
		break;
	case ZERO_PATRU:
		alphaAmb = 0.4;
		break;
	case ZERO_DOI:
		alphaAmb = 0.2;
		break;
	case ZERO_UNU:
		alphaAmb = 0.1;
		break;
	case ZERO:
		alphaAmb = 0.0;
		break;
	};
	switch (rendermode1c) {
	case UNU:
		alphaDifuz = 1.0;
		difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;
		break;
	case ZERO_SASE:
		alphaDifuz = 0.6;
		difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;
		break;
	case ZERO_PATRU:
		alphaDifuz = 0.4;
		difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;
		break;
	case ZERO_DOI:
		alphaDifuz = 0.2;
		difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;
		break;
	case ZERO_UNU:
		alphaDifuz = 0.1;
		difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;
		break;
	case ZERO:
		alphaDifuz = 0.0;
		difuzLumina[0] = alphaDifuz; difuzLumina[1] = alphaDifuz; difuzLumina[2] = alphaDifuz; difuzLumina[3] = 0;
		break;
	case ROSU:
		difuzLumina[0] = 1.0; difuzLumina[1] = 0.0; difuzLumina[2] = 0.0; difuzLumina[3] = 0.0;
		break;
	case VERDE:
		difuzLumina[0] = 0.0; difuzLumina[1] = 1.0; difuzLumina[2] = 0.0; difuzLumina[3] = 0.0;
		break;
	case ALBASTRU:
		difuzLumina[0] = 0.0; difuzLumina[1] = 0.0; difuzLumina[2] = 1.0; difuzLumina[3] = 0.0;
		break;
	};
	switch (rendermode1d) {
	case NONE:
		unghiCutOff = 180;
		break;
	case NOUAZECI:
		unghiCutOff = 90;
		break;
	case TREIZECI:
		unghiCutOff = 30;
		break;
	};
	// Sursa de lumina
	GLfloat ambientLumina[] = { alphaAmb, alphaAmb, alphaAmb, alphaAmb };
	GLfloat pozitial0[] = { xs, ys, zs, ts };
	GLfloat directieSpot[] = { 0, 0, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLumina);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difuzLumina);
	glLightfv(GL_LIGHT0, GL_SPECULAR, alb);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, directieSpot);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, unghiCutOff);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 3.0);
	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.2);

};
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lumina();
	GLfloat alb[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
		
	// Pozitia observatorului
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z+lz, 0.0f, 0.0f, 1.0f);
	//gluLookAt(0, 0, 50, 0 , 0, -1, 0.0f, 1.0f,0.0f);

	// Fundal
	GLfloat bleu[] = {0.52, 0.81, 0.93, 0.0 };
	switch (rendermode2a) {
	case FUNDAL1:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, bleu);
		break;
	case FUNDAL2:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bleu);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, negru);
		break;
	};
	
	glutSolidSphere(200, 30, 30);
 
	// Solul
	GLfloat verde[] = { 0.0, 1.0, 0.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, verde);
	glNormal3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, -100.0f, 0.0f);
	glVertex3f(-100.0f, 100.0f, 0.0f);
	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(100.0f, -100.0f, 0.0f);
	glEnd();

	// Sferele (pe partea stanga)
	float radius = 1.0; 
	GLfloat portocaliu[] = { 0.9, 0.5, 0.0, 0.0 };
	GLfloat rosu[] = { 0.9, 0.5, 0.0, 0.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, portocaliu);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, rosu);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 33.0f);
	for (int i = -3; i < 0; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 5.0+i*j/3, j * 5.0-i/2,  radius);
			glColor3f(0.9, 0.5, 0.0);
			glutSolidSphere(radius, 100, 100);
			glPopMatrix();
		}

	// Cuburile (pe partea dreapta)
	float lat = 1.5;
	GLfloat violet[] = { 0.8, 0.0, 0.9, 0.0 };
	GLfloat amb02[] = { 0.4, 0.4, 0.4, 0.0 };
	switch (rendermode2b) {
	case CUB1:
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, violet);
		break;
	case CUB2:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, negru);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, alb);
		break;
	case CUB3:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, negru);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, negru);
		break;
	case CUB4:
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, negru);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, violet);
		break;
	case CUB5:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, negru);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, violet);
		break;
	case CUB6:
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb02);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, violet);
		break;

	};
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, negru);
	for (int i = 0; i < 4; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 5.0+0.4*j*j, j * 5.0+i/10, lat);
			glutSolidCube(lat);
			glPopMatrix();
		}

	glutSwapBuffers();
	glFlush();
}

void renderScene2(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	lumina();


	GLfloat negru[] = { 0.0, 0.0, 0.0, 0.0 };
	// Pozitia observatorului
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 0.0f, 1.0f);
	//gluLookAt(0, 0, 50, 0 , 0, -1, 0.0f, 1.0f,0.0f);

	// Fundal
	glutSolidSphere(200, 30, 30);

	// Solul
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, -100.0f, 0.0f);
	glVertex3f(-100.0f, 100.0f, 0.0f);
	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(100.0f, -100.0f, 0.0f);
	glEnd();

	// Sferele (pe partea stanga)
	float radius = 1.0;
	for (int i = -3; i < 0; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 5.0 + i * j / 3, j * 5.0 - i / 2, radius);
			glColor3f(0.9, 0.5, 0.0);
			glutSolidSphere(radius, 100, 100);
			glPopMatrix();
		}

	// Cuburile (pe partea dreapta)
	float lat = 1.5;
	for (int i = 0; i < 4; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 5.0 + 0.4 * j * j, j * 5.0 + i / 10, lat);
			glutSolidCube(lat);
			glPopMatrix();
		}

	glutSwapBuffers();
	glFlush();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	float angle = 0.02f;
	float angles = 0.05f;
	switch (key) {
	case 'l':
		lx -= angle;
		break;
	case 'r':
		lx += angle;
		break;
	case 'u':
		lz += angle;
		break;
	case 'd':
		lz -= angle;
		break;
	case '1':
		xs-= angles;
		break;
	case '2':
		xs += angles;
		break;
	case '3':
		ys -= angles;
		break;
	case '4':
		ys += angles;
		break;
	case '5':
		zs -= angles;
		break;
	case '6':
		zs += angles;
		break;
	}
	if (key == 27)
		exit(0);
}
void processSpecialKeys(int key, int xx, int yy) {



	switch (key) {
	case GLUT_KEY_LEFT:
		x -= fraction;
		break;
	case GLUT_KEY_RIGHT:
		x += fraction;
		break;
	case GLUT_KEY_UP:
		y += fraction;
		break;
	case GLUT_KEY_DOWN:
		y -= fraction;
		break;
	}
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(1300, 700);
	glutCreateWindow("Modelul de iluminare");

	glutDisplayFunc(renderScene);
	//glutDisplayFunc(renderScene2);
	glutReshapeFunc(reshapeAndProjection);
	glutIdleFunc(renderScene);
	//glutIdleFunc(renderScene2);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	createMenu1();
	createMenu2();

	 glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 1;
}

