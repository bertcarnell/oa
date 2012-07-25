#ifndef GALOIS_H
#define GALOIS_H

/* Declarations for dynamic allocation */

/*int *ivector(), **imatrix();*/
int **imatrix(int nrl, int nrh, int ncl, int nch);
int *ivector(int nl, int nh);

/* Definitions for Galois Fields */

#include "galdef.h"
/*struct GF {
  int n,p,q;
  int *xton;
  int **plus;
  int **times;
  int *inv;
  int *neg;
  int *root;
  int **poly;
};*/

void GF_free(struct GF* gf );
void GF_poly_prod(int p, int n, int* xton, int* p1, int* p2, int* prod );
void GF_poly_sum(int p, int n, int* p1, int* p2, int* sum );
int GF_poly2int( int p, int n, int* poly );
void GF_print(struct GF* gf );
int GF_ready(struct GF* gf, int p, int n, int* xton );
void GF_set_fields();
int GF_getfield(int q, struct GF* gf );

#endif
