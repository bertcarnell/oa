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


/*     Utilities related to prime numbers.  */

#include "primes.h"
#include "defines.h"

/*  Glossary:

       isprime           returns 1 for prime argument
       ispcheck          was used to test isprime

       primepow          find q=p^n if q is a prime power with n>0
       isprimepow        returns 1 for prime power argument
       ipow              pow() with integer arguments and value
       fqpncheck         was used to test primepow

*/

namespace oa {

int isprime(int p )
/*int p;*/
{
int k;

if (p<2)return 0;

/*  This is not the fastest, but it is likely to
take negligible time compared to that used in constructing
the Galois field or the experimental design
*/

for(  k=2; k< sqrt( (double) (p+1) ); k++)
  if ((p/k)*k == p)return 0;
return 1;
}

void ispcheck()
{
int q;
for(  q=1; q<2000; q++)
  if (isprime(q))PRINT_MACRO("%d\n",q);
}

void primepow(int q, int* p, int* n, int* isit )
/*int q,*p,*n,*isit;*/
{
int k;
int firstfactor = 0;
 
*p = *n = *isit = 0;
if (q<=1)return;

if (isprime(q)){
  *p=q; *n=1; *isit=1;
  return;
}

for(  k=2; k<sqrt( (double) (q+1) ); k++)
  if ((q%k)==0){
    firstfactor = k;
    break;
  }
if (!isprime(firstfactor))return;

//while( 1 ){
for ( ; ; ){ // eliminates warning that while (1) gives
  if (q == 1){
    *isit = 1;
    *p = firstfactor;
    return;
  }
  if (q %  firstfactor == 0){
    *n += 1;
    q/= firstfactor;
  }
  else{
    return;
  }
}
}

int isprimepow(int q )
/*int q;*/
{
int p,n,ispp;
primepow( q,&p,&n,&ispp );
return ispp;
}


int ipow( int a, int b )
/*int a,b;*/
{return (int) pow( (double) a, (double) b );}


void fqpncheck()
{
int q, p, n, ispp;

for(  q=0; q<=20000; q++){
  primepow( q, &p, &n, &ispp );
  if (ispp)
    PRINT_MACRO("%5d %5d %5d\n",q,p,n);
}
}

}
