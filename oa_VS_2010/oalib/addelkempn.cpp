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

#include "akn.h"
#include "galois.h"
#include "primes.h"
#include "gfields.h"
#include "defines.h"

using namespace oa;

extern "C" {
	int addelkempn_main(int* _akn, int* _q, int* _ncol, int ** A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
/*int       akn, q, ncol, **A;*/
int akn = *_akn;
int q = *_q;
int ncol = *_ncol;
GF gf;

/*if(  argc==1  )
  scanf("%d %d %d",&akn,&q,&ncol);
else if( argc==2  ){
  sscanf(argv[1],"%d",&akn);
  scanf("%d %d",&q,&ncol);
}else if( argc==3  ){
  sscanf(argv[1],"%d",&akn);
  sscanf(argv[2],"%d",&q);
  ncol = 2*(ipow(q,akn)-1)/(q-1) - 1;*/  /*  2(q^3-1)/(q-1) - 1  */
/*}else{
  sscanf(argv[1],"%d",&akn);
  sscanf(argv[2],"%d",&q);
  sscanf(argv[3],"%d",&ncol);
}*/

if (ncol <= 0)
	ncol = 2*(ipow(q,akn)-1)/(q-1) - 1;

if(  !GF_getfield(q, &gf)  ){
  ERROR_MACRO("Could not construct the Galois field needed\n");
  ERROR_MACRO("for the Addelman-Kempthorne (n=%d, q=%d) design.\n",
	  akn,q);
  exit(1);
}

A = imatrix( 0, 2*ipow(q,akn)-1, 0, ncol-1  );
if(  !A  ){
  ERROR_MACRO("Could not allocate array for Addelman-Kempthorne\n");
  ERROR_MACRO("(n=%d, q=%d) design.\n",akn,q);
  exit(1);
}  

if(  addelkempn( &gf, akn, A, ncol )  ){
  //OA_put( A, 2*ipow(q,akn), ncol, q );
  exit(0);
}
else{
  ERROR_MACRO("Unable to construct Addelman-Kempthorne design \n");
  ERROR_MACRO("with n = %d, q = %d, ncol = %d.\n",akn,q,ncol);
  exit(1);
}
}
}
