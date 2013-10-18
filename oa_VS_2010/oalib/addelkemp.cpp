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

#include "construct.h"
#include "galois.h"
#include "gfields.h"
#include "defines.h"
#include "rutils.h"

using namespace oa;

/* n=2*q*q
 * 0 < ncol <= 2*q + 1
 * A=length(n*ncol) 
 */
extern "C" {
int addelkemp_main(int* _q, int* _ncol, int* _n, int* _A)
{
	int q = *_q;
	int ncol = *_ncol;
	int n = *_n;
	GF gf;
	int ** A;

	if (ncol <= 0)
	{
		ERROR_MACRO("ncol cannot be less than or equal to 0\n",2*q+1);
		return(EXIT_FAILURE);
	}
	if (ncol > 2*q+1)
	{
		ERROR_MACRO("At most 2q+1 = %d columns are possible\n",2*q+1);
		ERROR_MACRO("for the Addelman Kempthorne design with q = %d.\n",q);
		return(EXIT_FAILURE);
	}
	if (n != 2*q*q)
	{
		ERROR_MACRO("n must be equal to 2*q*q");
		return(EXIT_FAILURE);
	}
	if (!GF_getfield(q, &gf))
	{
		ERROR_MACRO("Could not construct the Galois field needed\n");
		ERROR_MACRO("for the Addelman Kempthorne design.\n");
		return(EXIT_FAILURE);
	}

	A = imatrix(0, n-1, 0, ncol-1);

	if (!A)
	{
		ERROR_MACRO("Could not allocate array for Addelman Kempthorne design.\n");
		return(EXIT_FAILURE);
	}  

	if (addelkemp( &gf, A, ncol ))
	{
		doubleArrayToSingle(A, _A, n, ncol);
		return(EXIT_SUCCESS);
	}
	else
	{
		ERROR_MACRO("Unable to construct Addelman Kempthorne design q=%d, ncol=%d.\n",
			q,ncol);
		return(EXIT_FAILURE);
	}
}
}
