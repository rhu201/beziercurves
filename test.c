#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#include "geometry.h"

#include "spline.c"
#include "bezier.h"
#include "bpt.h"

/* Functions. */
void Init(void);
void Reshape(int w, int h);
void Display(void);
void Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void DrawPoints(void);
void DrawLines();

/* Defines. */
#define MAXNPTS 200

/* Globals */
int winwidth, winheight;
int npts = 0;
point2d points[MAXNPTS];
int ok;
int flush = 1;

SplineCurve *s;
BezierCurve *b;
BezierPath *bp;

/* Functions */
void Init(){

	/* Select clearing color. */
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Reshape(int w, int h){
	winwidth  = w;
	winheight = h;

	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLsizei) w, 0, (GLsizei) h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Keyboard(unsigned char key, int x, int y){

	switch (key){
		case 27:
			exit(0);
			break;
		case 'q':
		case 'Q':
			exit(0);
			break;
		case 'v':
			ok = 1;
			flush = 1;
			s = createSplineCurve (points, npts);
			b =	createBezierCurve (points, npts);
			bp = createBezierPath (points, npts);
			break;
		case 'r':
			ok = 0;
			flush = 1;
			npts = 0;
	}
	glutPostRedisplay ();
}

void Mouse(int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN)
            {
                if (npts < MAXNPTS)
                {
				    points[npts].x = x;
                    points[npts].y = winheight-y;
				    printf("(%f,%f)\n", points[npts].x, points[npts].y);
                    npts++;
                }

                glutPostRedisplay();
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN)
            {
                npts = 0;
                glutPostRedisplay();
            }
            break;
        default:
            break;
    }
}

void DrawPoints()
{
	int i;

	glColor3f (0.0, 0.0, 0.0);
	glPointSize((GLdouble) 5);
	glBegin(GL_POINTS);
	for (i = 0; i < npts; i++)
		glVertex2d(points[i].x, points[i].y);
	glEnd();
}

void DrawLines()
{
	int i;

	glColor3f (0.6, 0.6, 0.6);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < npts; i++)
		glVertex2d(points[i].x, points[i].y);
	glEnd();
}

void drawXY () {
	glColor3f (0,0,0);
	glLineWidth (5);
	glBegin (GL_LINES);
		glVertex2d (50, -5);
		glVertex2d (50, 200);
		glVertex2d (-5, 5);
		glVertex2d (200, 5);
	glEnd ();
	glLineWidth (1);
}

void plotGraphSpline (Spline* s, double step, double r, double g, double b) {
	double i;
	glColor3f (r,g,b);
	glBegin (GL_LINE_STRIP);
	for (i = s->x[0] ; i < s->x[s->npts-1] ; i += step) {
	//	printf ("x %lf, %y %lf\n", i, splineComputa (s, step));
		glVertex2d (10*i+10, splineComputa (s, i));
	}
	glEnd ();
}

void Display(void){

	/* Clear buffers. */
	if (flush) {
		glClear(GL_COLOR_BUFFER_BIT);
		flush = 0;
	}
	
	DrawPoints ();

	if (!ok) goto a;

	DrawPoints ();

	glColor3f (0.6, 0.6, 0.6);
	drawPolygon (points, npts);

	glColor3f (1,0,0);
	drawSplineCurve (s, 0.001);	
	//drawBezierPath (bp, 0.001);

	//drawXY ();

	//plotGraphSpline (s->x, 0.01, 0, 1, 0);
	//plotGraphSpline (s->y, 0.01, 0, 0, 1);

	glColor3f (0,0,1);
	drawBezierCurve (b, 0.001);

	a:

	/* Draw. */
	glFlush();
	
}

int main(int argc, char** argv){

	//FILE* f = fopen ("teapot.bpt", "r");
	//readBPT (f);

	/* Call glut init functions. */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(512, 512); 
	glutCreateWindow("Test");
	Init();

	/* Call glut drawing functions. */
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutDisplayFunc(Display);


	glutMainLoop();
	return 0;
}
