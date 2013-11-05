/**
 * @file galois.h
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

#include <stdio.h>
#include <math.h>
#include "CommonDefines.h"
#include "galdef.h"
#include "primes.h"

/* Definitions for Galois Fields */

/*  Glossary:

       GF_poly_sum       Addition in polynomial representation
       GF_poly_prod      Multiplication in polynomial representation
       GF_poly2int       Convert polynomial to integer in 0..q-1
       GF_ready          Prepare (+,*,^-1) lookup tables
       GF_print          Print Galois field
       GF_free           Free storage

*/
namespace oacpp {
	class GaloisField
	{
	public:
		static void GF_poly_prod(int p, int n, std::vector<int> & xton, std::vector<int> p1, std::vector<int> p2, std::vector<int> & prod );
		static void GF_poly_sum(int p, int n, std::vector<int> p1, std::vector<int> p2, std::vector<int> & sum );
		static int GF_poly2int( int p, int n, std::vector<int> & poly );
		static void GF_print(GF & gf);
		static int GF_ready(GF & gf, int p, int n, std::vector<int> & xton );
		static void GF_set_fields();
		static int GF_getfield(int q, GF & gf);
	};
}

