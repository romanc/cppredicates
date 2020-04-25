#ifndef ORIGINAL_PREDICATES_H
#define ORIGIANL_PREDICATES_H

extern "C" {
	void exactinit();

	double orient2d(double[2], double[2], double[2]);
	double incircle(double[2], double[2], double[2], double[2]);
	double orient3d(double[3], double[3], double[3], double[3]);
	double insphere(double[3], double[3], double[3], double[3], double[3]);

	double orient2dfast(double[2], double[2], double[2]);
	double incirclefast(double[2], double[2], double[2], double[2]);
	double orient3dfast(double[3], double[3], double[3], double[3]);
	double inspherefast(double[3], double[3], double[3], double[3], double[3]);
}

#endif

