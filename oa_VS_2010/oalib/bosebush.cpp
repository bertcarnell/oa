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
	int bosebush_main(int *_q, int* _ncol, int * _A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
int q=*_q;
int ncol=*_ncol;
GF gf;
int ** A;

/*if (argc==1)
  scanf("%d %d",&q,&ncol);
else if ( argc==2){
  sscanf(argv[1],"%d",&q);
  ncol = 2*q;*/    /* Can get 2q without defect, 2q+1 with defect */
/*}else{
  sscanf(argv[1],"%d",&q);
  sscanf(argv[2],"%d",&ncol);
}*/
if (ncol <= 0)
	ncol = 2*q;

if (q%2){
  ERROR_MACRO("This implementation of Bose-Bush only works for a number\n");
  ERROR_MACRO("q of levels equal to a power of 2.  q=%d was requested.\n",q);
  ERROR_MACRO("The Addelman-Kempthorne designs might be available.\n");
  return(EXIT_FAILURE);
}

if (!GF_getfield(2*q, &gf)){
  ERROR_MACRO("Could not construct the Galois field needed\n");
  ERROR_MACRO("for the Bose Bush design.\n");
  return(EXIT_FAILURE);
}

A = imatrix( 0,2*q*q-1, 0,ncol-1);
if (!A){
  ERROR_MACRO("Could not allocate array for Bose design.\n");
  return(EXIT_FAILURE);
}  

if (bosebush( &gf, A, ncol )){
  //OA_put( A,2*q*q,ncol,q );
	doubleArrayToSingle(A, _A, 2*q*q, ncol);
  return(EXIT_SUCCESS);
}
else{
  ERROR_MACRO("Unable to construct Bose design q=%d, ncol=%d.\n",
	  q,ncol);
  return(EXIT_FAILURE);
}
}
}
