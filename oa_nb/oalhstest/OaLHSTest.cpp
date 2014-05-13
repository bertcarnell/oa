#include "OaLHSTest.h"

namespace oalhs_test
{
        /**
     * check to determine of an lhs is valid.
     * if bTranspose==false, then sum the columns
     * if bTranspose==true, then sum the rows
     * @param result
     * @param bTranspose
     * @return 
     */
    bool oaLHSTest::isValidLHS(const bclib::matrix<int> & result)
    {
        int total = 0;
        bclib::matrix<int>::size_type cols = result.colsize();
        bclib::matrix<int>::size_type rows = result.rowsize();
        /*
        * verify that the result is a latin hypercube.  One easy check is to ensure
        * that the sum of the rows is the sum of the 1st N integers.  This check can
        * be fooled in one unlikely way...
        * if a column should be 1 2 3 4 6 8 5 7 9 10
        * the sum would be 10*11/2 = 55
        * the same sum could come from 5 5 5 5 5 5 5 5 5 10
        * but this is unlikely
        */
        // sum each column
        for (bclib::matrix<int>::size_type jcol = 0; jcol < cols; jcol++)
        {
            total = 0;
            for (bclib::matrix<int>::size_type irow = 0; irow < rows; irow++)
            {
                total += result(irow, jcol);
            }
            if (total != static_cast<int>(rows * (rows + 1) / 2))
            {
                return false;
            }
        }
        return true;
    }
    
    bool oaLHSTest::isValidLHS(const bclib::matrix<double> & result)
    {
        bclib::matrix<int>::size_type n = result.rowsize();
        bclib::matrix<int>::size_type k = result.colsize();
        bclib::matrix<int> resultint = bclib::matrix<int>(n, k);
        bclib::matrix<double>::const_iterator it = result.begin();
        bclib::matrix<int>::iterator iti = resultint.begin();
        for (;it != result.end(); ++it, ++iti)
        {
            *iti = 1 + static_cast<int>(floor(static_cast<double>(n) * (*it)));
        }
        bool ret = isValidLHS(resultint);        
        return ret;
    }

	void oaLHSTest::Run()
	{
		printf("\toaLHSTest...");
		testOaLHS();
		testOaLHS_2();
        testGenerateOALHS();
		printf("passed\n");
	}

	void oaLHSTest::testOaLHS()
	{
		int n = 4;
		int k = 2;
        std::vector<int> oaseq = {1,1,
                                  1,2,
                                  2,1,
                                  2,2};
        bclib::matrix<int> oa = bclib::matrix<int>(n, k, oaseq);
        bclib::matrix<int> intlhs = bclib::matrix<int>(n, k);
        bclib::matrix<double> lhs = bclib::matrix<double>(n, k);
        
        bclib::CRandomStandardUniform oRandom = bclib::CRandomStandardUniform();
        oRandom.setSeed(1976, 1968);
        
        oalhslib::oaLHS(n, k, oa, intlhs, lhs, false, oRandom);
        
        bclib::Assert(oaseq.size(), oa.getDataVector().size());
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }
        
        bclib::Assert(k, intlhs.colsize(), "columnsize");
        bclib::Assert(k, lhs.colsize(), "columnsize");
        bclib::Assert(n, intlhs.rowsize(), "rowsize");
        bclib::Assert(n, lhs.rowsize(), "rowsize");
        bclib::Assert(isValidLHS(intlhs), "valid integer lhs");
        bclib::Assert(isValidLHS(lhs), "valid double lhs");
        
        oalhslib::oaLHS(n, k, oa, intlhs, false);
        bclib::Assert(oaseq.size(), oa.getDataVector().size());
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }
        bclib::Assert(k, intlhs.colsize(), "columnsize");
        bclib::Assert(n, intlhs.rowsize(), "rowsize");
        bclib::Assert(isValidLHS(intlhs), "valid integer lhs for deterministic oalhs");
        
        std::vector<int> lhsintseq = {1,1,
                                  2,3,
                                  3,2,
                                  4,4};
        for (unsigned int i = 0; i < lhsintseq.size(); i++)
        {
            bclib::Assert(lhsintseq[i], intlhs.getDataVector()[i], "deterministic oalhs values");
        }
        
	}

	void oaLHSTest::testOaLHS_2()
	{
		int n = 9;
		int k = 3;
        std::vector<int> oaseq = {1,1,1,
                                  1,2,2,
                                  1,3,3,
                                  2,1,3,
                                  2,2,1,
                                  2,3,2,
                                  3,1,2,
                                  3,2,3,
                                  3,3,1};
        bclib::matrix<int> oa = bclib::matrix<int>(n, k, oaseq);
        bclib::matrix<int> intlhs = bclib::matrix<int>(n, k);
        bclib::matrix<double> lhs = bclib::matrix<double>(n, k);
        
        bclib::CRandomStandardUniform oRandom = bclib::CRandomStandardUniform();
        oRandom.setSeed(1976, 1968);
        
        oalhslib::oaLHS(n, k, oa, intlhs, lhs, false, oRandom);
        
        bclib::Assert(oaseq.size(), oa.getDataVector().size());
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }
        
        bclib::Assert(k, intlhs.colsize(), "columnsize");
        bclib::Assert(k, lhs.colsize(), "columnsize");
        bclib::Assert(n, intlhs.rowsize(), "rowsize");
        bclib::Assert(n, lhs.rowsize(), "rowsize");
        bclib::Assert(isValidLHS(intlhs), "valid integer lhs");
        bclib::Assert(isValidLHS(lhs), "valid double lhs");
        
        oalhslib::oaLHS(n, k, oa, intlhs, false);
        bclib::Assert(oaseq.size(), oa.getDataVector().size());
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }
        bclib::Assert(k, intlhs.colsize(), "columnsize");
        bclib::Assert(n, intlhs.rowsize(), "rowsize");
        bclib::Assert(isValidLHS(intlhs), "valid integer lhs for deterministic oalhs");
        
        std::vector<int> lhsintseq = {1,1,1,
                                  2,4,4,
                                  3,7,7,
                                  4,2,8,
                                  5,5,2,
                                  6,8,5,
                                  7,3,6,
                                  8,6,9,
                                  9,9,3};
        for (unsigned int i = 0; i < lhsintseq.size(); i++)
        {
            bclib::Assert(lhsintseq[i], intlhs.getDataVector()[i], "deterministic oalhs values");
        }
        
	}
    
    void oaLHSTest::testGenerateOALHS()
    {
        bclib::matrix<double> oalhs = bclib::matrix<double>();
        
        printf("\tAsk for a 4, 2 design that should be possible\n");
        oalhslib::generateOALHS(4,2,oalhs,true,true);
        bclib::Assert(oalhs.rowsize() == 4);
        bclib::Assert(oalhs.colsize() == 2);
        
        printf("\tAsk for a 20, 3 that is not possible but needs a larger design\n");
        // ask for a oalhs that is not possible so a larger design is given
        oalhslib::generateOALHS(20,3,oalhs,true,true);
        bclib::Assert(oalhs.rowsize() == 25);
        bclib::Assert(oalhs.colsize() == 3);

        printf("\tAsk for a 20, 3 that is not possible but needs a smaller design\n");
        // ask for a oalhs that is not possible so a smaller design is given
        oalhslib::generateOALHS(20,3,oalhs,false,true);
        bclib::Assert(oalhs.rowsize() == 18);
        bclib::Assert(oalhs.colsize() == 3);
        
        printf("\tAsk for a 20, 10 that is not possible but needs a larger design\n");
        // ask for a oalhs that has too many variables and ask for a larger design
        oalhslib::generateOALHS(20,10,oalhs,true,true);
        bclib::Assert(oalhs.rowsize() == 54);
        bclib::Assert(oalhs.colsize() == 10);
    }
}
