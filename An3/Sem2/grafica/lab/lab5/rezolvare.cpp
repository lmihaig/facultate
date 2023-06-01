#include <windows.h>
#include <gl/freeglut.h>

GLint winWidth = 600, winHeight = 600;
GLfloat xx0 = 5, yy0 = 5, zz0 = 5;
GLfloat xref = 3.0, yref = 1.0, zref = 4.0;
GLfloat Vx = 8.0, Vy = 0.0, Vz = -8.0;

int p1[] = {-1, 4, 3};
int p2[] = {-1, 4, 5};
int p3[] = {-1, 0, 1};
int p4[] = {-1, 0, 5};
int p5[] = {-1, 2.27, 2.62};

GLfloat xwMin = -10.0, ywMin = -10.0, xwMax = 10.0, ywMax = 10.0;

GLfloat dnear = 0.0, dfar = 20.0;

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(xx0, yy0, zz0, xref, yref, zref, Vx, Vy, Vz);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void desen(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);
    glLineWidth(6.0);
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3iv(p1);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3iv(p2);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3iv(p4);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3iv(p3);
    glEnd();

    glPointSize(10);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex3iv(p5);
    glEnd();

    glutPostRedisplay();

    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            xx0 = 5, yy0 = 5, zz0 = 5;
        init();
        desen();
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            xx0 = -2, yy0 = 7, zz0 = 5;
        init();
        desen();
        break;
    }
}
void reshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0, 0, newWidth, newHeight);

    winWidth = newWidth;
    winHeight = newHeight;
}
void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Poligoane in context 3D. Fata si spatele unui poligon");

    init();
    glutMouseFunc(mouse);
    glutDisplayFunc(desen);
    glutMainLoop();
}
