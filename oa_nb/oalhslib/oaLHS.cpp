#include "oaLHS.h"

namespace oalhslib
{
    typedef bclib::matrix<int>::size_type msize_type;
    typedef bclib::matrix<int>::columnwise_iterator columnit;
    typedef std::vector<int>::iterator viterator;
    typedef std::vector<int>::const_iterator vconstiterator;
    typedef std::vector<int>::size_type vsize_type;
    
    // oa is provided in an arbitrary way (not necessarily all columns with the same q)
    void oaLHS(int n, int k, const bclib::matrix<int> & oa, bclib::matrix<int> & intlhs,
            bclib::matrix<double> & lhs, bool bVerbose, 
            bclib::CRandom<double> & oRandom)
    {
        if (oa.rowsize() != static_cast<msize_type>(n) ||
                oa.colsize() != static_cast<msize_type>(k))
        {
            throw std::runtime_error("wrong size");
        }
        if (intlhs.rowsize() != oa.rowsize() ||
                intlhs.colsize() != oa.colsize())
        {
            intlhs = bclib::matrix<int>(oa.rowsize(), oa.colsize());
        }
        if (lhs.rowsize() != oa.rowsize() ||
                lhs.colsize() != oa.colsize())
        {
            lhs = bclib::matrix<double>(oa.rowsize(), oa.colsize());
        }
        // iterate over the columns and make a list of the unique elements in the column
        std::vector<std::vector<int> > uniqueLevelsVector = std::vector<std::vector<int> >(oa.colsize());        
        oalhslib::findUniqueColumnElements<int>(oa, uniqueLevelsVector);
        
        if (bVerbose)
        {
            printOAandUnique(oa, uniqueLevelsVector);
        }
        
        replaceOAValues(oa, uniqueLevelsVector, intlhs, oRandom, true);
        
        if (bVerbose)
        {
            printf("\ninteger lhs:\n%s\n", intlhs.toString());
        }

        // transform integer hypercube to a double hypercube
        for (msize_type jcol = 0; jcol < static_cast<msize_type>(k); jcol++)
        {
            for (msize_type irow = 0; irow < static_cast<msize_type>(n); irow++)
            {
                lhs(irow,jcol) = static_cast<double>(intlhs(irow,jcol) - 1);
            }
        }
        std::vector<double> randomunif = std::vector<double>(n*k);
        for (vsize_type i = 0; i < static_cast<vsize_type>(n*k); i++)
        {
            randomunif[i] = oRandom.getNextRandom();
        }
        bclib::matrix<double> randomMatrix(n, k, randomunif);
        for (msize_type jcol = 0; jcol < static_cast<msize_type>(k); jcol++)
        {
            for (msize_type irow = 0; irow < static_cast<msize_type>(n); irow++)
            {
                lhs(irow,jcol) += randomMatrix(irow, jcol);
                lhs(irow,jcol) /= static_cast<double>(n);
            }
        }
    }
    
    void printOAandUnique(const bclib::matrix<int> & oa, const std::vector<std::vector<int> > & uniqueLevelsVector)
    {
        printf("\ninitial oa:\n%s\n", oa.toString());
        printf("unique values per row:\n");
        for (vsize_type vi = 0; vi < uniqueLevelsVector.size(); vi++)
        {
            for (vsize_type vvi = 0; vvi < uniqueLevelsVector[vi].size(); vvi++)
            {
                printf("%d,", uniqueLevelsVector[vi][vvi]);
            }
            printf("\n");
        }
    }

    void oaLHS(int n, int k, const bclib::matrix<int> & oa, bclib::matrix<int> & intlhs,
            bool bVerbose)
    {
        if (oa.rowsize() != static_cast<msize_type>(n) ||
                oa.colsize() != static_cast<msize_type>(k))
        {
            throw std::runtime_error("wrong size");
        }
        if (intlhs.rowsize() != oa.rowsize() ||
                intlhs.colsize() != oa.colsize())
        {
            intlhs = bclib::matrix<int>(oa.rowsize(), oa.colsize());
        }
        // iterate over the columns and make a list of the unique elements in the column
        std::vector<std::vector<int> > uniqueLevelsVector = std::vector<std::vector<int> >(oa.colsize());        
        oalhslib::findUniqueColumnElements<int>(oa, uniqueLevelsVector);
        
        if (bVerbose)
        {
            printOAandUnique(oa, uniqueLevelsVector);
        }
        
        bclib::CRandomStandardUniform oRandom;
        replaceOAValues(oa, uniqueLevelsVector, intlhs, oRandom, false);
        
        if (bVerbose)
        {
            printf("\nintlhs:\n%s\n", intlhs.toString());
        }
    }
    
    void replaceOAValues(const bclib::matrix<int> & oa,
        const std::vector<std::vector<int> > & uniqueLevelsVector,
        bclib::matrix<int> & intlhs,
        bclib::CRandom<double> & oRandom,
        bool isRandom)
    {
        int basecount = 1;
        std::vector<int> randints;
        std::vector<double> randdouble;
        viterator tempit;
        for (msize_type i = 0; i < oa.colsize(); i++)
        {
            // reset the basecount for each column
            basecount = 1;
            for (vconstiterator vit = uniqueLevelsVector[i].begin(); vit != uniqueLevelsVector[i].end(); ++vit)
            {
                // count the number of times this value is in the oa column
                int tempcount = (int) std::count(oa.columnwisebegin(i), oa.columnwiseend(i), *vit);
                randints = std::vector<int>(tempcount);
                if (isRandom)
                {
                    randdouble = std::vector<double>(tempcount);
                    // get a random ordering for the digits
                    for (std::vector<double>::iterator i = randdouble.begin(); i != randdouble.end(); i++)
                    {
                        *i = oRandom.getNextRandom();
                    }
                    //lhslib::runif_std(tempcount, randdouble, oRandom);
                    bclib::findorder_zero(randdouble, randints);
                }
                else
                {
                    for (int count = 0; count < tempcount; count++)
                    {
                        randints[count] = count;
                    }
                }
                // replace the elements of intlhs corresponding to the current unique value
                viterator randintsit = randints.begin();
                for (msize_type irow = 0; irow < oa.rowsize(); irow++)
                {
                    if (oa(irow, i) == *vit && randintsit != randints.end())
                    {
                        intlhs(irow, i) = basecount + *randintsit;
                        ++randintsit;
                    }
                }
                basecount += tempcount;
            }
        }
    }
    
    void generateOALHS(int n, int k, bclib::matrix<double> & oalhs,
        bool bChooseLargerDesign, bool bVerbose)
    {
        if (bVerbose)
        {
            printf("\n");
        }
        int q_addelkemp = bChooseLargerDesign ? (int) ceil(sqrt((double) n / 2.0)) : (int) floor(sqrt((double) n / 2.0));
        while (oacpp::primes::isprimepow(q_addelkemp) == 0 && q_addelkemp >= 2)
        {
            if (bChooseLargerDesign)
            {
                q_addelkemp++;
            }
            else
            {
                q_addelkemp--;
            }
        }
        int n_addelkemp = 2*q_addelkemp*q_addelkemp;
        int k_addelkemp = k < 2*q_addelkemp + 1 ? k : 2*q_addelkemp + 1;
        if (bVerbose)
        {
            printf("Candidate OA:  AddelKemp with q=%d n=%d k=%d\n", q_addelkemp, n_addelkemp, k_addelkemp);
        }
        
        int q_addelkemp3 = bChooseLargerDesign ? (int) ceil(pow((double) n / 2.0, 1.0/3.0)) : (int) floor(pow((double) n / 2.0, 1.0/3.0));
        while (oacpp::primes::isprimepow(q_addelkemp3) == 0 && q_addelkemp3 >= 2)
        {
            if (bChooseLargerDesign)
            {
                q_addelkemp3++;
            }
            else
            {
                q_addelkemp3--;
            }
        }
        int n_addelkemp3 = 2*q_addelkemp3*q_addelkemp3*q_addelkemp3;
        int k_addelkemp3 = k < 2*q_addelkemp3*q_addelkemp3 + 2*q_addelkemp3 + 1 ? k : 2*q_addelkemp3*q_addelkemp3 + 2*q_addelkemp3 + 1;
        if (bVerbose)
        {
            printf("Candidate OA:  AddelKemp3 with q=%d n=%d k=%d\n", q_addelkemp3, n_addelkemp3, k_addelkemp3);
        }

        int q_bose = bChooseLargerDesign ? (int) ceil(sqrt((double) n)) : (int) floor(sqrt((double) n));
        while (oacpp::primes::isprimepow(q_bose) == 0 && q_bose >= 2)
        {
            if (bChooseLargerDesign)
            {
                q_bose++;
            }
            else
            {
                q_bose--;
            }
        }
        int n_bose = q_bose*q_bose;
        int k_bose = k < q_bose + 1 ? k : q_bose + 1;
        if (bVerbose)
        {
            printf("Candidate OA:  Bose with q=%d n=%d k=%d\n", q_bose, n_bose, k_bose);
        }

        int q_bosebush = bChooseLargerDesign ? (int) ceil(sqrt((double) n / 2.0)) : (int) floor(sqrt((double) n / 2.0));
        if (q_bosebush % 2)
        {
            if (bChooseLargerDesign)
            {
                q_bosebush++;
            }
            else
            {
                q_bosebush--;
            }
        }
        int n_bosebush = 2*q_bosebush*q_bosebush;
        int k_bosebush = k < q_bosebush + 1 ? k : q_bosebush + 1;
        if (bVerbose)
        {
            printf("Candidate OA:  BoseBush with q=%d n=%d k=%d\n", q_bosebush, n_bosebush, k_bosebush);
        }
        
        std::vector<std::string> types = std::vector<std::string>();
        types.push_back("addelkemp");
        types.push_back("addelkemp3");
        types.push_back("bose");
        types.push_back("bosebush");
        std::vector<int> diffs = std::vector<int>();
        diffs.push_back(fabs((double) (n-n_addelkemp)));
        diffs.push_back(fabs((double) (n-n_addelkemp3)));
        diffs.push_back(fabs((double) (n-n_bose)));
        diffs.push_back(fabs((double) (n-n_bosebush)));
        
        // which is the smallest?
        std::vector<int> orders = std::vector<int>(diffs.size());
        bclib::findorder_zero(diffs, orders);
        oacpp::COrthogonalArray coa = oacpp::COrthogonalArray();
        
        std::string selected = types[orders[0]];
        
        bclib::matrix<int> intoalhs;
        if (selected == "addelkemp")
        {
            if (bVerbose)
            {
                printf("AddelKemp selected\n");
            }
            intoalhs = bclib::matrix<int>(n_addelkemp, k_addelkemp);
            oalhs = bclib::matrix<double>(n_addelkemp, k_addelkemp);
            coa.addelkemp(q_addelkemp, k_addelkemp, &n_addelkemp);
        }
        else if (selected == "addelkemp3")
        {
            if (bVerbose)
            {
                printf("AddelKemp3 selected\n");
            }
            intoalhs = bclib::matrix<int>(n_addelkemp3, k_addelkemp3);
            oalhs = bclib::matrix<double>(n_addelkemp3, k_addelkemp3);
            coa.addelkemp3(q_addelkemp3, k_addelkemp3, &n_addelkemp3);
        }
        else if (selected == "bose")
        {
            if (bVerbose)
            {
                printf("Bose selected\n");
            }
            intoalhs = bclib::matrix<int>(n_bose, k_bose);
            oalhs = bclib::matrix<double>(n_bose, k_bose);
            coa.bose(q_bose, k_bose, &n_bose);
        }
        else if (selected == "bosebush")
        {
            if (bVerbose)
            {
                printf("BoseBush selected\n");
            }
            intoalhs = bclib::matrix<int>(n_bosebush, k_bosebush);
            oalhs = bclib::matrix<double>(n_bosebush, k_bosebush);
            coa.bosebush(q_bosebush, k_bosebush, &n_bosebush);
        }

        // create information for other types of oa and then pick the closest to the desired
    }

}
