/**
 * @file rutils.cpp
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

#include "rutils.h"

namespace oacpp
{
    /* 
       In S one just does rank(runif(q)).  Here we want
    something like rank(runif(q))-1 since the symbols to
    be permuted are 0..q-1.  
     */
    void RUtils::unifperm(std::vector<int> & pi, int q)
    {
        int i;
        std::vector<double> z = std::vector<double>(q);
        if (!z.empty())
        {
            throw std::runtime_error("Could not allocate memory for random permutation.\n");
        }
        RUnif::runif(z, q);

        findranks(z, pi);

        for (i = 0; i < q; i++)
            pi[i] -= 1;
    }
} // end namespace
