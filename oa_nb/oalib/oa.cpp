/**
 * @file oa.cpp
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

#include "oa.h"

namespace oacpp
{
    /*  OUTPUT    OUTPUT    OUTPUT    OUTPUT    OUTPUT    OUTPUT    OUTPUT  */

    /*  READ    READ    READ    READ    READ    READ    READ    READ    READ  */

    /*  WORK    WORK    WORK    WORK    WORK    WORK    WORK    WORK    WORK  */

    void OrthogonalArrayStrength::OA_strworkcheck(double work, int str)
    {
        if (work > BIGWORK)
        {
            PRINT_OUTPUT("If the array has strength %d, %g comparisons will\n",
                    str, work);
            PRINT_OUTPUT("be required to prove it.  This might take a long time.\n");
            PRINT_OUTPUT("This warning is triggered when more than %d comparisons\n",
                    BIGWORK);
            PRINT_OUTPUT("are required.  To avoid this warning increase BIGWORK in\n");
            PRINT_OUTPUT("oa.h.  Intermediate results will be printed.\n\n");
            fflush(stderr);
        }
        else if (work > MEDWORK)
        {
            PRINT_OUTPUT("Since more than %d comparisons may be required to\n", MEDWORK);
            PRINT_OUTPUT("to check whether the array has strength %d, intermediate\n",
                    str);
            PRINT_OUTPUT("results will be printed.  To avoid this warning increase\n");
            PRINT_OUTPUT("MEDWORK in oa.h\n\n");
            fflush(stderr);
        }
    }

    /*  STRENGTH    STRENGTH    STRENGTH    STRENGTH    STRENGTH  */


    /*
         Calculate and return the strength of the array A.

    verbose = 0   =>   No printed output
    verbose = 1   =>   Only stderr output
    verbose = 2   =>   Output to both stdout and stderr

     */
    void OrthogonalArrayStrength::OA_strength(int q, int nrow, int ncol, matrix<int> & A, int* str, int verbose)
    {
        *str = -1;

        if (OA_str0(q, nrow, ncol, A, verbose))
            *str = 0;
        else
            return;
        if (OA_str1(q, nrow, ncol, A, verbose))
            *str = 1;
        else
            return;
        while (OA_strt(q, nrow, ncol, A, *str + 1, verbose))
            (*str)++;
        return;
    }

    /* Check strength 0 */
    int OrthogonalArrayStrength::OA_str0(int q, int nrow, int ncol, matrix<int> & A, int verbose)
    {
        int i, j1;

        for (j1 = 0; j1 < ncol; j1++)
            for (i = 0; i < nrow; i++)
                if (A(i,j1) < 0 || A(i,j1) >= q)
                {
                    if (verbose >= 2)
                    {
                        PRINT_OUTPUT("Array is not even of strength 0, that is there are elements\n");
                        PRINT_OUTPUT("other than integers 0 through %d inclusive in it.\n", q);
                        PRINT_OUTPUT("The first exception is A[%d,%d] = %d.\n", i, j1, A(i,j1));
                    }
                    return 0;
                }
        if (verbose >= 2)
        {
            PRINT_OUTPUT("The array has strength (at least) 0.\n");
        }
        return SUCCESS_CHECK;
    }

    /* Check strength 1 */
    int OrthogonalArrayStrength::OA_str1(int q, int nrow, int ncol, matrix<int> & A, int verbose)
    {
        int i, j1, q1;
        int lambda, count;
        double work;

        if (nrow % q)
        {
            if (verbose >= 2)
            {
                PRINT_OUTPUT("The array cannot have strength 1, because the number\n");
                PRINT_OUTPUT("of rows %d is not a multiple of q = %d.\n", nrow, q);
            }
            return 0;
        }

        lambda = nrow / q;
        work = nrow * ncol * q * 1.0;
        OA_strworkcheck(work, 1);
        for (j1 = 0; j1 < ncol; j1++)
        {
            for (q1 = 0; q1 < q; q1++)
            {
                count = 0;
                for (i = 0; i < nrow; i++)
                    count += (A(i,j1) == q1);
                if (count != lambda)
                {
                    if (verbose >= 2)
                    {
                        PRINT_OUTPUT("Array is not of strength 1.  The first violation arises for\n");
                        PRINT_OUTPUT("the number of times A[,%d] = %d.\n",
                                j1, q1);
                        PRINT_OUTPUT("This happened in %d rows, it should have happened in %d rows.\n",
                                count, lambda);
                    }
                    return 0;
                }
            }
            if (work > MEDWORK && verbose > 0)
                PRINT_OUTPUT("No violation of strength 1 involves column %d.\n", j1);
        }
        if (verbose >= 2)
        {
            PRINT_OUTPUT("The array has strength (at least) 1.\n");
        }
        return 1;
    }

    /* Check strength 2  */
    int OrthogonalArrayStrength::OA_str2(int q, int nrow, int ncol, matrix<int> & A, int verbose)
    {
        int i, j1, j2, q1, q2;
        int lambda, count;
        double work;

        if (ncol < 2)
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("Array has only %d column(s).  At least two\n", ncol);
                PRINT_OUTPUT("columns are necessary for strength 2 to make sense.\n");
            }
            return 0;
        }
        if (nrow % (q * q))
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("The array cannot have strength 2, because the number\n");
                PRINT_OUTPUT("of rows %d is not a multiple of q^2 = %d^2 = %d.\n", nrow, q, q * q);
            }
            return 0;
        }

        lambda = nrow / (q * q);
        work = nrow * ncol * (ncol - 1.0) * q * q / 2.0;
        OA_strworkcheck(work, 2);

        for (j1 = 0; j1 < ncol; j1++)
        {
            for (j2 = j1 + 1; j2 < ncol; j2++)
            {
                for (q1 = 0; q1 < q; q1++)
                    for (q2 = 0; q2 < q; q2++)
                    {
                        count = 0;
                        for (i = 0; i < nrow; i++)
                            count += (A(i,j1) == q1) && (A(i,j2) == q2);
                        if (count != lambda)
                        {
                            if (verbose >= 2)
                            {
                                PRINT_OUTPUT("Array is not of strength 2.  The first violation arises for\n");
                                PRINT_OUTPUT("the number of times (A[,%d],A[,%d]) = (%d,%d).\n",
                                        j1, j2, q1, q2);
                                PRINT_OUTPUT("This happened in %d rows, it should have happened in %d rows.\n",
                                        count, lambda);
                            }
                            return 0;
                        }
                    }
            }
            if (work > MEDWORK && verbose > 0)
                PRINT_OUTPUT("No violation of strength 2 involves column %d.\n", j1);
        }

        if (verbose >= 2)
        {
            PRINT_OUTPUT("The array has strength (at least) 2.\n");
        }
        return 1;
    }

    /* Check strength 3  */
    int OrthogonalArrayStrength::OA_str3(int q, int nrow, int ncol, matrix<int> & A, int verbose)
    {
        int i, j1, j2, j3, q1, q2, q3;
        int lambda, count;
        double work;

        if (ncol < 3)
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("Array has only %d column(s).  At least three\n", ncol);
                PRINT_OUTPUT("columns are necessary for strength 3 to make sense.\n");
            }
            return 0;
        }
        if (nrow % (q * q * q))
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("The array cannot have strength 3, because the number\n");
                PRINT_OUTPUT("of rows %d is not a multiple of q^3 = %d^3 = %d.\n", nrow, q, q * q * q);
            }
            return 0;
        }

        lambda = nrow / (q * q * q);
        work = nrow * ncol * (ncol - 1.0)*(ncol - 2.0) * q * q * q / 6.0;
        OA_strworkcheck(work, 3);

        for (j1 = 0; j1 < ncol; j1++)
        {
            for (j2 = j1 + 1; j2 < ncol; j2++)
                for (j3 = j2 + 1; j3 < ncol; j3++)
                {
                    for (q1 = 0; q1 < q; q1++)
                        for (q2 = 0; q2 < q; q2++)
                            for (q3 = 0; q3 < q; q3++)
                            {
                                count = 0;
                                for (i = 0; i < nrow; i++)
                                    count += (A(i,j1) == q1) && (A(i,j2) == q2) && (A(i,j3) == q3);
                                if (count != lambda)
                                {
                                    if (verbose >= 2)
                                    {
                                        PRINT_OUTPUT("Array is not of strength 3.  The first violation arises for\n");
                                        PRINT_OUTPUT("the number of times (A[,%d],A[,%d],A[,%d]) = (%d,%d,%d).\n",
                                                j1, j2, j3, q1, q2, q3);
                                        PRINT_OUTPUT("This happened in %d rows, it should have happened in %d rows.\n",
                                                count, lambda);
                                    }
                                    return 0;
                                }
                            }
                }
            if (work > MEDWORK && verbose > 0)
            {
                PRINT_OUTPUT("No violation of strength 3 involves column %d.\n", j1);
            }
        }
        if (verbose >= 2)
        {
            PRINT_OUTPUT("The array has strength (at least) 3.\n");
        }
        return 1;
    }

    /* Check strength 4  */
    int OrthogonalArrayStrength::OA_str4(int q, int nrow, int ncol, matrix<int> & A, int verbose)
    {
        int i, j1, j2, j3, j4, q1, q2, q3, q4;
        int lambda, count;
        double work;

        if (ncol < 4)
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("Array has only %d column(s).  At least four\n", ncol);
                PRINT_OUTPUT("columns are necessary for strength 4 to make sense.\n");
            }
            return 0;
        }
        if (nrow % (q * q * q * q))
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("The array cannot have strength 4, because the number\n");
                PRINT_OUTPUT("of rows %d is not a multiple of q^4 = %d^4 = %d.\n", nrow, q, q * q * q * q);
            }
            return 0;
        }

        lambda = nrow / (q * q * q * q);
        work = nrow * ncol * (ncol - 1.0)*(ncol - 2.0)*(ncol - 3.0) * q * q * q * q / 24.0;
        OA_strworkcheck(work, 4);

        for (j1 = 0; j1 < ncol; j1++)
        {
            for (j2 = j1 + 1; j2 < ncol; j2++)
                for (j3 = j2 + 1; j3 < ncol; j3++)
                    for (j4 = j3 + 1; j4 < ncol; j4++)
                    {
                        for (q1 = 0; q1 < q; q1++)
                            for (q2 = 0; q2 < q; q2++)
                                for (q3 = 0; q3 < q; q3++)
                                    for (q4 = 0; q4 < q; q4++)
                                    {
                                        count = 0;
                                        for (i = 0; i < nrow; i++)
                                            count += (A(i,j1) == q1) && (A(i,j2) == q2) && (A(i,j3) == q3) && (A(i,j4) == q4);
                                        if (count != lambda)
                                        {
                                            if (verbose >= 2)
                                            {
                                                PRINT_OUTPUT("Array is not of strength 4.  The first violation arises for\n");
                                                PRINT_OUTPUT("the number of times (A[,%d],A[,%d],A[,%d],A[,%d]) = (%d,%d,%d,%d).\n",
                                                        j1, j2, j3, j4, q1, q2, q3, q4);
                                                PRINT_OUTPUT("This happened in %d rows, it should have happened in %d rows.\n",
                                                        count, lambda);
                                            }
                                            return 0;
                                        }
                                    }
                    }
        }
        if (work > MEDWORK && verbose > 0)
        {
            PRINT_OUTPUT("No violation of strength 4 involves column %d.\n", j1);
        }

        if (verbose >= 2)
        {
            PRINT_OUTPUT("The array has strength (at least) 4.\n");
        }
        return 1;
    }

    /* Check strength t  */
    int OrthogonalArrayStrength::OA_strt(int q, int nrow, int ncol, matrix<int> & A, int t, int verbose)
    {
        int row, i, ic, iq, ctuples, qtuples;
        int lambda, count, match;
        double work;
        std::vector<int> clist, qlist;

        if (t < 0)
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("Don't know how to verify strength %d.  It doesn't\n", t);
                PRINT_OUTPUT("make sense.\n");
            }
            return 0;
        }
        if (ncol < t)
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("Array has only %d column(s).  At least %d\n", ncol, t);
                PRINT_OUTPUT("columns are necessary for strength %d to make sense.\n", t);
            }
            return 0;
        }
        if (t == 0)
        {
            return OA_str0(q, nrow, ncol, A, verbose);
        }
        if (nrow % Primes::ipow(q, t))
        {
            if (verbose > 0)
            {
                PRINT_OUTPUT("The array cannot have strength %d, because the number\n", t);
                PRINT_OUTPUT("of rows %d is not a multiple of q^%d = %d^%d = %d.\n",
                        nrow, t, q, t, Primes::ipow(q, t));
            }
            return 0;
        }

        lambda = nrow / Primes::ipow(q, t);
        work = nrow * Primes::ipow(q, t);
        ctuples = 1;

        clist = std::vector<int>(t);
        qlist = std::vector<int>(t);

        for (i = 0; i < t; i++)
        {
            work *= (ncol - i) / (i + 1.0);
            ctuples *= ncol - i;
            qlist[i] = 0;
            clist[i] = i;
        }
        for (i = 0; i < t; i++)
        {
            ctuples /= (i + 1);
        }
        qtuples = Primes::ipow(q, t);

        OA_strworkcheck(work, t);

        for (ic = 0; ic < ctuples; ic++)
        { /* Loop over ordered tuples of columns */
            for (iq = 0; iq < qtuples; iq++)
            { /* Loop over unordered tuples of symbols */
                count = 0;
                for (row = 0; row < nrow; row++)
                {
                    match = 1;
                    for (i = 0; i < t && match; i++)
                    {
                        match *= A(row,clist[i]) == qlist[i];
                    }
                    count += match;
                }
                if (count != lambda)
                {
                    if (verbose >= 2)
                    {
                        PRINT_OUTPUT("Array is not of strength %d.  The first violation arises for\n", t);
                        PRINT_OUTPUT("the number of times (");
                        for (i = 0; i < t; i++)
                        {
                            PRINT_OUTPUT("A(,%d)%s", clist[i], (i == t - 1) ? ")" : ",");
                        }
                        PRINT_OUTPUT(" = (");
                        for (i = 0; i < t; i++)
                        {
                            PRINT_OUTPUT("%d%s", qlist[i], (i == t - 1) ? ").\n" : ",");
                        }
                        PRINT_OUTPUT("This happened in %d rows, it should have happened in %d rows.\n",
                                count, lambda);
                    }
                    return 0;
                }
                for (i = t - 1; i >= 0; i--)
                {
                    qlist[i] = (qlist[i] + 1) % q;
                    if (qlist[i])
                    {
                        break;
                    }
                }
            }

            for (i = t - 1; i >= 0; i--)
            {
                clist[i] = (clist[i] + 1) % (ncol + i - t + 1);
                if (clist[i])
                {
                    break;
                }
            }

            if (work > MEDWORK && verbose > 0 &&
                  ((t == 1 || t > 1) && (clist[1] == 0))
                )
            {
                PRINT_OUTPUT("No violation of strength %d involves column %d.\n",
                    t, (clist[0] + ncol - 1) % ncol);
            }

            for (i = 1; i < t; i++)
            {
                if (clist[i] <= clist[i - 1])
                {
                    clist[i] = clist[i - 1] + 1;
                }
            }
        }

        if (verbose >= 2)
        {
            PRINT_OUTPUT("The array has strength (at least) %d.\n", t);
        }
        return 1;
    }
}// end namespace
