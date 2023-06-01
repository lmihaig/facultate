/* Obiecte 3D. Transformarea de vizualizare. Transformarea de proiectie.
Elemente de noutate:
- functia pentru vizualizare gluLookAt
- functii pentru proiectii (glOrtho, glFrustum, gluPerspective)
*/

#include <windows.h>
#include <gl/freeglut.h>

GLint winWidth = 600, winHeight = 600;
GLfloat x0 = 6.0, y0 = 9.0, z0 = 10.0; // pozitia observatorului
GLfloat xref = 0.0, yref = 0.0, zref = 0.0; // punctul de referinta --> spre care se uita observatorul
GLfloat Vx = 0.0, Vy = 0.0, Vz = 1.0; // "verticala din planul de vizualizare" // GLfloat Vx = 12.0, Vy = 18.0, Vz = 21.0;

GLfloat xwMin = -20.0, ywMin = -20.0, xwMax = 20.0, ywMax = 20.0;
GLfloat dnear = 0.1, dfar = 400.0, fov = 90, aspect = 1.0;

void init (void)
{
	glClearColor (1.0, 1.0, 1.0, 0.0);

	// este generata matricea de vizualizare
	glMatrixMode (GL_MODELVIEW);
	gluLookAt (x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

	// este generata matricea de proiectie
	glMatrixMode (GL_PROJECTION);
	//glOrtho (xwMin, xwMax, ywMin, ywMax, dnear, dfar); // proiectie ortogonala
	// glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar); // proiectie perspectiva
	gluPerspective(fov, aspect, dnear, dfar); // proiectie perspectiva
}

void displayFcn (void)
{
	glClear (GL_COLOR_BUFFER_BIT);
    // sfera
	glColor3f (0.0, 0.0, 1.0);
    glutWireSphere (8.0, 100, 10);
	// con
	glColor3f (1.0, 0.0, 0.0);
	glPushMatrix ( );
	 glTranslatef (-15.0, 4.0, -20.0);
	//glScaled (2.2, 2.2, 2.2);
	glutWireCone (5.0, 10.0, 50, 70);
	glPopMatrix ( );
    // tor
	glColor3f (0.0, 1.0, 0.0);
	glPushMatrix ( );
    glTranslatef (-5.0, -10.0, -15.0);
    glutWireTorus (3.0, 7.0, 40, 60);
	glPopMatrix ( );
	// ceainic
	glColor3f (1.0, 0.0, 1.0);
	glPushMatrix ( );
	glTranslatef (-5.0, 0.0, 0.0);
	glutWireTeapot (2.0);
	glPopMatrix ( );
    // cilindru
	glColor3d (0.2, 0.0, 0.6);
	GLUquadricObj *cylinder;
	glPushMatrix ( );
	glTranslatef (-15.0, 10.0, -18.0);
	cylinder = gluNewQuadric ( );
	gluQuadricDrawStyle (cylinder, GLU_SILHOUETTE);
	gluCylinder (cylinder, 3.0, 3.0, 5.0, 40, 20);
	glPopMatrix ( );
	// axele
	glColor3f (0.0, 0.0, 0.0);
	// glLineWidth (1.5);
	glBegin (GL_LINES);
	glVertex3i (0, 0, 0);
	glVertex3i (20, 0, 0);
	glVertex3i (0, 0, 0);
	glVertex3i (0, 20, 0);
	glVertex3i (0, 0, 0);
	glVertex3i (0, 0, 20);
	glEnd ( );

	glFlush ( );
}

void main (int argc, char** argv)
{
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition (50, 50);
	glutInitWindowSize (winWidth, winHeight);
	glutCreateWindow ("Obiecte 3D");

	init ( );
	glutDisplayFunc (displayFcn);
	glutMainLoop ( );
}


