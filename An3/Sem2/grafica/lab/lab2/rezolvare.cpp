#include <windows.h>     // sunt mentionate fisiere (biblioteci) care urmeaza sa fie incluse
#include <gl/freeglut.h> // nu trebuie uitat freeglut.h (sau glut.h sau gl.h & glu.h)
#include <tuple>
#include <string>
#include <iostream>

float ex2x1 = 100, ex2y1 = 300, ex2x2 = 200, ex2y2 = 400;
float ex3a = -1, ex3b = 1, ex3c = 0;

float pct1x = 50, pct1y = 300;
float pct2x = 300, pct2y = 500;
float pct3x = 300, pct3y = 100;

void init(void) // initializare fereastra de vizualizare
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // precizeaza culoarea de fond a ferestrei de vizualizare

    glMatrixMode(GL_PROJECTION);        // se precizeaza este vorba de o reprezentare 2D, realizata prin proiectie ortogonala
    gluOrtho2D(0.0, 800.0, 0.0, 600.0); // sunt indicate coordonatele extreme ale ferestrei de vizualizare
}
void desen(void) // procedura desenare
{

    // segmentele
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0); // culoarea primului segment: rosu
    glVertex2i(100, 100);
    glVertex2i(100, 200);
    glVertex2i(200, 200);
    glVertex2i(200, 100);
    glVertex2i(100, 100);

    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0); // culoarea primului segment: rosu
    glVertex2i(150, 150);
    glVertex2i(150, 250);
    glVertex2i(250, 250);
    glVertex2i(250, 150);
    glVertex2i(150, 150);

    glEnd();

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0); // culoarea primului segment: rosu
    glVertex2i(100, 100);
    glVertex2i(150, 150);

    glVertex2i(100, 200);
    glVertex2i(150, 250);

    glVertex2i(200, 200);
    glVertex2i(250, 250);

    glVertex2i(200, 100);
    glVertex2i(250, 150);

    glEnd();

    glPointSize(10.0);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(100, 100);

    glColor3f(1.0, 1.0, 0.0);
    glVertex2i(100, 200);

    glColor3f(0.8, 0.8, 0.8);
    glVertex2i(200, 200);

    glColor3f(0.0, 1.0, 1.0);
    glVertex2i(200, 100);

    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(150, 150);

    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(150, 250);

    glColor3f(1.0, 0.0, 1.0);
    glVertex2i(250, 250);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(250, 150);
    glEnd();

    // ex2
    glBegin(GL_POINTS);
    glColor3f(0.3, 0.5, 0.3);
    glVertex2i(ex2x1, ex2y1);
    glVertex2i(ex2x2, ex2y2);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0); // culoarea primului segment: rosu
    glVertex2i(ex2x1, ex2y1);
    glVertex2i(ex2x2, ex2y2);

    glEnd();

    // ex 3
    float xa = 0;
    float xb = 800;
    float ya = (-ex3a * xa - ex3c) / ex3b;
    float yb = (-ex3a * xb - ex3c) / ex3b;

    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 0.0);
    glVertex2i(xa, ya);
    glVertex2i(xb, yb);
    glEnd();

    glBegin(GL_POINTS);
    glColor3f(0.3, 0.1, 0.5);
    glVertex2i(pct1x, pct1y);
    glVertex2i(pct2x, pct2y);
    glVertex2i(pct3x, pct3y);

    glEnd();

    glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

std::tuple<float, float, float> ec_dreptei(float xa, float ya, float xb, float yb)
{
    float a = ya - yb;
    float b = xb - xa;
    float c = (xa - xb) * ya + (yb - ya) * xa;

    return std::make_tuple(a, b, c);
}

float f(float a, float b, float c, float x, float y)
{
    return a * x + b * y + c;
}
bool verifica_pct(float a, float b, float c, float xa, float ya, float xb, float yb)
{
    return f(a, b, c, xa, ya) * f(a, b, c, xb, yb) < 0;
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // initializare GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
    glutInitWindowPosition(100, 100);            // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
    glutInitWindowSize(800, 600);                // dimensiunile ferestrei
    glutCreateWindow("Puncte & Segmente");       // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

    // ex 2
    float a, b, c;
    std::tie(a, b, c) = ec_dreptei(ex2x1, ex2y1, ex2x2, ex2y2);
    printf("%.3fx + %.3fy + %.3f = 0\n", a, b, c);

    // ex 3
    std::cout << verifica_pct(ex3a, ex3b, ex3c, pct1x, pct1y, pct2x, pct2y) << std::endl;
    std::cout << verifica_pct(ex3a, ex3b, ex3c, pct1x, pct1y, pct3x, pct3y) << std::endl;

    init();                       // executa procedura de initializare
    glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
    glutDisplayFunc(desen);       // procedura desen este invocata ori de cate ori este nevoie
    glutMainLoop();               // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}