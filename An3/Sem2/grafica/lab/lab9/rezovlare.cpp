/* Deplasarea observatorului intr-o scena 3D
SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
Elemente de retinut:
- folosirea functiilor de desenare pentru a schita obiecte 3D
- schimbarea pozitiei observatorului se face in functia gluLookAt
- folosirea glutSpecialFunc si glutKeyboardFunc pentru interactiunea cu tastatura
*/

#include <gl/freeglut.h>
#include <math.h>
#include <iostream>
// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

int keybBackground = 1;
int currentColor = 1;

void Initialize(int key)
{

    switch (key)
    {
    case 0:
        glClearColor(0.0, 0.0, 0.0, 1.0);
        break;
    case 1:
        glClearColor(1, 0.0, 0.0, 0.0);
        keybBackground = 1;
        break;
    case 2:
        glClearColor(0.0, 1.0, 0.0, 0.0);
        keybBackground = 2;
        break;
    case 3:
        glClearColor(0.0, 0.0, 1.0, 0.0);
        keybBackground = 3;
        break;
    }
}

void callback_Main(int key)
{
    if (key == 0)
    {
        exit(0);
    }
}

void callback_Color(int key)
{
    currentColor = key;
    std::cout << currentColor;
}

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

void drawSnowMan()
{
    glPushMatrix();

    glColor3f(1.0f, 0.5f, 0.0f);
    glTranslatef(0.0f, 1.75f, 0.0f);
    glRotated(90, 1.0f, 0.0f, 0.0f);
    glutSolidCylinder(0.15f, 1.75f, 20, 20);
    glPopMatrix();

    glPushMatrix();

    switch (currentColor)
    {
    case 1:
        glColor3f(0.0f, 1.0f, 0.0f);
        break;
    case 2:
        glColor3f(1.0f, 1.0f, 0.0f);
        break;
    case 3:
        glColor3f(0.0f, 1.0f, 1.0f);
        break;
    }
    glTranslatef(0.0f, 1.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);
    glPopMatrix();
}

void renderScene(void)
{
    switch (keybBackground)
    {
    case 1:
        glClearColor(1.0f, 0.1f, 0.1f, 1.0f);
        break;
    case 2:
        glClearColor(0.3f, 1.0f, 0.3f, 1.0f);
        break;
    case 3:
        glClearColor(0.3f, 0.1f, 0.8f, 1.0f);
        break;
    }
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();
    // Set the camera
    gluLookAt(x, 1.0f, z,
              x + lx, 1.0f, z + lz,
              0.0f, 1.0f, 0.0f);

    // Draw ground
    glColor3f(0.1f, 0.9f, 0.1f);
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

void processNormalKeys(unsigned char key, int xxx, int yyyy)
{
    float fraction = 0.1f;

    switch (key)
    {
    case 'l':
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;

    case 'a':
        angle -= 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case 'd':
        angle += 0.01f;
        lx = sin(angle);
        lz = -cos(angle);
        break;
    case 'w':
        x += lx * fraction;
        z += lz * fraction;
        break;
    case 's':
        x -= lx * fraction;
        z -= lz * fraction;
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
    int menuMain, menuBackground, menuColor;

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Scena de primavara");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    menuBackground = glutCreateMenu(Initialize);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Blue", 3);

    menuColor = glutCreateMenu(callback_Color);
    glutAddMenuEntry("ala", 0);
    glutAddMenuEntry("bala", 1);

    menuMain = glutCreateMenu(callback_Main);

    glutAddSubMenu("Culoare fundal ", menuBackground);
    glutAddSubMenu("Culoare frunze ", menuColor);
    glutAddMenuEntry("Iesire ", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}
