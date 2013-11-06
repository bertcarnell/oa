/**
 * @file oa.h
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

#ifndef OA_H
#define OA_H

/*  

  If more than BIGWORK comparisons are required in
an oacheck routine, then a warning is printed that
a large job is underway.  If more than MEDWORK comparisons
are required then intermediate results are printed.

  No strength checking beyond strength MAXSTR is done.
Only change it if you implement the higher strength
checks!

*/

#include "CommonDefines.h"
#include "primes.h"
#include "matrix.h"

#define BIGWORK 100000000
#define MEDWORK BIGWORK/10

/*  
   Glossary:
    OA_put            write OA to standard output
    OA_fput           write OA to stream
    OA_get            get OA from standard input
    OA_fget           get OA from stream
    OA_parsein        read arguments q,nrow,ncol to OA "filter programs"
    OA_strworkcheck   warn about large work loads in strength checking programs
*/
namespace oacpp {
	class OrthogonalArrayStrength {
	public:
		static void OA_strworkcheck(double work, int str);
		static void OA_strength(int q, int nrow, int ncol, matrix<int> & A, int* str, int verbose );
		static int OA_str0(int q, int nrow, int ncol, matrix<int> & A, int verbose   );
		static int OA_str1( int q, int nrow, int ncol, matrix<int> & A, int verbose   );
		static int OA_str2(int q, int nrow, int ncol, matrix<int> & A, int verbose   );
		static int OA_str3(int q, int nrow, int ncol, matrix<int> & A, int verbose );
		static int OA_str4(int q, int nrow, int ncol, matrix<int> & A, int verbose   );
		static int OA_strt(int q, int nrow, int ncol, matrix<int> & A, int t, int verbose   );
	};
}// end namespace

#endif
