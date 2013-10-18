#ifndef RUNIF_H
#define RUNIF_H

#include <cstdio>
#include <cmath>

namespace oa {
	int mod( int a, int b );
	int seedok(int is, int js, int ks, int ls ); 
	void seed(int is, int js, int ks, int ls );
	void runif (double *x, int n);
	void ranums(double *x, int n);
}

#endif
