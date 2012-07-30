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


#include "rutils.h"
#include "defines.h"

/*double **dmatrix(), *dvector();*/


/*

 Utilities based on runif

*/

namespace oa {

void unifperm( int* pi, int q )  
/* 
   In S one just does rank(runif(q)).  Here we want
something like rank(runif(q))-1 since the symbols to
be permuted are 0..q-1.  
*/

/*int q, *pi;*/
{
int i;
double *z;

z = dvector( 0,q-1 );
if(  !z  ){
  ERROR_MACRO("Could not allocate memory for random permutation.\n");
  exit(1);
}
runif( z,q );

findranks( q,z,pi );

for(  i=0; i<q; i++  )
  pi[i] -= 1;

free_dvector( z,0,q-1);
}


/* These routines perform sorting and ranking chores. */

int rankcomp( double** a, double** b )

/*double **a, **b;*/
{
/*printf("Randcomp a = (%g,%g) b=(%g,%g)\n",a[0][0],a[0][1],b[0][0],b[0][1]);*/
if(  a[0][0] < b[0][0]  )return(-1);
if(  a[0][0] > b[0][0]  )return( 1);
return(0);
}

template <class T>
int rankcomp(const void* a, const void* b)
{
	T a_ = *(static_cast<const T*>(a));
	T b_ = *(static_cast<const T*>(b));
	if (a_ < b_)
		return -1;
	if (a_ > b_)
		return 1;
	return 0;
}


int findranks(int n, double* v, int* r )
/*int n, *r;
double *v;*/

{
double **temp;
int    i;

temp = dmatrix(0,n-1,0,1);

if(  !temp  ){
  ERROR_MACRO("findranks: could not allocate memory to find ranks.\n");
  exit(1);
}

for( i=0; i<n; i++  ){
  temp[i][0] = v[i];
  temp[i][1] = (double) i;
}
//qsort((void *)temp,(size_t) n,sizeof(temp[0]),rankcomp);
std::qsort(static_cast<void *>(temp), static_cast<size_t>(n), sizeof(double), rankcomp<double>);

for(  i=0; i<n; i++  )
  r[ (int)temp[i][1] ] = i+1; /*Ranks go 1..n */

return 0;
}


int doubcomp( double a, double b )
/*double a,b;*/
{
if(  a < b  )return(-1);
if(  a > b  )return( 1);
return(0);
}
}
