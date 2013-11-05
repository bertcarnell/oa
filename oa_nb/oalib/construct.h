/**
 * @file construct.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:  This file may be freely used and shared according to the original license.
 * 
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 * 
 * Original Header:
 * <blockquote>
 * These programs construct and manipulate orthogonal arrays.  They were prepared by
 * 
 * - Art Owen
 * - Department of Statistics
 * - Sequoia Hall
 * - Stanford CA 94305
 * 
 * They may be freely used and shared.  This code comes 
 * with no warranty of any kind.  Use it at your own
 * risk.
 * 
 * I thank the Semiconductor Research Corporation and
 * the National Science Foundation for supporting this
 * work.
 * </blockquote>
 */

#pragma once

/*  Constructions for designs using Galois fields */

#include <math.h>
#include <stdio.h>
#include "CommonDefines.h"
#include "galois.h"
#include "ak.h"

/*  Glossary:

    bose:            OA( q^2, q+1, q, 2  )
                     R.C. Bose (1938) Sankhya Vol 3 pp 323-338
    bosecheck:       test input to bose

    bosebush:        OA( 2q^2, 2q+1, q, 2 ), only implemented for q=2^n
    bosebushcheck:   test input to bosebush

    polyeval:        evaluate a polynomial with coefficients, argument
                     and result in a Galois field

*/

namespace oacpp {
	class OAConstruct
	{
	public:
		static int bosecheck(int q, int ncol );
		static int bose(GF & gf, matrix<int> & A, int ncol );
		static int itopoly(int n, int q, int d, std::vector<int> & coef );
		static int polyeval(GF & gf, int d, std::vector<int> & poly, int arg, int* value );
		static int bushcheck(int q, int str, int ncol);
		static int bush(GF & gf, matrix<int> &  A, int str, int ncol  );
		static int addelkemp(GF & gf, matrix<int> & A, int ncol );
		static int bosebushcheck(int q, int p, int ncol  );
		static int bosebush(GF & gf, matrix<int> & B, int ncol );
		static int bosebushlcheck(int s, int p, int lam, int ncol  );
		static int bosebushl(GF & gf, int lam, matrix<int> & B, int ncol );
		static int addelkempcheck(int q, int p, int ncol );
	};
}// end namespace
