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

using namespace oa;

extern "C" {
	int bose_main(int * _q, int * _ncol, int ** A)
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
  ncol = q+1;
}else{
  sscanf(argv[1],"%d",&q);
  sscanf(argv[2],"%d",&ncol);
}*/

if (ncol <= 0)
	ncol = q+1;

if(  !GF_getfield(q, &gf)  ){
  fprintf(stderr,"Could not construct Galois field needed for Bose design.\n");
  exit(1);
}

A = imatrix( 0,q*q-1, 0,ncol-1  );
if(  !A  ){
  fprintf(stderr,"Could not allocate array for Bose design.\n");
  exit(1);
}  

if(  bose( &gf, A, ncol )  )
  //OA_put( A,q*q,ncol,q );
  exit(0);
else{
  fprintf(stderr,"Unable to construct Bose design q=%d, ncol=%d.\n",
	  q,ncol);
  exit(1);
}
}
}
