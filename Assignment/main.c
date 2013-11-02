#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

bool mouse_clicked;
int px,py;
int status=0;
struct Cord
{
	int x,y;
	int flag;//flag=0 for points not drawn,flag=1 for points drawn
	struct Cord *next;
};
struct Cord *points=NULL;

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
void circle(int x,int y,int r)
{
	float i;
	glBegin(GL_LINES);
	for(i=0;i<360;i+=0.5)
	{
		glVertex2i(x,y);
		glVertex2f(x+r*cosf(i),y+r*sinf(i));
	}
	glEnd();
}
		

void simulate_movement()
{
	//printf("in simulate movement");
	struct Cord *temp;
	
	temp=points;
	
	if(temp->next!=NULL)
	{
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex2i(temp->x,temp->y);
		glVertex2i(temp->next->x,temp->next->y);
		glEnd();
		glColor3f(1,1,1);
		circle(px,py,10);
		glColor3f(0,0,0);
		circle(temp->next->x,temp->next->y,10);
		
		px=temp->next->x;
		py=temp->next->y;
		
		struct Cord *t=temp;
		points=temp->next;
		free(t);
		usleep(30000);
	}
	else
	{
		glColor3f(1,1,1);
		circle(px,py,10);
		free(temp);
		points=NULL;
		status=0;
	}
	
	glFlush();
}
	

void draw()
{
	switch(status)
	{
		case 0: initialize();
			break;
		case 1: simulate_movement();
			break;
	}
		
	glFlush();
}

void use_point(int x,int y)
{
	struct Cord *temp;
	if(points==NULL)
	{
		struct Cord *new=(struct Cord *)malloc(sizeof(struct Cord*));
		new->x=x;
		new->y=y;
		new->flag=0;
		new->next=NULL;
		points=new;
		temp=points;
	}
	else
	{
		struct Cord *temp;
		temp=points;
		while(temp->next!=NULL)
			temp=temp->next;
		struct Cord *new=(struct Cord *)malloc(sizeof(struct Cord*));
		new->x=x;
		new->y=y;
		new->flag=0;
		new->next=NULL;
		temp->next=new;
	}
	glColor3f(1,0,0);
	temp=points;
	if(temp->next!=NULL)
	{
		while(temp->next->next!=NULL)
			temp=temp->next;
	
		glBegin(GL_LINES);
			glVertex2i(temp->x,temp->y);
			glVertex2i(x,y);
		glEnd();
	}
	
	glFlush();
}

void mouse(GLint button,GLint state,GLint x,GLint y)
{
	//printf("mouse event");
	if(status==0)
	{
		if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
		{
			//printf("mouse down");
			mouse_clicked=true;
		}
		else if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP)
		{
			//printf("mouse up");
			mouse_clicked=false;
			status=1;
		}
	}
	//printf("out of function mouse_clicked=%d\n",mouse_clicked);
	//printf("\n");
}

void mouse_move(int x,int y)
{
	if(y<500)
		use_point(x,600-y);
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
	glutMouseFunc(mouse);
	glutMotionFunc(mouse_move);
	glutMainLoop();
}
