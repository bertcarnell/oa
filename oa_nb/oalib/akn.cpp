/**
 * @file akn.cpp
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

#include "ak.h"

namespace oacpp
{
    int Addelkemp::addelkempncheck(int q, int p, int akn, int ncol)
    {
        std::string msg;
        if (akn < 2)
        {
            msg = boost::str(boost::format("This Addelman-Kempthorne OA(2q^n,ncol,q,2) is only \n available for n >= 2.  n = %d was requested. \n") % akn);
            throw std::runtime_error(msg.c_str());
        }

        if (p == 2 && q > 4)
        {
            msg = "This Addelman-Kempthorne OA(2q^n,ncol,q,2) is only \n available for odd prime powers q and for even prime \n powers q<=4. \n";
            throw std::runtime_error(msg.c_str());
        }

        if (ncol > 2 * (Primes::ipow(q, akn) - 1) / (q - 1) - 1)
        {
            msg = boost::str(boost::format("The Addelman-Kempthorne construction needs \n ncol <= 2(q^n-1)(q-1) -1. Can't have ncol = %d \n with n=%d and q = %d,\n") % ncol % akn % q);
            throw std::runtime_error(msg.c_str());
        }

        return SUCCESS_CHECK;
    }

    /* Implement Addelman and Kempthorne's 1961 A.M.S. method with n=3 */
    int Addelkemp::addelkempn(GF & gf, int akn, matrix<int> & A, int ncol)
    {
        int p, q;
        int kay; /* A&K notation */
        int col, square, ksquare;
        int monic, elt;
        size_t numin;
        size_t aknu = static_cast<size_t> (akn);

        p = gf.p, q = gf.q;

        if (!addelkempncheck(q, p, akn, ncol))
        {
            return 0;
        }

        std::vector<int> b(q);
        std::vector<int> c(q);
        std::vector<int> k(q);
        std::vector<int> x(aknu);
        std::vector<int> s(aknu);
        std::vector<int> coef(aknu);
        std::vector<int> indx(aknu);

        x.assign(aknu, 0); // this might not be necessary?
        /*for (size_t i = 0; i < aknu; i++)
        {
            x[i] = 0;
        }*/
        for (size_t row = 0; row < static_cast<size_t>(Primes::ipow(q, akn)); row++)
        { /* First q^akn rows */
            col = 0;
            s.assign(aknu, 0);
            s[0] = 1;
            //for (size_t i = 1; i < aknu; i++) /* first subset */
            //{
            //    s[i] = 0; /* nonempty subsets of x indices */
            //}
            
            for (size_t sub = 1; sub < static_cast<size_t>(Primes::ipow(2, akn)) && col < ncol; sub++)
            {
                monic = -1;
                numin = 0;
                for (size_t i = 0; i < aknu; i++)
                {
                    if (s[i])
                    {
                        if (monic == -1)
                        {
                            monic = i;
                        }
                        else
                        {
                            indx[numin++] = i;
                        }
                    }
                }
                for (size_t i = 0; i < numin; i++)
                {
                    coef[i] = 1;
                }
                for (size_t poly = 0; poly < static_cast<size_t>(Primes::ipow(q - 1, numin)) && col < ncol; poly++)
                {
                    elt = x[monic];
                    for (size_t i = 0; i < numin; i++)
                    {
                        elt = gf.plus(elt, gf.times(coef[i],x[indx[i]]));
                    }
                    A(row,col++) = elt;
                    for (size_t i = numin - 1; i >= 0; i--)
                    {
                        coef[i] = (coef[i] + 1) % q;
                        if (coef[i])
                        {
                            break;
                        }
                        else
                        {
                            coef[i] = 1;
                        }
                    }
                }
                for (size_t i = 0; i < aknu; i++)
                {
                    s[i] = (s[i] + 1) % 2;
                    if (s[i])
                    {
                        break;
                    }
                }
            }

            square = gf.times(x[0], x[0]);

            s[1] = 1;
            for (size_t i = 2; i < aknu; i++) /* first subset */
            {
                s[i] = 0; /* nonempty subsets of x indices */
            }
            for (size_t sub = 1; sub < static_cast<size_t>(Primes::ipow(2, akn - 1)) && col < ncol; sub++)
            {
                monic = -1;
                numin = 0;
                for (size_t i = 1; i < aknu; i++)
                {
                    if (s[i])
                    {
                        if (monic == -1)
                        {
                            monic = i;
                        }
                        else
                        {
                            indx[numin++] = i;
                        }
                    }
                }
                coef[0] = 0;
                for (size_t i = 1; i < numin + 1; i++)
                {
                    coef[i] = 1;
                }
                for (size_t poly = 0; poly < static_cast<size_t>(q * Primes::ipow(q - 1, numin)) && col < ncol; poly++)
                {
                    elt = gf.plus(square,gf.times(x[0],coef[0]));
                    elt = gf.plus(elt,x[monic]);
                    for (size_t i = 1; i < numin + 1; i++)
                    {
                        elt = gf.plus(elt,gf.times(coef[i],x[indx[i - 1]]));
                    }
                    A(row,col++) = elt;
                    for (size_t i = numin + 1 - 1; i >= 0; i--)
                    {
                        coef[i] = (coef[i] + 1) % q;
                        if (coef[i])
                        {
                            break;
                        }
                        else
                        {
                            if (i > 0)
                            {
                                coef[i] = 1;
                            }
                        }
                    }
                }
                for (size_t i = 1; i < aknu; i++)
                {
                    s[i] = (s[i] + 1) % 2;
                    if (s[i])
                    {
                        break;
                    }
                }
            }

            for (size_t i = aknu - 1; i >= 0; i--)
            {
                x[i] = (x[i] + 1) % q;
                if (x[i])
                {
                    break;
                }
            }
        }

        if (p != 2) /* Constants kay,b,c,k for odd p */
        {
            akodd(gf, &kay, b, c, k);
        }
        else /* Constants kay,b,c,k for even p */
        {
            akeven(gf, &kay, b, c, k);
        }

        x.assign(aknu, 0);
        /*for (size_t i = 0; i < aknu; i++)
        {
            x[i] = 0;
        }*/
        for (size_t row = static_cast<size_t>(Primes::ipow(q, akn)); row < static_cast<size_t>(2 * Primes::ipow(q, akn)); row++) /* Second q^akn rows */
        {
            col = 0;
            s.assign(aknu, 0);
            s[0] = 1;
            //for (size_t i = 1; i < aknu; i++) /* first subset */
            //{
            //    s[i] = 0; /* nonempty subsets of x indices */
            //}
            for (size_t sub = 1; sub < static_cast<size_t>(Primes::ipow(2, akn)) && col < ncol; sub++)
            {
                monic = -1;
                numin = 0;
                for (size_t i = 0; i < aknu; i++)
                {
                    if (s[i])
                    {
                        if (monic == -1)
                        {
                            monic = i;
                        }
                        else
                        {
                            indx[numin++] = i;
                        }
                    }
                }
                for (size_t i = 0; i < numin; i++)
                {
                    coef[i] = 1;
                }
                for (size_t poly = 0; poly < static_cast<size_t>(Primes::ipow(q - 1, numin)) && col < ncol; poly++)
                {
                    elt = x[monic];
                    if (numin && s[0])
                    {
                        elt = gf.plus(elt,b[coef[0]]);
                    }
                    for (size_t i = 0; i < numin; i++)
                    {
                        elt = gf.plus(elt,gf.times(coef[i],x[indx[i]]));
                    }
                    A(row,col++) = elt;
                    for (size_t i = numin - 1; i >= 0; i--)
                    {
                        coef[i] = (coef[i] + 1) % q;
                        if (coef[i])
                        {
                            break;
                        }
                        else
                        {
                            coef[i] = 1;
                        }
                    }
                }
                for (size_t i = 0; i < aknu; i++)
                {
                    s[i] = (s[i] + 1) % 2;
                    if (s[i])
                    {
                        break;
                    }
                }
            }

            ksquare = gf.times(kay,gf.times(x[0],x[0]));

            s[1] = 1;
            for (size_t i = 2; i < aknu; i++) /* first subset */
            {
                s[i] = 0; /* nonempty subsets of x indices */
            }
            for (size_t sub = 1; sub < static_cast<size_t>(Primes::ipow(2, akn - 1)) && col < ncol; sub++)
            {
                monic = -1;
                numin = 0;
                for (size_t i = 1; i < aknu; i++)
                {
                    if (s[i])
                    {
                        if (monic == -1)
                        {
                            monic = i;
                        }
                        else
                        {
                            indx[numin++] = i;
                        }
                    }
                }
                coef[0] = 0;
                for (size_t i = 1; i < numin + 1; i++)
                {
                    coef[i] = 1;
                }
                for (size_t poly = 0; poly < static_cast<size_t>(q * Primes::ipow(q - 1, numin)) && col < ncol; poly++)
                {
                    elt = gf.plus(ksquare,gf.times(x[0],k[coef[0]]));
                    elt = gf.plus(elt,x[monic]);
                    elt = gf.plus(elt,c[coef[0]]);
                    for (size_t i = 1; i < numin + 1; i++)
                    {
                        elt = gf.plus(elt,gf.times(coef[i],x[indx[i - 1]]));
                    }
                    A(row,col++) = elt;
                    for (size_t i = numin + 1 - 1; i >= 0; i--)
                    {
                        coef[i] = (coef[i] + 1) % q;
                        if (coef[i])
                        {
                            break;
                        }
                        else
                        {
                            coef[i] = i > 0 ? 1 : 0;
                        }
                    }
                }
                for (size_t i = 1; i < aknu; i++)
                {
                    s[i] = (s[i] + 1) % 2;
                    if (s[i])
                    {
                        break;
                    }
                }
            }

            for (size_t i = aknu - 1; i >= 0; i--)
            {
                x[i] = (x[i] + 1) % q;
                if (x[i])
                {
                    break;
                }
            }
        }

        return 1;
    }

} // end namespace
