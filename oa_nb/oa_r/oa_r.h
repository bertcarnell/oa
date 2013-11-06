/**
 * @file oa_r.h
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

#ifndef OA_R_H
#define	OA_R_H

#include <Rcpp.h>
#include "COrthogonalArray.h"
#include "matrix.h"
#include "oa_r_utils.h"

RcppExport SEXP /*int matrix*/ oa_type1(SEXP /*char*/ type, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*int*/ n);
RcppExport SEXP /*int matrix*/ oa_type2(SEXP /*char*/ type, SEXP /*int*/ int1, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*int*/ n);

#endif	/* OA_R_H */

