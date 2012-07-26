#ifndef GALOIS_H
#define GALOIS_H

/* Declarations for dynamic allocation */

#include "memory.h"
#include "galdef.h"

/*int *ivector(), **imatrix();*/

/* Definitions for Galois Fields */
namespace oa {
	void GF_free(GF* gf );
	void GF_poly_prod(int p, int n, int* xton, int* p1, int* p2, int* prod );
	void GF_poly_sum(int p, int n, int* p1, int* p2, int* sum );
	int GF_poly2int( int p, int n, int* poly );
	void GF_print(GF* gf );
	int GF_ready(GF* gf, int p, int n, int* xton );
}

#endif
