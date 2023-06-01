#include <windows.h> 
#include <gl/freeglut.h> 

int keybBackground, currentColor;

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

void desen(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLineWidth(2.0);
	glBegin(GL_LINES);
	if (currentColor == 0)
		glColor3f(0.2, 0.2, 0.2); 
	if (currentColor == 1)
		glColor3f(1.0, 1.0, 1.0);
	glVertex2i(370, 30);
	glVertex2i(20, 380);
	
	glVertex2i(10, 10);
	glVertex2i(500, 500);
	glEnd();

	glutPostRedisplay();
	glutSwapBuffers();
	glFlush(); 
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
}
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}
void main(int argc, char** argv)
{
	int menuMain, menuBackground,menuColor;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Exemplu meniu cu submeniuri");
	Initialize(keybBackground);
	glutDisplayFunc(desen);
	glutReshapeFunc(reshape);

	
	menuBackground = glutCreateMenu(Initialize);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	menuColor = glutCreateMenu(callback_Color);
	glutAddMenuEntry("Grey ", 0);
	glutAddMenuEntry("White ", 1);

	menuMain = glutCreateMenu(callback_Main);

	glutAddSubMenu("Culoare fundal ", menuBackground);
	glutAddSubMenu("Culoare primitive ", menuColor);
	glutAddMenuEntry("Iesire ", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	glutMainLoop();

}