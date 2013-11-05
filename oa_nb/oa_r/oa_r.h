/**
 * @file oa_r.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#ifndef OA_R_H
#define	OA_R_H

#include <Rcpp.h>
#include "COrthogonalArray.h"
#include "matrix.h"
#include "oa_r_utils.h"

RcppExport SEXP /*int matrix*/ oa_type1(SEXP /*char*/ type, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*int*/ n);
RcppExport SEXP /*int matrix*/ oa_type2(SEXP /*char*/ type, SEXP /*int*/ int1, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*int*/ n);

#endif	/* OA_R_H */

