#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

int status=0;

void init(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
	
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,800.0,0.0,600.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
}

void initialize()
{
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
		glVertex2i(0,0);
		glVertex2i(800,0);
		glVertex2i(800,90);
		glVertex2i(0,90);
	glEnd();
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
		glVertex2i(0,90);
		glVertex2i(800,90);
		glVertex2i(800,100);
		glVertex2i(0,100);
	glEnd();
}

void draw()
{
	switch(status)
	{
		case 0: initialize();
			break;
	}
		
	glFlush();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Ball movement simulation");
	
	init();
	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutMainLoop();
}
