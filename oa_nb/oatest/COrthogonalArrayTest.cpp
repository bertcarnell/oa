/**
 * @file COrthogonalArrayTest.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
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

#include "COrthogonalArrayTest.h"

namespace oaTest{
	void COrthogonalArrayTest::Run()
	{
		printf("\tCOrthogonalArray...");
		testAddelkemp();
        testAddelkempRange();
		testAddelkemp3();
        testAddelkemp3Range();
        //testAddelkempn(); // deprecated
        testBose();
        testBoseRange();
        testBoseBushRange();
        testBushRange();
        testBoseBushl();
        testBusht();
		printf("passed\n");
	}
    
    void COrthogonalArrayTest::testRange(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            std::vector<int> & q, std::vector<int> & ncol)
	{
        assert(q.size() == ncol.size());
        oacpp::COrthogonalArray coa;
        int n = 0;
        
        int i;
        int chunk = PARALLEL_CHUNK_SIZE;
        int threadid;

        #pragma omp parallel shared(chunk,q,ncol,f) private(i, threadid, coa, n)
        {
            #pragma omp for schedule(dynamic,chunk)
            for (i = 0; i < q.size(); i++)
            {
                try
                {
                    f(coa, q[i], ncol[i], &n);
                    standardChecks(coa.getoa(), q[i], ncol[i]);
                }
                catch (std::exception & e)
                {
                    std::printf("\n ** error on q=%d ncol=%d *****\n", q[i], ncol[i]);
                    std::printf("error = %s\n", e.what());
                }
            }
        }
    }
    
    void COrthogonalArrayTest::testException(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            int q, int ncol)
    {
        oacpp::COrthogonalArray coa;
        int n = 0;
        try
        {
            f(coa, q, ncol, &n);
        }
        catch (...)
        {
            Assert(true, "Exception Thrown as Expected");
            return;
        }
        Assert(false, "failed to throw exception\n");
    }
    
	void COrthogonalArrayTest::testAddelkemp()
	{
		int q = 2;
		int ncol = 2*q;
		int n = 2*q*q;
        oacpp::COrthogonalArray coa;
		coa.addelkemp(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

		q = 3;
		ncol = 2*q;
		n = 2*q*q;
		coa.addelkemp(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

		q = 3;
		ncol = 3;
		n = 2*q*q;
		coa.addelkemp(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::addelkemp;
        testException(f, 0, 0);
        testException(f, 6, 12);
        testException(f, 10, 2);
	}
    
	void COrthogonalArrayTest::testAddelkempRange()
	{
        std::vector<int> q = {2,3,4,5,7,9,11,13,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {2,3,4,5,7};
        std::vector<int> ncol(q.size());
        std::transform(q.begin(), q.end(), ncol.begin(), multiplyByTwo);
        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::addelkemp;
        testRange(f, q, ncol);
    }
    
   	void COrthogonalArrayTest::testAddelkemp3()
	{
		int q = 3;
		int ncol = 2*q*q + 2*q + 1;
		int n;
        oacpp::COrthogonalArray coa;
		coa.addelkemp3(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

		q = 3;
		ncol = 2*q*q + 2*q +1;
		coa.addelkemp3(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

		q = 3;
		ncol = 9;
		coa.addelkemp3(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::addelkemp3;
        testException(f, 0, 0);
        testException(f, 1, 12);
        testException(f, 6, 12);
	}

	void COrthogonalArrayTest::testAddelkemp3Range()
	{
        std::vector<int> q = {2,3,4,5,7,9,11,13,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {2,3,4,5,7};
        std::vector<int> ncol(q.size());
        std::transform(q.begin(), q.end(), ncol.begin(), multiplyByTwo);
        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::addelkemp3;
        testRange(f, q, ncol);
    }

	void COrthogonalArrayTest::testAddelkempn()
	{
        // design equivalent to Addelkemp3
		int q = 3;
		int ncol = 2*q*q + 2*q + 1;
		int n;
        int akn = 3;
        oacpp::COrthogonalArray coa;
        coa.addelkempn(akn, q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
	}

	void COrthogonalArrayTest::testBose()
	{
		int q = 2;
		int ncol = q;
		int n = 0;
        oacpp::COrthogonalArray coa;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

		q = 3;
		ncol = q;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

		q = 4;
		ncol = q;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

		q = 4;
		ncol = 3;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);

        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::bose;
        testException(f, 0, 0);
        testException(f, 1, 1);
        testException(f, 6, 3);
        testException(f, 3, 9);
    }

	void COrthogonalArrayTest::testBoseRange()
	{
        std::vector<int> q = {2,3,4,5,7,9,11,13,16,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {2,3,4,5,7,8,9};
        std::vector<int> ncol(q);
        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::bose;
        testRange(f, q, ncol);
    }

	void COrthogonalArrayTest::testBoseBushRange()
	{
        //std::vector<int> q = {2,3,4,5,7,11,13,17,19,23,29,31,37,41,43,49}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> pow = {1,2,3,4,5};
        std::vector<int> q(pow.size());
        std::transform(pow.begin(), pow.end(), q.begin(), powerOfTwo);
        std::vector<int> ncol(q.size());
        std::transform(q.begin(), q.end(), ncol.begin(), multiplyByTwo);
        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::bosebush;
        testRange(f, q, ncol);
    }

	void COrthogonalArrayTest::testBushRange()
	{
        // start at 4 since this is strength 3 for the standard bush design
        std::vector<int> q = {4,5,7,9,11,13,16,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {4,5};
        std::vector<int> ncol(q);
        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::bush;
        testRange(f, q, ncol);
    }
    
    void COrthogonalArrayTest::testBoseBushl()
    {
		int q = 2;
		int ncol = q;
        int lambda = 2;
		int n = 0;
        oacpp::COrthogonalArray coa;
		coa.bosebushl(lambda, q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
    }
    
    void COrthogonalArrayTest::testBusht()
    {
		int q = 3;
		int ncol = 3;
        int str = 2;
		int n = 0;
        oacpp::COrthogonalArray coa;
		coa.busht(str, q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
    }
} // end namespace
