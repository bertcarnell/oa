/**
 * @file OaLHSTest.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2019, Robert Carnell
 *
 * @license <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "OaLHSTest.h"

namespace oalhs_test
{
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
        
		// test that the input oa was unchanged
        bclib::Assert(static_cast<int>(oaseq.size()), static_cast<int>(oa.getDataVector().size()));
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }

        bclib::Assert(k, static_cast<int>(intlhs.colsize()), "columnsize");
        bclib::Assert(k, static_cast<int>(lhs.colsize()), "columnsize");
        bclib::Assert(n, static_cast<int>(intlhs.rowsize()), "rowsize");
        bclib::Assert(n, static_cast<int>(lhs.rowsize()), "rowsize");
        bclib::Assert(isValidLHS(intlhs), "valid integer lhs");
        bclib::Assert(isValidLHS(lhs), "valid double lhs");
        
        oalhslib::oaLHS(n, k, oa, intlhs, false);
        bclib::Assert(static_cast<int>(oaseq.size()), static_cast<int>(oa.getDataVector().size()));
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }
        bclib::Assert(k, static_cast<int>(intlhs.colsize()), "columnsize");
        bclib::Assert(n, static_cast<int>(intlhs.rowsize()), "rowsize");
        bclib::Assert(isValidLHS(intlhs), "valid integer lhs for deterministic oalhs");

        std::vector<int> lhsintseq = {1,1,
                                  2,3,
                                  3,2,
                                  4,4};
        for (unsigned int i = 0; i < lhsintseq.size(); i++)
        {
            bclib::Assert(lhsintseq[i], intlhs.getDataVector()[i], "deterministic oalhs values");
        }
        
		// debugging whether the printing methods have a memory leak
		oalhslib::oaLHS(n, k, oa, intlhs, lhs, true, oRandom);

		// debugging the same R method that caused the memory leak
		// #' oa <- createBose(3, 4, TRUE)
		// #' B <- oa_to_oalhs(9, 4, oa, FALSE)
		oacpp::COrthogonalArray coa = oacpp::COrthogonalArray();
		int q = 3;
		k = 4;
		n = 0;
		coa.bose(q, k, &n);
		bclib::Assert(9, n, "Check Bose output n");
		oalhslib::oaLHS(n, k, coa.getoa(), intlhs, lhs, true, oRandom);
		bclib::Assert(oaLHSTest::isValidLHS(intlhs));
		bclib::Assert(oaLHSTest::isValidLHS(lhs));
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
        
        bclib::Assert(static_cast<int>(oaseq.size()), static_cast<int>(oa.getDataVector().size()));
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }
        
        bclib::Assert(k, static_cast<int>(intlhs.colsize()), "columnsize");
        bclib::Assert(k, static_cast<int>(lhs.colsize()), "columnsize");
        bclib::Assert(n, static_cast<int>(intlhs.rowsize()), "rowsize");
        bclib::Assert(n, static_cast<int>(lhs.rowsize()), "rowsize");
        bclib::Assert(isValidLHS(intlhs), "valid integer lhs");
        bclib::Assert(isValidLHS(lhs), "valid double lhs");
        
        oalhslib::oaLHS(n, k, oa, intlhs, false);
        bclib::Assert(static_cast<int>(oaseq.size()), static_cast<int>(oa.getDataVector().size()));
        for (unsigned int i = 0; i < oaseq.size(); i++)
        {
            bclib::Assert(oaseq[i], oa.getDataVector()[i]);
        }
        bclib::Assert(k, static_cast<int>(intlhs.colsize()), "columnsize");
        bclib::Assert(n, static_cast<int>(intlhs.rowsize()), "rowsize");
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
		bool methodVerbose = false;

        bclib::matrix<double> oalhs = bclib::matrix<double>();
		bclib::CRandomStandardUniform oRandom = bclib::CRandomStandardUniform();
		oRandom.setSeed(1976, 1968);
        
		if (methodVerbose)
		{
			printf("\n");
			printf("\tAsk for a 4, 2 design that should be possible\n");
		}
        oalhslib::generateOALHS(4, 2, oalhs, true, methodVerbose, oRandom);
        bclib::Assert(oalhs.rowsize() == 4, "generate 1");
        bclib::Assert(oalhs.colsize() == 2, "generate 2");
		bclib::Assert(oalhs(0, 0) != 0.0);
		bclib::Assert(oalhs(0, 1) != 0.0);
		bclib::Assert(oalhs(1, 0) != 0.0);
		bclib::Assert(isValidLHS(oalhs), "GenerateOALhs error 1");

        if (methodVerbose)
			printf("\tAsk for a 20, 3 that is not possible but needs a larger design\n");
        oalhslib::generateOALHS(20, 3, oalhs, true, methodVerbose, oRandom);
        bclib::Assert(oalhs.rowsize() == 25, "generate 3");
        bclib::Assert(oalhs.colsize() == 3, "generate 4");
		bclib::Assert(isValidLHS(oalhs), "GenerateOALhs error 2");

        if (methodVerbose)
			printf("\tAsk for a 20, 3 that is not possible but needs a smaller design\n");
        oalhslib::generateOALHS(20, 3, oalhs, false, methodVerbose, oRandom);
        bclib::Assert(oalhs.rowsize() == 18, "generate 5");
        bclib::Assert(oalhs.colsize() == 3, "generate 6");
		bclib::Assert(isValidLHS(oalhs), "GenerateOALhs error 3");

        if (methodVerbose)
			printf("\tAsk for a 20, 10 that is not possible but needs a larger design\n");
        oalhslib::generateOALHS(20, 10, oalhs, true, methodVerbose, oRandom);
        bclib::Assert(oalhs.rowsize() == 54, "generate 7");
        bclib::Assert(oalhs.colsize() == 10, "generate 8");
		bclib::Assert(isValidLHS(oalhs), "GenerateOALhs error 4");
	}
}
