#ifndef OALIB_H
#define OALIB_H

extern "C" {
	int addelkemp_main(int* _q, int* _ncol, int* _n, int* _A);
	int addelkemp3_main(int* _q, int* _ncol, int * _n, int * _A);
	int addelkempn_main(int* _akn, int* _q, int* _ncol, int * _A);
	int bose_main(int * _q, int * _ncol, int * _A);
	int bosebush_main(int *_q, int* _ncol, int * _A);
	int bosebushl_main(int *_lam, int *_q, int*_ncol, int* _A);
	int bush_main(int *_q, int *_ncol, int* _A);
	int busht_main(int *_str, int *_q, int *_ncol, int * _A);
}
int oaagree(int *_nrow, int *_ncol, int** A);
int oarand(int is, int js, int ks, int ls, int * _q, int*_nrow, int*_ncol, int** A);
int oastr(int *_q, int*_nrow, int*_ncol, int**A);
int oatriple(int * _nrow, int * _ncol, int **A);


#endif
