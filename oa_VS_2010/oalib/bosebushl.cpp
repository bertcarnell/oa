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
#include "primes.h"
#include "gfields.h"
#include "defines.h"
#include "rutils.h"

using namespace oa;

extern "C" {
	int bosebushl_main(int *_lam, int *_q, int*_ncol, int * _A)
/*int main(int argc, char* argv[])
int  argc;
char *argv[];*/
{
int lam=*_lam;
int q=*_q;
int ncol=*_ncol;
GF gf;
int       pq, nq, isppq,  pl, nl, isppl;
int ** A;

/*if (argc==1)
  scanf("%d %d %d",&lam,&q,&ncol);
else if ( argc==2){
  sscanf(argv[1],"%d",&lam);
  scanf("%d %d",&q,&ncol);
}else if ( argc==3 ){
  sscanf(argv[1],"%d",&lam);
  sscanf(argv[2],"%d",&q);
  ncol = q*lam;
}else{
  sscanf(argv[1],"%d",&lam);
  sscanf(argv[2],"%d",&q);
  sscanf(argv[3],"%d",&ncol);
}*/
if (ncol <= 0)
	ncol = q*lam;
primepow( lam, &pl, &nl, &isppl);
primepow(  q , &pq, &nq, &isppq);

if (!isppq){
  ERROR_MACRO("The Bose-Bush construction requires that q be a prime\n");
  ERROR_MACRO("raised to a positive integral power. q=%d was requested\n",q);
  ERROR_MACRO(" and is not such a prime power.\n");
  return(EXIT_FAILURE);
}

if (!isppl){
  ERROR_MACRO("The Bose-Bush construction requires that lambda be a prime\n");
  ERROR_MACRO("raised to a positive integral power. lambda=%d was requested\n",lam);
  ERROR_MACRO(" and is not such a prime power.\n");
  return(EXIT_FAILURE);
}

if (pl != pq){
  ERROR_MACRO("The Bose-Bush construction requires lambda and q\n");
  ERROR_MACRO("to be powers of the same prime. So lambda = %d = %d^%d\n",
	  lam,pl,nl);
  ERROR_MACRO("and q = %d = %d^%d are not suitable.\n",q,pq,nq);
  return(EXIT_FAILURE);
}

if (!GF_getfield(lam*q, &gf)){
  ERROR_MACRO("Could not construct the Galois field needed\n");
  ERROR_MACRO("for the Bose-Bush design.\n");
  return(EXIT_FAILURE);
}

A = imatrix( 0,lam*q*q-1, 0,ncol-1);
if (!A){
  ERROR_MACRO("Could not allocate array for Bose design.\n");
  return(EXIT_FAILURE);
}  

if (bosebushl( &gf, lam, A, ncol )){
  //OA_put( A,lam*q*q,ncol,q );
	doubleArrayToSingle(A, _A, lam*q*q, ncol);
	return(EXIT_SUCCESS);
}
else{
  ERROR_MACRO("Unable to construct Bose design lambda=%d, q=%d, ncol=%d.\n",
	  lam,q,ncol);
  return(EXIT_FAILURE);
}
}
}


