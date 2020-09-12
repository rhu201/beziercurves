#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "bezier.h"

BezierPath *createBezierPath (point2d *pts, int n) {
	BezierPath *b = malloc (sizeof (BezierPath));
	b->pts = malloc (sizeof (point2d) * n);
	b->npts = n;
	int i;

	for (i = 0 ; i < n ; i++) {
		b->pts[i] = pts[i];
	}
	
	b->next = NULL;
	
	return b;
}

void evaluateBezierPath (BezierPath *b, double t, point2d *out) {
	int i, j;
	point2d *aux = malloc (sizeof (point2d) * b->npts);

	for (i = 0 ; i < b->npts ; i++) {
		aux[i] = b->pts[i];		
	}
	for (j = 1 ; j < b->npts ; j++) {
		for (i = 0 ; i < b->npts - j ; i++) {
			aux[i].x = (1-t)*aux[i].x + t*aux[i+1].x;
			aux[i].y = (1-t)*aux[i].y + t*aux[i+1].y;
		}
	}

	*out = aux[0];

	free (aux);
}

void drawBezierPath (BezierPath *b, double step) {
	double i;
	point2d aux;

	glBegin (GL_LINE_STRIP);
	for (i = 0 ; i < 1 ; i += step) {
		evaluateBezierPath (b, i, &aux);
		glVertex2d (aux.x, aux.y);
	}
	glEnd ();
}

void joinBezierCurve (BezierCurve *b, BezierPath *p) {
	if (!b->head) {
		b->head = b->tail = p;
		return;
	}

	b->tail->next = p;
	b->tail = p;
}

BezierCurve *createBezierCurve (point2d *pts, int n) {
	/*int i;
	BezierCurve *b = malloc (sizeof (BezierCurve));
	b->head = b->tail = NULL;
	for (i = 0 ; i < n/3 ; i ++) {
		BezierPath * bp = createBezierPath (pts, 3);
		joinBezierCurve (b, bp);
		pts += 2;
	}
*/
//Original code, makes a single high-degree bezier curve

	BezierCurve *b = malloc (sizeof (BezierCurve));
	b->head = b->tail = createBezierPath (pts, n);

	return b;
}

void drawBezierCurve (BezierCurve *b, double step) {
	BezierPath *p = b->head;
	while (p) {
		drawBezierPath (p, step);
	//	glPointSize (5);
	//	glColor3f (0,1,0);
	//	glBegin(GL_POINTS);
	//	glVertex2d (p->p3.x, p->p3.y);
	//	glEnd();
	//	glColor3f (0,0,1);
		p = p->next;
	}
}

BezierPatch *createBezierPatch (point3d **pts, int u, int v) {
	BezierPatch *b = malloc (sizeof (BezierPatch));
//	b->pts = malloc (sizeof (point3d*) * u);
	b->pts = pts;

	/*
	for (i = 0 ; i < u ; i++) {
		b->pts[i] = malloc (sizeof (point3d) * v);
		for (j = 0 ; j < v ; j++) {
			b->pts[i][j] = pts[i][j];
		}
	}
	*/

	b->u = u;
	b->v = v;

	return b;
}

double choose (double n, double i) {
	if (i == 0) return 1;
	if (i > n - i) i = n - i;
	return n/i*choose(n-1, i-1);
}

double basis_func (int n, int i, double x) {
	return pow (x, i)*pow(1-x, i)*choose(n, i);
}

void evaluateBezierPatch (BezierPatch *b, double u, double v, point3d *out) {
	int i, j;
	for (i = 0 ; i < b->u ; i++) {
		for (j = 0 ; j < b->v ; j++) {
			out->x = b->pts[i][j].x*basis_func(b->u, i, u)*basis_func(b->v, j, v);
			out->y = b->pts[i][j].y*basis_func(b->u, i, u)*basis_func(b->v, j, v);
			out->z = b->pts[i][j].z*basis_func(b->u, i, u)*basis_func(b->v, j, v);
		}
	}
}

void drawBezierSurface (BezierSurface *b, double step) {
	double i, j;
	for (i = 0 ; i <= 1 ; i += step) {
		for (j = 0 ; j <= 1 ; j += step) {
			
		}
	}
}

BezierSurface *createBezierSurface () {
	BezierSurface *b = malloc (sizeof (BezierSurface));
	b->head = b->tail = NULL;

	return b;
}

void joinBezierSurface (BezierSurface *b, BezierPatch *bp) {

}
