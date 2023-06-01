// TRIUNGHI ROTIT / STATIC

#include <windows.h>
#include <time.h>
#include <gl/freeglut.h>
double i = 0.0;
double j = 0.0;
double k = 0.0;
double alpha = 1.0;

void delay(int msec)
{
    clock_t goal = msec + clock();
    while (goal > clock())
        ;
}

/*

void init (void)  // initializare fereastra de vizualizare
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity (  );

    glMatrixMode (GL_PROJECTION); // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D (-800.0, 800.0, -600.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
    glClear (GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare

}



void rotireTriunghi (void)
{
    glClear(GL_COLOR_BUFFER_BIT);


    // TRIUNGHIUL ORIGINAL
    glLineWidth(6.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glBegin (GL_TRIANGLES);
    glColor3f (0,0,1);
    glVertex2f(100,100);
    glColor3f (0,1,0);
    glVertex2f(500,100);
    glColor3f (1,0,0);
    glVertex2f(300,400);
    glEnd( );

    // CENTRUL DE GREUTATE
    glColor3f(0,0,0);
    glPointSize(10);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glVertex2f(300,200);
    glEnd( );

    // APLICAREA TRANSFORMARII ASUPRA TRIUNGHIULUI

    glPushMatrix ( );
    glTranslated(i,200,0);
    glRotated(j, 0, 0, 1);
    glScalef(i * 0.01, i* 0.02, 0.0);
    glTranslated(-300,-150,0);

    glBegin (GL_TRIANGLES);
    glColor3f (0,0,1);
    glVertex2f(100,100);
    glColor3f (0,1,0);
    glVertex2f(500,100);
    glColor3f (1,0,0);
    glVertex2f(300,400);
    glEnd( );
    glPopMatrix ( );


    glFlush ( );
    delay(20);

}



void miscad(void)
{
    i = i + alpha;
    if (i > 750.0)
        alpha = -1.0;
    else if (i < 0.0)
        alpha = 1.0;
    j = j + 15.0;

    glutPostRedisplay();
}

void miscas(void)
{

    i = i + alpha;
    if (i < 0.0)
        alpha = 1.0;
    else if (i > 750.0)
        alpha = -1.0;
    j = j + 15.0;

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

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv); // initializare GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
    glutInitWindowPosition(100, 100); // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
    glutInitWindowSize(1200, 800); // dimensiunile ferestrei
    glutCreateWindow("Triunghi rotit in jurul centrului de greutate"); // creeaza fereastra
    init();
    glutDisplayFunc(rotireTriunghi); // procedura desen este invocata ori de cate ori este nevoie
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop(); // ultima instructiune a programului, asteapta (eventuale) noi date de intrare

}

*/

#include <math.h>
const double TWO_PI = 3.141592 * 2;

GLsizei winWidth = 500, winHeight = 500;
GLuint regHex;
static GLfloat rotTheta = 0.0;

class scrPt
{
public:
    GLint x, y;
};

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
}
void deseneazaScena(void)
{

    scrPt hexVertex;
    GLdouble hexTheta;
    GLint k;

    glClearColor(1.0, 1.0, 1.0, 1.0);
    regHex = glGenLists(1);
    glNewList(regHex, GL_COMPILE);
    glColor3f(0.9, 0.1, 0.6);
    glBegin(GL_POLYGON);
    for (k = 0; k < 5; k++)
    {
        hexTheta = TWO_PI * k / 5;
        hexVertex.x = 30 * cos(hexTheta);
        hexVertex.y = 30 * sin(hexTheta);
        glVertex2i(hexVertex.x, hexVertex.y);
    }
    glEnd();
    glEndList();

    glClear(GL_COLOR_BUFFER_BIT);
    // axa de rostogolire in afara transformarii
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2i(0, 0);
    glVertex2i(1000, 1000);
    glEnd();
    // patratul
    glPushMatrix();
    glTranslated(i, i, 0.0);
    glPushMatrix();
    glRotated(j, 0.0, 0.0, 1.0);
    glScalef(i * 0.01, i * 0.01, 0);

    glCallList(regHex);

    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
    glFlush();
    delay(20);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0, 780.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void miscad(void)
{
    i = i + alpha;
    if (i > 750.0)
        alpha = -1.0;
    else if (i < 0.0)

        alpha = 1.0;
    j = j + 15.0;

    glutPostRedisplay();
}

void miscas(void)
{
    i = i + alpha;
    if (i < 0.0)
        alpha = 1.0;
    else if (i > 750.0)
        alpha = -1.0;
    j = j + 15.0;

    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            alpha = -1.0;
        glutIdleFunc(miscas);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            alpha = 1.0;
        glutIdleFunc(miscad);
        break;
    default:
        break;
    }
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Patrat care se rostogoleste");
    init();
    glutDisplayFunc(deseneazaScena);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();
}