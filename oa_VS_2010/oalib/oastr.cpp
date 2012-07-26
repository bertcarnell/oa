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


#include <cstdio>
#include "oa.h"

/*  
 
   Use brute force to check the actual strength
of the input array.

*/

using namespace oa;

int oastr(int *_q, int*_nrow, int*_ncol, int**A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
int q = *_q;
int nrow = *_nrow;
int ncol = *_ncol;
int str;

//double work;

//OA_parsein( &q, &nrow, &ncol, &A );
OA_strength( q,nrow,ncol,A,&str,2 );

if(  str <0  ){
  printf("\nThe array does not even have strength 0, meaning that\n");
  printf("it is not composed of symbols 0 through %d.\n");
}
else
  printf("\nThe array has strength %d and no higher strength.\n",str);
return 0;
}
