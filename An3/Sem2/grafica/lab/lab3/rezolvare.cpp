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

    glFlush(); // proceseaza procedurile OpenGL cat mai rapid
}

typedef struct
{
    float i;
    float j;
    float k;
} vect;

vect produs_vect(vect a, vect b)
{
    vect r = {
        a.j * b.k - a.k * b.j,
        -a.i * b.k + a.k * b.i,
        a.i * b.j - a.j * b.i,
    };
    return r;
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);                       // initializare GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // se utilizeaza un singur buffer | modul de colorare RedGreenBlue (= default)
    glutInitWindowPosition(100, 100);            // pozitia initiala a ferestrei de vizualizare (in coordonate ecran)
    glutInitWindowSize(800, 600);                // dimensiunile ferestrei
    glutCreateWindow("lab 3");                   // creeaza fereastra, indicand numele ferestrei de vizualizare - apare in partea superioara

    // ex 1
    vect a = {1, 2, 3};
    vect b = {-1, -2, -3};

    vect r = produs_vect(a, b);
    std::cout << r.i << " " << r.j << " " << r.k;

    init();                       // executa procedura de initializare
    glClear(GL_COLOR_BUFFER_BIT); // reprezentare si colorare fereastra de vizualizare
    glutDisplayFunc(desen);       // procedura desen este invocata ori de cate ori este nevoie
    glutMainLoop();               // ultima instructiune a programului, asteapta (eventuale) noi date de intrare
}