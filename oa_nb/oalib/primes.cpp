/**
 * @file primes.cpp
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

#include "primes.h"

namespace oacpp
{
    int Primes::isprime(int p)
    /*int p;*/
    {
        int k;

        if (p < 2)return 0;

        /*  This is not the fastest, but it is likely to
        take negligible time compared to that used in constructing
        the Galois field or the experimental design
         */

        for (k = 2; k < sqrt((double) (p + 1)); k++)
            if ((p / k) * k == p)return 0;
        return 1;
    }

    void Primes::ispcheck()
    {
        int q;
        for (q = 1; q < 2000; q++)
        {
            if (isprime(q))
            {
                PRINT_OUTPUT("%d\n", q);
            }
        }
    }

    void Primes::primepow(int q, int* p, int* n, int* isit)
    {
        int firstfactor = 0; // maybe uninitialized otherwise

        *p = *n = *isit = 0;
        if (q <= 1)
        {
            return;
        }

        if (isprime(q))
        {
            *p = q;
            *n = 1;
            *isit = 1;
            return;
        }

        for (int k = 2; k < sqrt((double) (q + 1)); k++)
        {
            if ((q % k) == 0)
            {
                firstfactor = k;
                break;
            }
        }
        if (!isprime(firstfactor))
        {
            return;
        }

        while (1)
        {
            if (q == 1)
            {
                *isit = 1;
                *p = firstfactor;
                return;
            }
            if (q % firstfactor == 0)
            {
                *n += 1;
                q /= firstfactor;
            }
            else
            {
                return;
            }
        }
    }

    int Primes::isprimepow(int q)
    {
        int p, n, ispp;
        primepow(q, &p, &n, &ispp);
        return ispp;
    }

    int Primes::ipow(int a, int b)
    {
        return (int) pow((double) a, (double) b);
    }

    void Primes::fqpncheck()
    {
        int q, p, n, ispp;

        for (q = 0; q <= 20000; q++)
        {
            primepow(q, &p, &n, &ispp);
            if (ispp)
            {
                PRINT_OUTPUT("%5d %5d %5d\n", q, p, n);
            }
        }
    }

} // end namespace
