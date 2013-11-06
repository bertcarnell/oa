/**
 * @file oa_r_utils.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

