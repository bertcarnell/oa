#ifndef OA_H
#define OA_H

/*  

  If more than BIGWORK comparisons are required in
an oacheck routine, then a warning is printed that
a large job is underway.  If more than MEDWORK comparisons
are required then intermediate results are printed.

  No strength checking beyond strength MAXSTR is done.
Only change it if you implement the higher strength
checks!

*/

#define BIGWORK 100000000
#define MEDWORK BIGWORK/10

void OA_put(int** A, int n, int k, int q);
void OA_fput(FILE* stream, int **A, int n, int k, int q );
int  OA_get(int** A, int n, int k, int q, int eof_assert);
int OA_fget(FILE* stream, int** A, int n, int k, int q, int eof_assert);
int OA_read( int ***A, int *n, int *k, int* q );
int OA_fread(FILE* stream, int*** A, int *n, int *k, int *q);
int OA_parsein( int argc, char *argv[], int *q, int *nrow, int *ncol, int ***A);
void OA_strworkcheck(double work, int str);
void OA_strength(int q, int nrow, int ncol, int **A, int* str, int verbose );
int OA_str0(int q, int nrow, int ncol, int** A, int verbose   );
int OA_str1( int q, int nrow, int ncol, int** A, int verbose   );
int OA_str2(int q, int nrow, int ncol, int** A, int verbose   );
int OA_str3(int q, int nrow, int ncol, int** A, int verbose );
int OA_str4(int q, int nrow, int ncol, int** A, int verbose   );
int OA_strt(int q, int nrow, int ncol, int **A, int t, int verbose   );


int isprime(int p );
void ispcheck();
void primepow(int q, int* p, int* n, int* isit );
int isprimepow(int q );
int ipow( int a, int b );
void fqpncheck();

#endif
