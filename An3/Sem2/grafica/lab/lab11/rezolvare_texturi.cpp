
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "SOIL.h"

GLfloat texpts[2][2][2] = {{{1.0, 1.0}, {1.0, 0.0}},
                           {{0.0, 1.0}, {0.0, 0.0}}};

#define imageWidth 64
#define imageHeight 64
GLubyte image[3 * imageWidth * imageHeight];
GLuint texture1;

void LoadTexture(void)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;
    unsigned char *image = SOIL_load_image("dog.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // SOIL_free_image_data(image);
    // glBindTexture(GL_TEXTURE_2D, 0);
}

void LoadTexture2(void)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height;
    unsigned char *image = SOIL_load_image("cat.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    // SOIL_free_image_data(image);
    // glBindTexture(GL_TEXTURE_2D, 0);
}

void init(void)
{
    glClearColor(0.6, 0.9, 0.95, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4, 0.3, 0.1);

    glEnable(GL_TEXTURE_2D);
    LoadTexture();

    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glColor3f(1.0, 0.1, 0.1);
    glVertex3f(-2.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glColor3f(0.1, 1.0, 0.1);
    glVertex3f(-2.0, 1.0, 0.0);
    glTexCoord2f(0.0, 0.0);
    glColor3f(1.0, 1.0, 0.1);
    glVertex3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glColor3f(0.0, 0.1, 1.0);
    glVertex3f(0.0, -1.0, 0.0);
    glEnd();

    LoadTexture2();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(2.0, -1.0, 0.0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(2.0, 1.0, 0.0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(4.0, 1.0, 0.0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(4.0, -1.0, 0.0);
    glEnd();
    glFlush();
}
void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluOrtho2D(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w,
                   4.0 * (GLfloat)h / (GLfloat)w);
    else
        gluOrtho2D(-4.0 * (GLfloat)w / (GLfloat)h,
                   4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
