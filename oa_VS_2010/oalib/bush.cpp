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
	int bush_main(int *_q, int *_ncol, int** A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
int q=*_q;
int ncol=*_ncol;
GF gf;

/*if(  argc==1  )
  scanf("%d %d",&q,&ncol);
else if( argc==2  ){
  sscanf(argv[1],"%d",&q);
  ncol = q+1;
}else{
  sscanf(argv[1],"%d",&q);
  sscanf(argv[2],"%d",&ncol);
}*/
if (ncol <= 0)
	ncol = q+1;

if(  !GF_getfield(q, &gf)  ){
  ERROR_MACRO("Could not construct the Galois field needed\n");
  ERROR_MACRO("for the strength 3 Bush design.\n");
  exit(1);
}

A = imatrix( 0,q*q*q-1, 0,ncol-1  );
if(  !A  ){
  ERROR_MACRO("Could not allocate array for Bush design.\n");
  exit(1);
}  

if(  bush( &gf, A, 3, ncol )  ){
  //OA_put( A,q*q*q,ncol,q );
  exit(0);
}
else{
  ERROR_MACRO("Unable to construct the strength 3 Bush design q=%d, ncol=%d.\n",
	  q,ncol);
  exit(1);
}
}
}
