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

#include "galois.h"
#include "construct.h"
#include "gfields.h"
#include "defines.h"
#include "rutils.h"

using namespace oa;

extern "C" {
	int bose_main(int * _q, int * _ncol, int * _A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
int q = *_q;
int ncol = *_ncol;
GF gf;
int ** A;

/*if (argc==1)
  scanf("%d %d",&q,&ncol);
else if ( argc==2){
  sscanf(argv[1],"%d",&q);
  ncol = q+1;
}else{
  sscanf(argv[1],"%d",&q);
  sscanf(argv[2],"%d",&ncol);
}*/

if (ncol <= 0)
	ncol = q+1;

if (!GF_getfield(q, &gf)){
  ERROR_MACRO("Could not construct Galois field needed for Bose design.\n");
  return(EXIT_FAILURE);
}

A = imatrix( 0,q*q-1, 0,ncol-1);
if (!A){
  ERROR_MACRO("Could not allocate array for Bose design.\n");
  return(EXIT_FAILURE);
}  

if (bose( &gf, A, ncol ))
{
  //OA_put( A,q*q,ncol,q );
	doubleArrayToSingle(A, _A, q*q, ncol);
	return(EXIT_SUCCESS);
}
else{
  ERROR_MACRO("Unable to construct Bose design q=%d, ncol=%d.\n",
	  q,ncol);
  return(EXIT_FAILURE);
}
}
}
