/* Reprezentarea dreptunghiurilor
De retinut:
(i) modul in care sunt indexate varfurile. ORDINEA ESTE ESENTIALA.
(ii) Folosirea unor primitive de tipul caracter
(iii) Functia glPolygonMode
(iv) Functia Reshape
De testat si functia desen2
*/

#include <windows.h>
#include <gl/freeglut.h>

GLint winWidth = 800, winHeight = 600, xMax = 800, yMax = 600;

void init(void)  // initializare fereastra de vizualizare
{
	glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
	glMatrixMode(GL_PROJECTION);  // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
	gluOrtho2D(0.0, xMax, 0.0, yMax); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}

void desen1(void) // procedura desenare desen1
{
	glClear(GL_COLOR_BUFFER_BIT);
	int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
	// Ordinea indicarii coordonatelor / indexarea conteaza!
	x1 = 10; y1 = 10;
	x2 = 110; y2 = 10;
	x3 = 110; y3 = 110;
	x4 = 10; y4 = 110;
	x5 = 210; y5 = 10;
	x6 = 210; y6 = 110;

	// Varianta corecta
	//x1 = 10; y1 = 10;
	//x2 = 10; y2 = 110;
	//x3 = 110; y3 = 10;
	//x4 = 110; y4 = 110;
	//x5 = 210; y5 = 10;
	//x6 = 210; y6 = 110;
	
	// glPolygonMode (GL_BACK, GL_LINE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUAD_STRIP);
		glVertex2i(x1, y1);
		glVertex2i(x2, y2);
		glVertex2i(x3, y3);
		glVertex2i(x4, y4);
		glVertex2i(x5, y5);
		glVertex2i(x6, y6);
	glEnd();

	glColor3f(0.0, 0.0, 0.0);
	// Primitive de tip caracter
	glRasterPos2i(x1, y1);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
	glRasterPos2i(x2, y2);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '2');
	glRasterPos2i(x3, y3);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '3');
	glRasterPos2i(x4, y4);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '4');
	glRasterPos2i(x5, y5);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '5');
	glRasterPos2i(x6, y6);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '6');

	glFlush();
}
void desen2(void) // procedura desenare desen2
{
	glClear(GL_COLOR_BUFFER_BIT);
	int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
	// Ordinea indicarii coordonatelor / indexarea conteaza!
	//x1 = 10; y1 = 10;
	//x2 = 110; y2 = 10;
	//x3 = 110; y3 = 110;
	//x4 = 10; y4 = 110;
	//x5 = 210; y5 = 10;
	//x6 = 210; y6 = 110;

	// Varianta corecta
	x1 = 10; y1 = 10;
	x2 = 10; y2 = 110;
	x3 = 110; y3 = 10;
	x4 = 110; y4 = 110;
	x5 = 210; y5 = 10;
	x6 = 210; y6 = 110;
	

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBegin(GL_QUAD_STRIP);
		glColor3f(0.0, 0.0, 0.0);
		glVertex2i(x1, y1);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2i(x2, y2);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(x3, y3);
		glColor3f(0.8, 0.4, 0.0);
		glVertex2i(x4, y4);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2i(x5, y5);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2i(x6, y6);
	glEnd();

	// Primitivele de tip caracter
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2i(x1, y1);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '1');
	glRasterPos2i(x2, y2);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '2');
	glRasterPos2i(x3, y3);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '3');
	glRasterPos2i(x4, y4);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '4');
	glRasterPos2i(x5, y5);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '5');
	glRasterPos2i(x6, y6);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '6');

	glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	winWidth = newWidth;
	winHeight = newHeight;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
}
void main(int argc, char** argv)
{
	glutInit(&argc, argv); // initializare GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
	glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
	glutInitWindowSize(winWidth, winHeight); // dimensiunile ferestrei 
	glutCreateWindow("Poligoane"); // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara
	init(); // executa procedura de initializare
	glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
	glutDisplayFunc(desen1); // procedura desen este invocata ori de cate ori este nevoie
	glutReshapeFunc(reshapeFcn);
	glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}