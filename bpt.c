#include <stdio.h>
#include <stdlib.h>

#include "bpt.h"
#include "bezier.h"

BezierSurface *readBPT (FILE *bpt) {
	//read number of patches
	//read dimensions
	//for each patch
	//read it's coordinates and initialze a patch
	//join all patches in a surface
	//return
	
	int npatches, u, v, i, j;
	BezierPatch *bp;
	BezierSurface *bs = createBezierSurface ();
	point3d **patch;
	//reads the number of patches in the file
	fscanf (bpt, "%d", &npatches);
	printf ("%d\n", npatches);
	//gets u and v sizes of the patches
	fscanf (bpt, "%d %d", &u, &v);
	printf ("%d %d\n", u, v);
	
	while (!feof(bpt)) {
		patch = malloc (sizeof (point3d*) * u);
		for (i = 0 ; i < u ; i++) {
			patch[i] = malloc (sizeof (point3d) * v);
			for (j = 0 ; j < v ; j++) {
				fscanf (bpt, "%lf", &patch[i][j].x);
				fscanf (bpt, "%lf", &patch[i][j].y);
				fscanf (bpt, "%lf", &patch[i][j].z);
				printf ("%lf %lf %lf\n", patch[i][j].x, patch[i][j].y, patch[i][j].z);
			}
		}
		bp = createBezierPatch (patch, u, v);
		joinBezierSurface (bs, bp);
	}

	return bs;
}

