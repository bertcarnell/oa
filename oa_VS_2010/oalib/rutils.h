#ifndef RUTILS_H
#define RUTILS_H

#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "memory.h"
#include "runif.h"

namespace oa {
	void unifperm( int* pi, int q ) ; 
	int rankcomp( double** a, double** b );
	int findranks(int n, double* v, int* r );
	int doubcomp( double a, double b );
}

#endif
