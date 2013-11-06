/**
 * @file construct.cpp
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

#include "construct.h"

namespace oacpp
{
    int OAConstruct::bosecheck(int q, int ncol)
    {
        std::string msg;
        if (ncol > q + 1)
        {
            msg = boost::str(boost::format("Bose's design must have ncol <= q+1. \n Had q=%d and ncol=%d. \n") % q % ncol);
            throw std::runtime_error(msg.c_str());
        }
        if (ncol <= 0)
        {
            msg = "Nonpositive number of columns requested for Bose's design\n";
            throw std::runtime_error(msg.c_str());
        }
        return SUCCESS_CHECK;
    }

    int OAConstruct::bose(GF & gf, matrix<int> & A, int ncol)
    {
        size_t icol, irow;
        size_t q = static_cast<size_t>(gf.q);

        if (!bosecheck(q, ncol))
        {
            return 0;
        }

        irow = 0;
        for (size_t i = 0; i < q; i++)
        {
            for (size_t j = 0; j < q; j++)
            {
                icol = 0;
                A(irow,icol++) = i;
                if (ncol > 1)
                {
                    A(irow,icol++) = j;
                }
                for (size_t icol = 2; icol < static_cast<size_t>(ncol); icol++)
                {
                    A(irow, icol) = gf.plus(j,gf.times(i,icol - 1));
                }
                irow++;
            }
        }

        return 1;
    }

    int OAConstruct::itopoly(int n, int q, int d, std::vector<int> & coef)
    {
        for (size_t i = 0; i <= static_cast<size_t>(d); i++)
        {
            coef[i] = n % q;
            n = n / q;
        }
        return 0;
    }

    int OAConstruct::polyeval(GF & gf, int d, std::vector<int> & poly, int arg, int* value)
    /*  find  value = poly(arg) where poly is a polynomial of degree d  
        and all the arithmetic takes place in the given Galois field.*/
    {
        int ans;

        ans = 0;
        for (size_t i = d; i >= 0; i--) /* Horner's rule */
        {
            ans = gf.plus(gf.times(ans,arg),poly[i]);
        }

        *value = ans;
        return 0;
    }

    int OAConstruct::bushcheck(int q, int str, int ncol)
    {
        std::string msg;
        if (ncol > q + 1)
        {
            msg = boost::str(boost::format("Bush designs require ncol <= q+1. \n Cannot have q = %d and ncol = %d. \n") % q % ncol);
            throw std::runtime_error(msg.c_str());
        }
        if (str > ncol)
        {
            msg = boost::str(boost::format("It doesn't make sense to have an array of strength \n %d with only %d columns. \n") % str % ncol);
            throw std::runtime_error(msg.c_str());
        }
        if (str >= q + 1)
        {
            PRINT_OUTPUT("Bush's (1952) theorem has a condition t<q where t\n");
            PRINT_OUTPUT("is the strength of the array and q is the number of symbols.\n");
            PRINT_OUTPUT("Here we have t = %d and q = %d.  The array may still\n", str, q);
            PRINT_OUTPUT("be useful, but a full factorial would have at least as\n");
            PRINT_OUTPUT("many columns.\n");
        }

        return SUCCESS_CHECK;
    }

    int OAConstruct::bush(GF & gf, matrix<int> & A, int str, int ncol)
    {
        int q = gf.q;
        if (!bushcheck(q, str, ncol))
        {
            return 0;
        }

        std::vector<int> coef(str);

        for (size_t i = 0; i < static_cast<size_t>(Primes::ipow(q, str)); i++)
        {
            itopoly(i, q, str - 1, coef);
            A(i,0) = coef[str - 1];
            for (size_t j = 0; j < static_cast<size_t>(ncol - 1); j++)
            {
                polyeval(gf, str - 1, coef, j, &(A(i,1 + j)));
            }
        }
        return 1;
    }

    int OAConstruct::addelkempcheck(int q, int p, int ncol)
    {
        std::string msg;
        if (p == 2 && q > 4)
        {
            msg = boost::str(boost::format("This Addelman-Kempthorne OA(2q^2,ncol,q,2) is only \n available for odd prime powers q and for even prime \n powers q<=4.  q=%d is not available, but a Bose Bush \n construction exists for that design. \n") % q);
            throw std::runtime_error(msg.c_str());
        }

        if (ncol > 2 * q + 1)
        {
            msg = boost::str(boost::format("The Addelman-Kempthorne construction needs ncol <= 2q+1. \n Can't have ncol = %d with q = %d, \n") % ncol % q);
            throw std::runtime_error(msg.c_str());
        }

        if (ncol == 2 * q + 1)
        {
            PRINT_OUTPUT("\nWarning: The Addelman-Kempthorne construction with ncol = 2q+1\n");
            PRINT_OUTPUT("has a defect.  While it is still an OA(2q^2,2q+1,q,2),\n");
            PRINT_OUTPUT("there exist some pairs of rows that agree in three columns.\n");
            PRINT_OUTPUT("The final column in the array is involved in all of these\n");
            PRINT_OUTPUT("triple coincidences.\n\n\n");
        }
        return SUCCESS_CHECK;
    }

    /* Implement Addelman and Kempthorne's 1961 A.M.S. method with n=2 */
    int OAConstruct::addelkemp(GF & gf, matrix<int> & A, int ncol)
    {
        int kay; /* A&K notation */
        int row, col, square, ksquare, temp;

        int p = gf.p;
        size_t q = gf.q;

        if (!addelkempcheck(q, p, ncol))return 0;

        std::vector<int> b(q);
        std::vector<int> c(q);
        std::vector<int> k(q);

        for (size_t i = 0; i < q; i++)
        { /* First q*q rows */
            square = gf.times(i,i);
            for (size_t j = 0; j < q; j++)
            {
                row = i * q + j;
                col = 0;
                if (col < ncol)
                {
                    A(row,col++) = j;
                }
                for (size_t m = 1; m < q && col < ncol; m++)
                {
                    A(row,col++) = gf.plus(i,gf.times(m,j));
                }
                for (size_t m = 0; m < q && col < ncol; m++)
                {
                    temp = gf.plus(j,gf.times(m,i));
                    A(row,col++) = gf.plus(temp,square); /* Rgt cols */
                }
                if (col < ncol)
                {
                    A(row,col++) = i;
                }
            }
        }

        if (p != 2) /* Constants kay,b,c,k for odd p */
        {
            Addelkemp::akodd(gf, &kay, b, c, k);
        }
        else /* Constants kay,b,c,k for even p */
        {
            Addelkemp::akeven(gf, &kay, b, c, k);
        }

        for (size_t i = 0; i < q; i++)
        { /* Second q*q rows */
            square = gf.times(i,i);
            ksquare = gf.times(kay,square);
            for (size_t j = 0; j < q; j++)
            {
                row = q * q + i * q + j;
                col = 0;
                if (col < ncol)
                {
                    A(row,col++) = j;
                }
                for (size_t m = 1; m < q && col < ncol; m++, col++)
                {
                    A(row,col) = gf.plus(A(row - q * q,col),b[m]);
                }
                if (col < ncol)
                {
                    A(row,col++) = gf.plus(ksquare,j); /* q+1 */
                }
                for (size_t m = 1; m < q && col < ncol; m++)
                {
                    temp = gf.times(i,k[m]);
                    temp = gf.plus(ksquare,temp);
                    temp = gf.plus(j,temp);
                    A(row,col++) = gf.plus(temp,c[m]);
                }
                if (col < ncol)
                {
                    A(row,col++) = i;
                }
            }
        }

        return 1;
    }

    int OAConstruct::bosebushcheck(int q, int p, int ncol)
    {
        std::string msg;
        if (p != 2)
        {
            msg = "This version of Bose and Bush needs q=2^n for some n.\n";
            throw std::runtime_error(msg.c_str());
        }

        if (ncol > 2 * q + 1)
        {
            msg = boost::str(boost::format("The Bose-Bush construction needs ncol <= 2q+1. \n Can't have ncol = %d with q = %d,\n") % ncol % q);
            throw std::runtime_error(msg.c_str());
        }

        if (ncol == 2 * q + 1)
        {
            PRINT_OUTPUT("\nWarning: The Bose-Bush construction with ncol = 2q+1\n");
            PRINT_OUTPUT("has a defect.  While it is still an OA(2q^2,2q+1,q,2),\n");
            PRINT_OUTPUT("there exist some pairs of rows that agree in three columns.\n\n\n");
        }
        return SUCCESS_CHECK;
    }

    /* Implement Bose and Bush's 1952 A.M.S. method with p=2, u=1 */
    int OAConstruct::bosebush(GF & gf, matrix<int> & B, int ncol)
    {
        int p, irow;
        int mul;

        p = gf.p; /* GF(q) used to generate design with q/2 levels */
        size_t q = static_cast<size_t>(gf.q);
        size_t s = q / 2; /* number of levels in design */
        matrix<int> A(s, q);

        if (!bosebushcheck(s, p, ncol))
        {
            return 0;
        }

        irow = 0;
        for (size_t i = 0; i < q; i++)
        {
            for (size_t j = 0; j < q; j++)
            {
                mul = gf.times(i,j);
                mul = mul % s;
                for (size_t k = 0; k < s; k++)
                {
                    A(k,j) = gf.plus(mul,k);
                }
            }
            for (size_t k = 0; k < s; k++)
            {
                for (size_t j = 0; j < static_cast<size_t>(ncol) && j < 2 * s + 1; j++)
                {
                    B(irow,j) = A(k,j);
                }
                if (static_cast<size_t>(ncol) == 2 * s + 1)
                {
                    B(irow,ncol - 1) = i % s;
                }
                irow++;
            }
        }
        return 1;
    }

    int OAConstruct::bosebushlcheck(int s, int p, int lam, int ncol)
    {
        std::string msg;
        if (!Primes::isprime(p))
        {
            msg = "Bose Bush routine given a nonprime.\n";
            throw std::runtime_error(msg.c_str());
        }

        if (ncol > lam * s + 1)
        {
            msg = boost::str(boost::format("The Bose-Bush construction needs ncol <= lambda*q+1. \n Can't have ncol = %d with lam = %d and q = %d,\n") % ncol % lam % s);
            throw std::runtime_error(msg.c_str());
        }

        if (ncol == lam * s + 1)
        {
            PRINT_OUTPUT("\nWarning: The Bose-Bush construction with ncol = lambda*q+1\n");
            PRINT_OUTPUT("has a defect.  While it is still an OA(lambda*q^2,lambda*q+1,q,2),\n");
            PRINT_OUTPUT("it may have worse coincidence properties than\n");
            PRINT_OUTPUT("OA(lambda*q^2,lambda*q+1,q,2).\n");
        }
        return SUCCESS_CHECK;
    }

    int OAConstruct::bosebushl(GF & gf, int lam, matrix<int> & B, int ncol)
    /* Implement Bose and Bush's 1952 A.M.S. method with given lambda */
    {
        int p, irow;
        int mul;

        p = gf.p; /* GF(q) used to generate design with q/lam levels */
        size_t q = static_cast<size_t>(gf.q);
        size_t s = q / lam; /* number of levels in design */
        matrix<int> A(s,q);

        if (!bosebushlcheck(s, p, lam, ncol))
        {
            return 0;
        }

        irow = 0;
        for (size_t i = 0; i < q; i++)
        {
            for (size_t j = 0; j < q; j++)
            {
                mul = gf.times(i,j);
                mul = mul % s;
                for (size_t k = 0; k < s; k++)
                {
                    A(k,j) = gf.plus(mul,k);
                }
            }
            for (size_t k = 0; k < s; k++)
            {
                for (size_t j = 0; j < static_cast<size_t>(ncol) && j < lam * s + 1; j++)
                {
                    B(irow,j) = A(k,j);
                }
                if (ncol == lam * static_cast<int>(s) + 1)
                {
                    B(irow,ncol - 1) = i % s;
                }
                irow++;
            }
        }
        return 1;
    }

} // end namespace  
