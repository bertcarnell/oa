#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <cstdio>
#include <cstdlib>
#include "galois.h"

namespace oa {
	int bosecheck(int q, int ncol );
	int bose(GF* gf, int** A, int ncol );
	void itopoly(int n, int q, int d, int* coef );
	void polyeval(GF* gf, int d, int* poly, int arg, int* value );
	int bushcheck(int q, int str, int ncol);
	int bush(GF* gf, int** A, int str, int ncol);
	int addelkemp(GF* gf, int** A, int ncol );
	int bosebushcheck(int q, int p, int ncol);
	int bosebush(GF* gf, int** B, int ncol );
	int bosebushlcheck(int s, int p, int lam, int ncol);
	int bosebushl(GF* gf, int lam, int** B, int ncol );
}

#endif
