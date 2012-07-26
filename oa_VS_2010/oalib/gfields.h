#ifndef GFIELDS_H
#define GFIELDS_H

/* Declarations for dynamic allocation */

#include "memory.h"
#include "galdef.h"

/*int *ivector(), **imatrix();*/

/* Definitions for Galois Fields */
namespace oa {
	void GF_set_fields();
	int GF_getfield(int q, GF* gf );
}

#endif
