/**
 * @file oa_r_utils.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#ifndef OA_R_UTILS_H
#define	OA_R_UTILS_H

#include <Rcpp.h>
#include "matrix.h"

namespace oarutils {

    template <class T>
    Rcpp::IntegerMatrix convertToIntegerMatrix(const oacpp::matrix<T> & A)
    {
        size_t nrows = A.rowsize();
        size_t ncols = A.colsize();
        Rcpp::IntegerMatrix rcppA(nrows, ncols);
        for (size_t i = 0; i < nrows; i++)
        {
            for (size_t j = 0; j < ncols; j++)
            {
                rcppA(i,j) = static_cast<int>(A(i,j));
            }
        }
        return rcppA;
    }
    
} // end namespace

#endif	/* OA_R_UTILS_H */

