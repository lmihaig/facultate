/* Deplasarea observatorului intr-o scena 3D
SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
Elemente de retinut:
- folosirea functiilor de desenare pentru a schita obiecte 3D
- schimbarea pozitiei observatorului se face in functia gluLookAt
- folosirea glutSpecialFunc si glutKeyboardFunc pentru interactiunea cu tastatura
*/

#include <gl/freeglut.h>
#include <math.h>
// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

GLfloat rosu[] = {1.0, 0.0, 0.0, 1.0};
GLfloat alb[] = {1.0, 1.0, 1.0, 0.0};
GLfloat galben[] = {1.0, 1.0, 0.0, 0.0};

GLfloat negru[] = {0.0, 0.0, 0.0, 0.0};

void drawSnowMan()
{
    GLfloat pozitial0[] = {1.0, 5.0, 3.0, 0.0};

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, pozitial0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, alb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, galben);
    glLightfv(GL_LIGHT0, GL_SPECULAR, rosu);

    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw Body
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);

    // Draw Head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

    // Draw Eyes
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, negru);
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    // Draw Nose
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, rosu);
    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
}

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(x, 1.0f, z,
              x + lx, 1.0f, z + lz,
              0.0f, 1.0f, 0.0f);

    // Draw ground
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, alb);
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    // Draw 36 SnowMen
    for (int i = -3; i < 3; i++)
        for (int j = -3; j < 3; j++)
        {
            glPushMatrix();
            glTranslatef(i * 10.0, 0, j * 10.0);
            drawSnowMan();
            glPopMatrix();
        }
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'l':
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    }
    if (key == 27)
        exit(0);
}

void processSpecialKeys(int key, int xx, int yy)
{

    float fraction = 0.1f;

    switch (key)
    {
    case GLUT_KEY_LEFT:
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case GLUT_KEY_UP:
        x += lx * fraction;
        z += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        x -= lx * fraction;
        z -= lz * fraction;
        break;
    }
}

int main(int argc, char **argv)
{
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Scena 3D cu oameni de zapada");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
