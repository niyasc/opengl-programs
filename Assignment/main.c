#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>

int px,py;
int scene=0;
struct Cordinates
{
	int x,y;
	struct Cordinates *next;
};
struct Cordinates *points=NULL,*rpoints=NULL;


void init(void)
{
	glClearColor(1.0,1.0,1.0,1.0);
	
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,800.0,0.0,600.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
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
	
void use_reverse_point(int x,int y)
{
	struct Cordinates *temp;
	if(rpoints==NULL)
	{
		struct Cordinates *new=(struct Cordinates *)malloc(sizeof(struct Cordinates));
		new->x=x;
		new->y=y;
		new->next=NULL;
		rpoints=new;
		temp=rpoints;
	}
	else
	{
		struct Cordinates *temp;
		struct Cordinates *new=(struct Cordinates *)malloc(sizeof(struct Cordinates));
		new->x=x;
		new->y=y;
		new->next=rpoints;
		rpoints=new;
	}
	glColor3f(1,0,0);
	temp=rpoints;
	if(temp->next!=NULL)
	{
	
		glBegin(GL_LINES);
			glVertex2i(rpoints->x,rpoints->y);
			glVertex2i(rpoints->next->x,rpoints->next->y);
		glEnd();
	}
	
	glFlush();
}	

void simulate_movement()
{
	//printf("in simulate movement");
	struct Cordinates *temp;
	
	temp=points;
	
	if(temp->next!=NULL)
	{
		glColor3f(1,1,1);
		/*glBegin(GL_LINES);
		glVertex2i(temp->x,temp->y);
		glVertex2i(temp->next->x,temp->next->y);
		glEnd();*/
		circle(px,py,10);
		glColor3f(0,0,0);
		circle(temp->next->x,temp->next->y,10);
		
		px=temp->next->x;
		py=temp->next->y;
		
		struct Cordinates *t=temp;
		points=temp->next;
		use_reverse_point(t->x,t->y);
		free(t);
		usleep(50000);
	}
	else
	{
		glColor3f(1,1,1);
		circle(px,py,10);
		free(temp);
		points=NULL;
		scene=2;
	}
	
	glFlush();
}

void simulate_reverse_movement()
{
	//printf("in simulate movement");
	struct Cordinates *temp;
	
	temp=rpoints;
	
	if(temp->next!=NULL)
	{
		glColor3f(1,1,1);
		glBegin(GL_LINES);
		glVertex2i(temp->x,temp->y);
		glVertex2i(temp->next->x,temp->next->y);
		glEnd();
		circle(px,py,10);
		glColor3f(0,0,0);
		circle(temp->next->x,temp->next->y,10);
		
		px=temp->next->x;
		py=temp->next->y;
		
		struct Cordinates *t=temp;
		rpoints=temp->next;
		//use_reverse_point(t->x,t->y);
		free(t);
		usleep(50000);
	}
	else
	{
		glColor3f(1,1,1);
		circle(px,py,10);
		free(temp);
		rpoints=NULL;
		scene=0;
	}
	
	glFlush();
}
	

void draw()
{
	switch(scene)
	{
		case 1: simulate_movement();
			break;
		case 2: simulate_reverse_movement();
	}
		
	glFlush();
}

void use_point(int x,int y)
{
	struct Cordinates *temp;
	if(points==NULL)
	{
		struct Cordinates *new=(struct Cordinates *)malloc(sizeof(struct Cordinates));
		new->x=x;
		new->y=y;
		new->next=NULL;
		points=new;
		temp=points;
	}
	else
	{
		struct Cordinates *temp;
		temp=points;
		while(temp->next!=NULL)
			temp=temp->next;
		struct Cordinates *new=(struct Cordinates *)malloc(sizeof(struct Cordinates));
		new->x=x;
		new->y=y;
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
	if(scene==0)
	{
		if(button==GLUT_LEFT_BUTTON&&state==GLUT_UP)
		{
			//printf("mouse up");
			scene=1;
		}
	}
	//printf("out of function mouse_clicked=%d\n",mouse_clicked);
	//printf("\n");
}

void mouse_move(int x,int y)
{
	if(x>=0&&x<=800&&y>=0&&y<=600)
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
