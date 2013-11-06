/**
 * @file runif.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
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

#ifndef RUNIF_H
#define RUNIF_H

#include "CommonDefines.h"

/*
c
c Marsaglia - Zaman universal random number generator.
c
c reinitialization: call seed(is,js,ks,ls), with integer arguments
c from 1 to 168, not all 1.
c
c generate n uniform random numbers and store in x(n): call ranums(x,n).
c


  Transliterated from FORTRAN to C by Art Owen, 4 March 1993.

  Functions:

    mod( a,b )             a mod b
    seedok( is,js,ks,ls )  1 if seeds ok, 0 otherwise
    seed( is,js,ks,ls )    sets seed integers, rejects invalid input
    ranums( z,n )          sets z[0] through z[n-1] 
                           to the next n random uniforms between 0 and 1
    runif( z,n )           same as ranums

  The C and f77 programs shown below find the first 2000 random
  numbers starting at 0 and print them to 10 places.  The maximum
  difference between any two corresponding random numbers was
  5e-11.  Equality held in 1822 of the cases.  The original FORTRAN 
  subroutines are appended in a comment at the end of this file.
*/

namespace oacpp {

	class RUnif
	{
	public:
		static void seed(int is, int js, int ks, int ls );
		static void runif(std::vector<double> & x, int n);

	private:
		static int mod( int a, int b );
		static int seedok(int is, int js, int ks, int ls );
		static void ranums(std::vector<double> & x, int n);

		static int m_jent, m_i, m_j, m_k, m_l, ip, jp;
		static double u[97+1];
		static double c, cd, cm;
	};
}

#endif
