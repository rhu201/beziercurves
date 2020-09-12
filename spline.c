#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "geometry.h"

/* Struct representando a Spline global
 * Cada Spline local s_i é dada por:
 * 		y[i] + b[i]*(x - x[i]) + c[i]*(x-x[i])^2 + d[i]*(x-x[i])^3
 * */
typedef struct _spli {
	double *x, *y;
	int npts;
	//O tamanho dos vetores b, c e d é npts-1
	double *b, *c, *d;
} Spline;

typedef struct _paspli {
	Spline *x, *y;
} SplineCurve;

Spline *splineConstruir (double *x, double *y, int n) {
	Spline *s = malloc (sizeof(Spline));
	double *b, *c, *d;
	double *h, *alpha, *l, *mu, *z;
	int i;

	b = malloc (sizeof(double) * n + 1);
	c = malloc (sizeof(double) * n + 1);
	d = malloc (sizeof(double) * n + 1);
	
	h = malloc (sizeof(double) * (n + 1));
	alpha = malloc (sizeof(double) * (n + 1));
	l = malloc (sizeof(double) * (n + 1));
	mu = malloc (sizeof(double) * (n + 1));
	z = malloc (sizeof(double) * (n + 1));

	for (i = 0 ; i < n ; i++) {
		h[i] = x[i+1] - x[i];
	}

	for (i = 1; i < n ; i++) {
		alpha[i] = (3/h[i])*(y[i+1]-y[i]) - (3/h[i-1])*(y[i] - y[i-1]);
	}

	l[0] = 1;
	mu[0] = z[0] = 0;

	for (i = 1; i < n ; i++) {
		l[i] = 2*(x[i+1]-x[i-1]) - h[i-1]*mu[i-1];
		mu[i] = h[i]/l[i];
		z[i] = (alpha[i] - h[i-1]*z[i-1])/l[i];
	}

	l[n] = 1;
	z[n] = 0;
	c[n] = 0;

	for (i = n-1 ; i >= 0 ; i--) {
		c[i] = z[i] - mu[i]*c[i+1];
		b[i] = ((y[i+1] - y[i])/h[i]) - (h[i]*(c[i+1]+2*c[i])/3);
		d[i] = (c[i+1]-c[i])/(3*h[i]);
	}

	s->b = b;
	s->c = c;
	s->d = d;
	s->x = x;
	s->y = y;
	
	s->npts = n;

	free (h);
	free (alpha);
	free (l);
	free (mu);
	free (z);

	return s;
}

double splineComputa (Spline *s, double x) {
	int i;
	double h;	

	for (i = 0 ; i < s->npts ; i++) {
		if (x >= s->x[i] && x <= s->x[i+1])
			break;
	}

	h = x - s->x[i];

	return s->y[i] + h*(s->b[i] + h*(s->c[i] + s->d[i]*h));
}

void splineDestroi (Spline *s) {
	free (s->x);
	free (s->y);
	free (s->b);
	free (s->c);
	free (s->d);

	free (s);
}

void splinePrint (Spline *s) {
	int i;
	
	for (i = 0 ; i < s->npts ; i++) {
		printf ("Para %lf <= x <= %lf:\n", s->x[i], s->x[i+1]);
		printf ("\t%lf + %lf(x - %lf) + %lf(x - %lf)^2 + %lf(x - %lf)^3\n", 
					s->y[i], s->b[i], s->x[i], s->c[i], s->x[i], s->d[i], s->x[i]);
	}
}

SplineCurve *createSplineCurve (point2d* pts, int n) {
	double *t = malloc (sizeof (double) * n);
	double *x = malloc (sizeof (double) * n);
	double *y = malloc (sizeof (double) * n);
	int i;
	SplineCurve *s = malloc (sizeof (SplineCurve));

	for (i = 0 ; i < n ; i++) {
		t[i] = i;
		x[i] = pts[i].x;
		y[i] = pts[i].y;
	}	

	s->x = splineConstruir (t, x, n);
	s->y = splineConstruir (t, y, n);

	return s;
}

void drawSplineCurve (SplineCurve *s, double step) {
	double i;

	glBegin (GL_LINE_STRIP);
	for (i = s->x->x[0] ; i < s->x->x[s->x->npts-1] ; i += step) {
		glVertex2f (splineComputa (s->x, i), splineComputa (s->y, i));
	}
	glEnd ();
}
