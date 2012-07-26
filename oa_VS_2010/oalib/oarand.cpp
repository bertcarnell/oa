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

#include "oa.h"
#include "runif.h"
#include "rutils.h"

/*int *ivector(), **imatrix();*/
/*  

  In each column of an orthogonal array, independently randomize the symbols.

*/
using namespace oa;

int oarand(int is, int js, int ks, int ls, int * _q, int*_nrow, int*_ncol, int** A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
//int q, nrow, ncol, **A;
int q=*_q;
int nrow=*_nrow;
int ncol=*_ncol;
int i, j, *pi;
//int is,js,ks,ls;

//if(  argc >= 5  ){  /* Take random seed */
//  sscanf(argv[argc-1],"%d",&is);
//  sscanf(argv[argc-2],"%d",&js);
//  sscanf(argv[argc-3],"%d",&ks);
//  sscanf(argv[argc-4],"%d",&ls);
  seed( is,js,ks,ls );
//}  
//argc -= 4;
//OA_parsein( argc,argv, &q, &nrow, &ncol, &A );

pi = ivector( 0,q-1 );

for(  j=0; j<ncol; j++  ){
  unifperm( pi,q );
  for(  i=0; i<nrow; i++  )
    A[i][j] = pi[ A[i][j] ];
}

//OA_put( A,nrow,ncol,q );
exit(0);
}
