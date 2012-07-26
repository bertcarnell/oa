#ifndef AKN_H
#define AKN_H

#include <cmath>
#include <cstdio>

#include "akconst.h"
#include "galdef.h"
#include "primes.h"

namespace oa {
	int addelkempncheck(int q, int p, int akn, int ncol  );
	int addelkempn(GF* gf, int akn, int** A, int ncol );
}

#endif
