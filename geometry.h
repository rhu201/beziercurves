#ifndef __GEOMETRY__
#define __GEOMETRY__

typedef struct point_2d {
	double x;
	double y;
} point2d;

typedef struct point_3d {
	double x, y, z;
} point3d;

point2d *linearCombination (double a, point2d *p1, double b, point2d *p2);

void drawPolygon (point2d *pts, int n);

#endif
