/**
 * @file runif.cpp
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

#include "runif.h"

namespace oacpp
{
    // must define static member variables in the .cpp file
    int RUnif::m_i;
    int RUnif::m_j;
    int RUnif::m_jent;
    int RUnif::m_k;
    int RUnif::m_l;
    double RUnif::u[97 + 1];
    double RUnif::c;
    double RUnif::cd;
    double RUnif::cm;
    int RUnif::ip;
    int RUnif::jp;

    int RUnif::mod(int a, int b)
    /*int  a,b;*/
    {
        int ans;
        ans = a % b;
        if (ans >= 0)return ans;
        else return ans + b;
    }

    int RUnif::seedok(int is, int js, int ks, int ls) /*  1 iff seed is ok   */
    /*int is,js,ks,ls;*/
    {
        if (is == 1 && js == 1 && ks == 1 && ls == 1)return 0;
        if (is < 1 || js < 1 || ks < 1 || ls < 1)return 0;
        if (is > 168 || js > 168 || ks > 168 || ls > 168)return 0;
        return 1;
    }

    void RUnif::seed(int is, int js, int ks, int ls)
    /*int is,js,ks,ls;*/
    {
        m_jent = 0;

        if (seedok(is, js, ks, ls))
        {
            m_i = is;
            m_j = js;
            m_k = ks;
            m_l = ls;
        }
        else
        {
            PRINT_OUTPUT("Error: Invalid seed %d %d %d %d\n", is, js, ks, ls);
            PRINT_OUTPUT("Must be four integers between 1 and 168, and\n");
            PRINT_OUTPUT("must not all be 1.  Seed not changed.\n");
        }
    }

    void RUnif::runif(std::vector<double> & x, int n)
    {
        // if the seed is not ok, it was set by default and not through seed()
        if (!seedok(m_i, m_j, m_k, m_l))
        {
            m_jent = 0;
            m_i = 12;
            m_j = 34;
            m_k = 56;
            m_l = 78;
        }
        ranums(x, n);
    }

    void RUnif::ranums(std::vector<double> & x, int n)
    /*int     n;
    double *x;*/
    {
        int ii, jj, m;
        double s, t, uni;

        // if the seed is not ok, it was set by default and not through seed()
        if (!seedok(m_i, m_j, m_k, m_l))
        {
            m_jent = 0;
            m_i = 12;
            m_j = 34;
            m_k = 56;
            m_l = 78;
        }

        if (m_jent != 0) goto L30;
        m_jent = 1;
        for (ii = 1; ii <= 97; ii++)
        { /* do 20 ii=1,97 */
            s = 0.0;
            t = 0.5;
            for (jj = 1; jj <= 24; jj++)
            { /* do 10 jj=1,24 */
                m = mod(mod(m_i*m_j, 179) * m_k, 179);
                m_i = m_j;
                m_j = m_k;
                m_k = m;
                m_l = mod(53 * m_l + 1, 169);
                if (mod(m_l * m, 64) >= 32) s = s + t;
                t = 0.5 * t;
            } /* 10   continue */
            u[ii] = s;
        } /* 20   continue */

        c = 362436.0 / 16777216.0;
        cd = 7654321.0 / 16777216.0;
        cm = 16777213.0 / 16777216.0;
        ip = 97;
        jp = 33;

L30:
        for (ii = 1; ii <= n; ii++)
        { /*  ii do 40 ii=1,n */
            uni = u[ip] - u[jp];
            if (uni < 0.0) uni = uni + 1.0;
            u[ip] = uni;
            ip = ip - 1;
            if (ip == 0) ip = 97;
            jp = jp - 1;
            if (jp == 0) jp = 97;
            c = c - cd;
            if (c < 0.0) c = c + cm;
            uni = uni - c;
            if (uni < 0.0) uni = uni + 1.0;
            x[ii - 1] = uni;
        } /* 40   continue */
    }

} // end namespace
