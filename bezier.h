#ifndef __BEZIER__
#define __BEZIER__

#include "geometry.h"

typedef struct _bezierCubic {
	struct _bezierCubic *next;
	point2d *pts;
	int npts;
} BezierPath;

typedef struct _bezier {
	BezierPath *head, *tail;
} BezierCurve;

typedef struct _bPatch {
	struct _bPatch *next;
	point3d **pts;
	int u, v;
} BezierPatch;

typedef struct _bSurface {
	BezierPatch *head, *tail;
} BezierSurface;

/* Creates a bezier path using degree elevation to turn the curve into a cubic if needed */
BezierPath *createBezierPath (point2d *pts, int n);

void evaluateBezierPath (BezierPath *b, double t, point2d *out);

void drawBezierPath (BezierPath *b, double step);

void joinBezierCurve (BezierCurve *b, BezierPath *p);

BezierCurve *createBezierCurve (point2d *pts, int n);

void drawBezierCurve (BezierCurve *b, double step);

BezierPatch *createBezierPatch (point3d **pts, int u, int v);

BezierSurface *createBezierSurface ();

void joinBezierSurface (BezierSurface *b, BezierPatch *bp);

void evaluateBezierPatch (BezierPatch *b, double u, double v, point3d *out);

void drawBezierSurface (BezierSurface *b, double step);
#endif
