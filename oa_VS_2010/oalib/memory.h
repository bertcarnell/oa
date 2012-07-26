#ifndef MEMORY_H
#define MEMORY_H

//#include <malloc.h>
#include <cstdio>

namespace oa {
	int **imatrix(int nrl, int nrh, int ncl, int nch);
	int *ivector(int nl, int nh);
	void free_imatrix(int** m, int nrl, int nrh, int ncl, int nch);
	void free_ivector(int* v, int nl, int nh);
	double **dmatrix(int nrl, int nrh, int ncl, int nch);
	double *dvector(int nl, int nh);
	void free_dmatrix(double** m, int nrl, int nrh, int ncl, int nch);
	void free_dvector(double* v, int nl, int nh);
	int grow_imatrix_byrows(int*** imat, int oldrowsize, int newrowsize, int colsize );
}

#endif