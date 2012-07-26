#ifndef OALIB_H
#define OALIB_H

extern "C" {
	int addelkemp_main(int* _q, int* _ncol, int* n, int** A);
	int addelkemp3_main(int q, int ncol, int ** A);
	int addelkempn_main(int* _akn, int* _q, int* _ncol, int ** A);
	int bose_main(int * _q, int * _ncol, int ** A);
	int bosebush_main(int *_q, int* _ncol, int **A);
	int bosebushl_main(int *_lam, int *_q, int*_ncol, int**A);
	int bush_main(int *_q, int *_ncol, int** A);
	int busht_main(int *_str, int *_q, int *_ncol, int **A);
}
int oaagree(int *_nrow, int *_ncol, int** A);
int oarand(int is, int js, int ks, int ls, int * _q, int*_nrow, int*_ncol, int** A);
int oastr(int *_q, int*_nrow, int*_ncol, int**A);
int oatriple(int * _nrow, int * _ncol, int **A);


#endif
