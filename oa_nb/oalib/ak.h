/**
 * @file ak.h
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

#ifndef AK_H
#define AK_H

/*     Addelman-Kempthorne Constructions with n = 3.

       The article is quite vague on this.  Page 1173 states
   "When n>2 the same procedure will yield the desired plans
   if Lemma 5a is used in place of Lemma 5."  Page 1175
   provides the example n=3,q=3 which is OA( 54,25,3,2 ).
   Based on this example it is possible to make an educated
   guess as to how the construction generalizes to n=3.
   The resulting OA's are seen, by brute force to be of
   strength 2 for q=2,3,4,5,7,11.  These OAs are:
         OA(   16,  13,  2, 2 )   
	 OA(   54,  25,  3, 2 )
	 OA(  128,  41,  4, 2 )   
	 OA(  250,  61,  5, 2 )
	 OA(  686, 113,  7, 2 )
	 OA( 1458, 181,  9, 2 )
	 OA( 2662, 265, 11, 2 )
   The one with q=7 required 212709392 comparisons to determine
   that it really is of strength 2.  This took roughly 11.5 minutes
   on a DEC 5000/240 workstation (real and elapsed in this case).
   
   The array with q=11 took 1.12671e+10 comparisons to verify its strength.
   This took roughly 10 1/2 hours.
   Here is the tail end of the output from oacheck2:
   No violation of strength 2 involves column 262.
   No violation of strength 2 involves column 263.
   No violation of strength 2 involves column 264.
   The array is of strength (at least) 2.
   [2]    Done                 aktest | oacheck2 11 2662 265
   37890.0u 31.7s 10:33:11 99% 61+110k 0+0io 0pf+0w
*/

/*  For even q, only q= 2 or 4 are available.  The prescription
given in Addelman and Kempthorne (1961) does not appear to work.
Commented out code below attempts to implement that prescription.
It seemed to be impossible to find a constant b[1],c[1] pair.
*/

/*     Addelman-Kempthorne Constructions with general n.

       The article is quite vague on this.  Page 1173 states
   "When n>2 the same procedure will yield the desired plans
   if Lemma 5a is used in place of Lemma 5."  Page 1175
   provides the example n=3,q=3 which is OA( 54,25,3,2 ).
   Based on this example it is possible to make an educated
   guess as to how the construction generalizes.

*/

#include "CommonDefines.h"
#include "galois.h"
#include "primes.h"
#include "matrix.h"

namespace oacpp {
	class Addelkemp 
	{
	public:
		static int addelkemp3check(int q, int p, int ncol);
		static int akeven(GF & gf, int* kay, std::vector<int> & b, std::vector<int> & c, std::vector<int> & k );
		static int akodd(GF & gf, int* kay, std::vector<int> & b, std::vector<int> & c, std::vector<int> & k );
		static int addelkempncheck(int q, int p, int akn, int ncol  );
		static int addelkempn(GF & gf, int akn, matrix<int> & A, int ncol );
		static int addelkemp3(GF & gf, matrix<int> & A, int ncol );
	};
}

#endif
