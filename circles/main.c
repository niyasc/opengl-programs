#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

struct Circle
{
	float x,y;
	float r;
	float color[3];
	int x_dir,y_dir;
}c[4];

void set_dir(int);
void init(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,800.0,0.0,600.0);
	
	int i;
	for(i=0;i<4;i++)
	{
		do
		{
			c[i].x=(float)(random()%800);
			c[i].y=(float)(random()%600);
			
		}while((c[i].x<50)||(c[i].y<50)||(c[i].x>750)||(c[i].y>550));
		

		
		
		printf("\n%f %f\n",c[i].x,c[i].y);
		c[i].r=50;
		int j;
		for(j=0;j<3;j++)
		{
			c[i].color[j]=1;
		}
		set_dir(i);
			
	}
}

void set_dir( int i)
{
	switch(random()%8)
	{
	case 0: c[i].x_dir=-1;
		c[i].y_dir=-1;
		break;
	case 1:	c[i].x_dir=-1;
		c[i].y_dir=0;
		break;
	case 2:	c[i].x_dir=-1;
		c[i].y_dir=1;
		break;
	case 3:	c[i].x_dir=0;
		c[i].y_dir=-1;
		break;
	case 4:	c[i].x_dir=0;
		c[i].y_dir=1;
		break;
	case 5:	c[i].x_dir=1;
		c[i].y_dir=-1;
		break;
	case 6:	c[i].x_dir=1;
		c[i].y_dir=0;
		break;
	case 7:	c[i].x_dir=1;
		c[i].y_dir=1;
		break;
	}
}
void line(float x1,float y1,float x2,float y2)
{
	
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
}

void circle(float x,float y,int r)
{
	int i;
	float tx,ty;
	glBegin(GL_POINTS);
		for(i=0;i<360;i++)
		{
			glVertex2f(x+r*cos(i),y+r*sin(i));
		}
	glEnd();
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i;
	for(i=0;i<4;i++)
	{
		glColor3f(c[i].color[0],c[i].color[1],c[i].color[2]);
		circle(c[i].x,c[i].y,c[i].r);
	}
	
	glFlush();
}

void anim()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i;
	for(i=0;i<4;i++)
	{
		c[i].x+=c[i].x_dir;
		c[i].y+=c[i].y_dir;
		while((c[i].x<50)||(c[i].y<50)||(c[i].x>750)||(c[i].y>550))
		{
			set_dir(i);
			c[i].x+=c[i].x_dir;
			c[i].y+=c[i].y_dir;
		}
		glColor3f(c[i].color[0],c[i].color[1],c[i].color[2]);
		circle(c[i].x,c[i].y,c[i].r);
	}
	usleep(5000);
	glFlush();
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(50,100);
	glutInitWindowSize(800,600);
	glutCreateWindow("Moving Circles");
	
	init();
	glutDisplayFunc(draw);
	glutIdleFunc(anim);
	glutMainLoop();
}
