#include <windows.h>
#include <gl/freeglut.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1800.0, 0.0, 900.0);
}
void desen(void)
{

    // segmentele
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 5.0, 0.0);
    glVertex2i(370 + 700, 30 + 250);
    glVertex2i(20 + 700, 380 + 250);
    glColor3f(0.0, 1.0, 5.0);
    glVertex2i(10 + 700, 10 + 250);
    glVertex2i(500 + 700, 500 + 250);
    glEnd();

    glPointSize(50.0);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(8.0, 0.0, 0.0);
    glVertex2i(900, 450);
    glEnd();

    // initiale
    glLineWidth(8.0);
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0);

    glVertex2i(500, 50);
    glVertex2i(550, 50);
    glVertex2i(500, 50);
    glVertex2i(500, 150);

    glVertex2i(600, 50);
    glVertex2i(625, 150);
    glVertex2i(625, 150);
    glVertex2i(650, 50);
    glVertex2i(650, 50);
    glVertex2i(675, 150);
    glVertex2i(675, 150);
    glVertex2i(700, 50);

    glVertex2i(800, 150);
    glVertex2i(750, 150);
    glVertex2i(750, 50);
    glVertex2i(750, 150);
    glVertex2i(800, 50);
    glVertex2i(750, 50);
    glVertex2i(800, 50);
    glVertex2i(800, 100);
    glVertex2i(800, 100);
    glVertex2i(750, 100);

    glEnd();

    glFlush();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1800, 900);
    glutCreateWindow("Puncte & Segmente");
    init();
    glClear(GL_COLOR_BUFFER_BIT);
    glutDisplayFunc(desen);
    glutMainLoop();
}