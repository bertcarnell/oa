/*  Use numerical recipes in C styled memory management methods */

#include "memory.h"
#include "defines.h"

namespace oa {

int **imatrix(int nrl, int nrh, int ncl, int nch)
/*int nrl,nrh,ncl,nch;*/
{
  int i;
  int **m;

  //m=(int **) malloc((unsigned) (nrh-nrl+1)*sizeof(int*));
  m = new int*[static_cast<unsigned int>(nrh-nrl+1)];
  if (!m){
    ERROR_MACRO("Unable to allocate %d int* s.\n",nrh-nrl+1);
    return m;
  }
  m -= nrl;

  for(i=nrl;i<=nrh;i++) {
    //m[i]=(int *) malloc((unsigned) (nch-ncl+1)*sizeof(int));
	m[i] = new int[static_cast<unsigned int>(nch-ncl+1)];
    if (!m[i]) {
      ERROR_MACRO("Unable to allocate %d'th row in an integer matrix.\n",
	      i-nrl+1);
      return NULL;
    }
    m[i] -= ncl;
  }
  return m;
}

int *ivector(int nl, int nh)
/*int nl,nh;*/
{
  int *v;

  //v=(int *)malloc((unsigned) (nh-nl+1)*sizeof(int) );
  v = new int[static_cast<unsigned int>(nh-nl+1)];
  if (!v){
    ERROR_MACRO("Unable to allocate %d int s.\n",nh-nl+1);
    return v;
  }
  return(v-nl);
}

/* ARGSUSED */
void free_imatrix(int** m, int nrl, int nrh, int ncl, int nch)
/*int nrl,nrh,ncl,nch;
int **m;*/
{
	nch = 0; // unreferenced
	if (m == NULL)
		return;
	int i;
	for(  i=nrh;i>=nrl;i--  )
		//free( (char*) (m[i]+ncl) );
		delete[] (m[i]+ncl);
	//free((char*) (m+nrl));
	delete[] (m+nrl);
	m = NULL;
}

/* ARGSUSED */
void free_ivector(int* v, int nl, int nh)
/*int *v;
int nl,nh;*/
{
	nh = 0; // unreferenced
  //free((char*) (v+nl));
	if (v == NULL) return;
	delete[] (v+nl);
	v = NULL;
}



double **dmatrix(int nrl, int nrh, int ncl, int nch)
/*int nrl,nrh,ncl,nch;*/
{
  int      i;
  double **m;

  //m=(double **) malloc((unsigned) (nrh-nrl+1)*sizeof(double*));
  m = new double*[static_cast<unsigned int>(nrh-nrl+1)];
  if (!m){
    ERROR_MACRO("Unable to allocate %d double* s.\n",nrh-nrl+1);
    return m;
  }
  m -= nrl;

  for(i=nrl;i<=nrh;i++) {
    //m[i]=(double *) malloc((unsigned) (nch-ncl+1)*sizeof(double));
	m[i] = new double[static_cast<unsigned int>(nch-ncl+1)];
    if (!m[i]) {
      ERROR_MACRO("Unable to allocate %d'th row in an double matrix.\n",
	      i-nrl+1);
      return NULL;
    }
    m[i] -= ncl;
  }
  return m;
}

double *dvector(int nl, int nh)
/*int nl,nh;*/
{
  double *v;

  //v=(double *)malloc((unsigned) (nh-nl+1)*sizeof(double) );
  v = new double[static_cast<unsigned int>(nh-nl+1)];
  if (!v){
    ERROR_MACRO("Unable to allocate %d double s.\n",nh-nl+1);
    return v;
  }
  return(v-nl);
}

/* ARGSUSED */
void free_dmatrix(double** m, int nrl, int nrh, int ncl, int nch)
/*int nrl,nrh,ncl,nch;
double **m;*/
{
	nch = 0;// unreferenced
	if (m == NULL)
		return;
	int i;
	for(  i=nrh;i>=nrl;i--  )
		//free( (char*) (m[i]+ncl) );
		delete[] (m[i]+ncl);
	//free((char*) (m+nrl));
	delete[] (m+nrl);
	m = NULL;
}

/* ARGSUSED */
void free_dvector(double* v, int nl, int nh)
/*double *v;
int nl,nh;*/
{
	nh = 0; // unreferenced
  //free((char*) (v+nl));
  delete[] (v+nl);
  v = NULL;
}










/*  Add rows to a matrix:

      imat            pointer to that matrix
      oldrowsize      highest index+1 of old rows
      newrowsize      highest index+1 of new rows
      colsize         number of cols

*/

int grow_imatrix_byrows(int*** imat, int oldrowsize, int newrowsize, int colsize )
/*int ***imat, oldrowsize, newrowsize, colsize;*/
{
  int i;
  int ** imat_new;

  //imat[0] = (int **) realloc(imat[0],
  //	  (unsigned) (newrowsize)*sizeof(int*));
  imat_new = new int*[static_cast<unsigned int>(newrowsize)];
  if (!(imat_new)){
    ERROR_MACRO("Unable to reallocate %d int* s.\n",newrowsize);
    return 0;
  }
  for (i = 0; i < oldrowsize; i++)
	  imat_new[i] = imat[0][i];

  for(i=oldrowsize; i<newrowsize; i++) {
    //imat[0][i] = (int *) malloc((unsigned) (colsize)*sizeof(int));
	imat_new[i] = new int[static_cast<unsigned int>(colsize)];
    if (!imat_new[i]) {
      ERROR_MACRO("Unable to reallocate %d'th row in an integer matrix.\n",
	      i);
	  // delete new memory;
	  for (int j = oldrowsize; j < i; i++)
		  delete[] imat_new[j];
	  // delete new matrix
	  delete[] imat_new;
      return 0;
    }
  }
  delete[] imat[0];
  imat = &imat_new;
  return 0;
}

}
