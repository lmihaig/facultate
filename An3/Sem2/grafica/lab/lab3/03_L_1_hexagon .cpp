/*Hearn & Baker */
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <GL/freeglut.h>

const double TWO_PI = 6.2831853;

GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;
static GLfloat rotTheta = 0.0;

class scrPt 
{
public: 
	GLint x, y;
};

static void init (void)
{
	scrPt hexVertex;
	GLdouble hexTheta;
	GLint k;

	glClearColor (1.0, 1.0, 1.0, 1.0);
	regHex = glGenLists (1);
	glNewList (regHex, GL_COMPILE);
		glColor3f (1.0, 0.0, 0.0);
		glBegin (GL_POLYGON);
		for (k=0; k < 6; k++)
		{
			hexTheta = TWO_PI * k / 6;
			hexVertex.x = 150 + 100 * cos (hexTheta);
			hexVertex.y = 150 + 100 * sin (hexTheta);
			glVertex2i (hexVertex.x, hexVertex.y);
		}
		glEnd ( );
	glEndList ( );
}
void displayHex (void)
{
	glClear (GL_COLOR_BUFFER_BIT);

 
	glCallList (regHex);
	glPopMatrix ( );

 
	glFlush ( );
}

 

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glViewport (0, 0, (GLsizei) newWidth, (GLsizei) newHeight);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ( );
	gluOrtho2D (-320.0, 320.0, -320.0, 320.0);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ( );

	glClear (GL_COLOR_BUFFER_BIT);
}

 
void main (int argc, char **argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (150, 150);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Hexagon - utilizarea listelor de display");

	init ( );
	glutDisplayFunc (displayHex);
	glutReshapeFunc (winReshapeFcn);

	glutMainLoop ( );

}



