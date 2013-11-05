/**
 * @file primes.h
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

/*     Utilities related to prime numbers.  */

#include <math.h>
#include <stdio.h>
#include "CommonDefines.h"

/*  Glossary:

       isprime           returns 1 for prime argument
       ispcheck          was used to test isprime

       primepow          find q=p^n if q is a prime power with n>0
       isprimepow        returns 1 for prime power argument
       ipow              pow() with integer arguments and value
       fqpncheck         was used to test primepow

*/
namespace oacpp {
	class Primes
	{
	public:
		static int isprime(int p );
		static void ispcheck();
		static void primepow(int q, int* p, int* n, int* isit );
		static int isprimepow(int q );
		static int ipow( int a, int b );
		static void fqpncheck();
	};
}// end namespace
