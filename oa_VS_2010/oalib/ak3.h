#ifndef AK3_H
#define AK3_H

#include <cmath>
#include <cstdio>

#include "akconst.h"
#include "galdef.h"

namespace oa {
	int addelkemp3check(int q, int p, int ncol);
	int addelkemp3(GF* gf, int** A, int ncol );
}

#endif
