#include <GL/glut.h>

#include "geometry.h"

point2d *linearCombination (double a, point2d *p1, double b, point2d *p2) {
	point2d *out = malloc (sizeof(point2d));
	out->x = a*p1->x + b*p2->x;
	out->y = a*p1->y + b*p2->x;

	return out;
}

void drawPolygon (point2d *pts, int n) {
	int i;
	glColor3f (0.6, 0.6, 0.6);
	glBegin (GL_LINE_STRIP);
	for (i = 0 ; i < n ; i++) {
		glVertex2f (pts[i].x, pts[i].y);
	}
	glEnd ();
}


