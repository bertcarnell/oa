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

using namespace oa;

extern "C" {
	int addelkemp_main(int* _q, int* _ncol, int* n, int** A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
int q = *_q;
int ncol = *_ncol;
GF gf;

/*if(  argc==1  )
  scanf("%d %d",&q,&ncol);
else if( argc==2  ){
  sscanf(argv[1],"%d",&q);
  ncol = 2*q;    /* Can get 2q without defect, 2q+1 with defect */ /*
}else{
  sscanf(argv[1],"%d",&q);
  sscanf(argv[2],"%d",&ncol);
}*/

if (ncol <= 0)
	ncol = 2*q;
if(  ncol > 2*q+1  ){
  ERROR_MACRO("At most 2q+1 = %d columns are possible\n",2*q+1);
  ERROR_MACRO("for the Addelman Kempthorne design with q = %d.\n",q);
  exit(1);
}  

if(  !GF_getfield(q, &gf)  ){
  ERROR_MACRO("Could not construct the Galois field needed\n");
  ERROR_MACRO("for the Addelman Kempthorne design.\n");
  exit(1);
}

A = imatrix( 0, 2*q*q-1, 0, ncol-1  );
if(  !A  ){
  ERROR_MACRO("Could not allocate array for Addelman Kempthorne design.\n");
  exit(1);
}  

if(  addelkemp( &gf, A, ncol )  ){
	*n = 2*q*q;
  /*OA_put( A, 2*q*q, ncol, q );*/
  exit(0);
}
else{
  ERROR_MACRO("Unable to construct Addelman Kempthorne design q=%d, ncol=%d.\n",
	  q,ncol);
  exit(1);
}
}
}
