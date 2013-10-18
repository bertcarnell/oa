#ifndef RUTILS_H
#define RUTILS_H

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "memory.h"
#include "runif.h"

namespace oa {
	void unifperm( int* pi, int q ) ; 
	int rankcomp( double** a, double** b );
	int findranks(int n, double* v, int* r );
	int doubcomp( double a, double b );
	void doubleArrayToSingle(int ** A, int * _A, int nrows, int ncols);
	bool dotProduct(std::vector<int> A, int nrows, int ncols);
}

#endif
