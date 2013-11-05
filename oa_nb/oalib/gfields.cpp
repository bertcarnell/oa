/**
 * @file gfields.cpp
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

#include "galois.h"

namespace oacpp
{
    // include declarations of xtndeclare
#include "xtndeclare.h"
    std::vector<int> xtnpt1;

    int GF_fields_are_set = 0;

    void GaloisField::GF_set_fields()
    {
        /* Brute force set up of defining vectors, from Carmichael */

        /* Declare x-to-the-power-n vectors, for GFs p-to-the-n */

        if (GF_fields_are_set)
        {
            PRINT_OUTPUT("Warning: Fields being re-initialized.  Possible memory waste.\n");
        }

        // set variables
#include "xtnset.h"

        xtnpt1 = std::vector<int>(1);
        xtnpt1[0] = 0;
        GF_fields_are_set = 1;
    }

    int GaloisField::GF_getfield(int q, GF & gf)
    {
        std::vector<int> xtn;
        int p, n, ispp;

        if (!GF_fields_are_set)
        {
            GF_set_fields();
        }

        if (q < 1)
        { /* Impossible argument */
            std::string msg = "Field must have positive number of elements.\n";
            throw std::runtime_error(msg.c_str());
        }
        if (q == 1)
        { /* Pointless  argument */
            std::string msg = "Field with 1 element was requested. \n";
            throw std::runtime_error(msg.c_str());
        }

        Primes::primepow(q, &p, &n, &ispp);
        if (!ispp)
        {
            std::string msg = boost::str(boost::format("q=%d is not a prime power.\n") % q);
            throw std::runtime_error(msg.c_str());
        }

        // include generated code
#include "xtndispatch.h"

        if (Primes::isprime(q))
        {
            xtn = xtnpt1; /* Could have tested p=q, or n=1 */
        }

        if (!(xtn.empty()))
        {
            if (GF_ready(gf, p, n, xtn))
            {
                return 1;
            }
            else
            {
                std::string msg = boost::str(boost::format("Construction failed for GF(%d).\n") % q);
                throw std::runtime_error(msg.c_str());
            }
        }
        else
        {
            std::string msg = boost::str(boost::format("GF(%d) = GF(%d^%d) is not included in this program. To add it, consider modifying gfields.c. \n") % q % p % n);
            throw std::runtime_error(msg.c_str());
        }
        return SUCCESS_CHECK;
    }

} // end namespace
