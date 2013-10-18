/*

  These programs construct and manipulate orthogonal 
arrays.  They were prepared by

    Art Owen
    Department of Statistics
    Sequoia Hall
    Stanford CA 94305

  They may be freely used and shared.  This code comes
with no warranty of any kind.  Use it at your own
risk.

  I thank the Semiconductor Research Corporation and
the National Science Foundation for supporting this
work.

*/

#include "ak3.h"
#include "galois.h"
#include "gfields.h"
#include "defines.h"
#include "rutils.h"

using namespace oa;

/* n=2*q*q*q
 * no restriction on ncol in original code... Assumed 0 < ncol <= 2*q*q + 2*q +1
 * A=length(n*ncol) */
extern "C" {
int addelkemp3_main(int* _q, int* _ncol, int * _n, int * _A)
{
	int q = *_q;
	int ncol = *_ncol;
	GF gf;
	int ** A;
	int n = *_n;

	if (n != 2*q*q*q)
	{
		ERROR_MACRO("n must be equal to 2*q*q*q\n");
		return(EXIT_FAILURE);
	}

	if (!GF_getfield(q, &gf))
	{
		ERROR_MACRO("Could not construct the Galois field needed\n");
		ERROR_MACRO("for the Addelman-Kempthorne (n=3) design.\n");
		return(EXIT_FAILURE);
	}

	A = imatrix( 0, n-1, 0, ncol-1);
	
	if (!A)
	{
		ERROR_MACRO("Could not allocate array for Addelman-Kempthorne (n=3) design.\n");
		return(EXIT_FAILURE);
	}  

	if (addelkemp3( &gf, A, ncol ))
	{
		doubleArrayToSingle(A, _A, n, ncol);
		return(EXIT_SUCCESS);
	}
	else
	{
		ERROR_MACRO("Unable to construct Addelman-Kempthorne (n=3) design q=%d, ncol=%d.\n",
			q,ncol);
		return(EXIT_FAILURE);
	}
}
}
