/**
 * @file COrthogonalArrayTest.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * License <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
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

namespace oaTest {

	void COrthogonalArrayTest::Run()
	{
		printf("\tCOrthogonalArray...");
		testAddelkemp();
        testAddelkempRange();
		testAddelkemp3();
        testAddelkemp3Range();
        testAddelkempn();
        testBose();
        testBoseRange();
        testBoseBush();
        testBoseBushRange();
		testBush();
        testBushRange();
        testBoseBushl();
        testBoseBushlRange();
        testBusht();
        testOaagree();
        testOatriple();
        testOarand();
        testOastr();
        testOastr1();
        testOastr2();
        testOastr3();
        testOastr4();
		testOastrt();
		printf("passed\n");
	}
    
    void COrthogonalArrayTest::testRange(
            const std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            const std::vector<int> & q, const std::vector<int> & ncol)
	{
        bclib::Assert(q.size() == ncol.size());
        oacpp::COrthogonalArray coa;
        int n = 0;
        
        int i;
#ifdef _OPENMP
        int chunk = PARALLEL_CHUNK_SIZE;
        int threadid;
#endif

        #pragma omp parallel shared(chunk,q,ncol,f) private(i, threadid, coa, n)
        {
            #pragma omp for schedule(dynamic,chunk)
            for (i = 0; i < static_cast<int>(q.size()); i++)
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
    
    void COrthogonalArrayTest::testRange2(
            std::function<void(oacpp::COrthogonalArray&, int, int, int, int*)> & f,
            std::vector<int> & int1,
            std::vector<int> & q, 
            std::vector<int> & ncol)
	{
        bclib::Assert(q.size() == ncol.size());
        oacpp::COrthogonalArray coa;
        int n = 0;
        
        int i;
#ifdef _OPENMP
        int chunk = PARALLEL_CHUNK_SIZE;
        int threadid;
#endif

        #pragma omp parallel shared(chunk,q,ncol,f) private(i, threadid, coa, n)
        {
            #pragma omp for schedule(dynamic,chunk)
            for (i = 0; i < static_cast<int>(q.size()); i++)
            {
                try
                {
                    f(coa, int1[i], q[i], ncol[i], &n);
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
            const std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
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
            bclib::Assert(true, "Exception Thrown as Expected");
            return;
        }
        bclib::Assert(false, "failed to throw exception\n");
    }
    
	void COrthogonalArrayTest::testAddelkemp()
	{
		int q = 2;
		int ncol = 2*q;
		int n = 2*q*q;
        oacpp::COrthogonalArray coa;
		coa.addelkemp(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage() == "");

		q = 3;
		ncol = 2*q;
		n = 2*q*q;
		coa.addelkemp(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage() == "");

		q = 3;
		ncol = 3;
		n = 2*q*q;
		coa.addelkemp(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage() == "");

        q = 3;
        ncol = 2*q + 1;
        n = 0;
        coa.addelkemp(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(WARNING_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() > 0);

        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::addelkemp);
        testException(f, 0, 0);
        testException(f, 6, 12);
        testException(f, 10, 2);
        
        oacpp::GaloisField gf = oacpp::GaloisField();
        gf.q = 6;
        int kay = 0;
        std::vector<int> b = std::vector<int>(4);
        std::vector<int> c = std::vector<int>(4);
        std::vector<int> k = std::vector<int>(9);
        ASSERT_THROW(oacpp::oaaddelkemp::akeven(gf, &kay, b, c, k));
        
        gf = oacpp::GaloisField(3); 
        //gf.q = 3;
        //gf.p = 3;
        gf.root = std::vector<int>(gf.u_q);
        ASSERT_THROW(oacpp::oaaddelkemp::akodd(gf, &kay, b, c, k));
		
		int p = 2;
		q = 5;
		ncol = 3;
		// Error when p == 2 and q > 4
		ASSERT_THROW(oacpp::oaconstruct::addelkempcheck(q, p, ncol));
		
		q = 3;
		p = 2;
		ncol = 8;
		// Error when ncol > 2 * q + 1
		ASSERT_THROW(oacpp::oaconstruct::addelkempcheck(q, p, ncol));
	}
    
	void COrthogonalArrayTest::testAddelkempRange()
	{
        std::vector<int> q = {2,3,4,5,7,9,11,13,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {2,3,4,5,7};
        std::vector<int> ncol(q.size());
        std::transform(q.begin(), q.end(), ncol.begin(), multiplyByTwo);
		std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::addelkemp);
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
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		q = 3;
		ncol = 2*q*q + 2*q +1;
		coa.addelkemp3(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		q = 3;
		ncol = 9;
		coa.addelkemp3(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::addelkemp3);
        testException(f, 0, 0);
        testException(f, 1, 12);
        testException(f, 6, 12);
        
        q = 5;
        int p = 2;
        ncol = 7;
        // p == 2 && q > 4
        ASSERT_THROW(oacpp::oaaddelkemp::addelkemp3check(q, p, ncol));
		p = 3;
        q = 8;
        // q == 8
        ASSERT_THROW(oacpp::oaaddelkemp::addelkemp3check(q, p, ncol));
        q = 3;
        p = 2;
        ncol = 2*q*q + 2*q + 1 + 1;
        // ncol > 2*q*q + 2*q + 1
        ASSERT_THROW(oacpp::oaaddelkemp::addelkemp3check(q, p, ncol));
        
        bclib::matrix<int> A = bclib::matrix<int>(2,2);
        oacpp::GaloisField gf = oacpp::GaloisField(5);
        gf.p = 2;
        gf.q = 5;
        // addlekemp3check fails
        ASSERT_THROW(oacpp::oaaddelkemp::addelkemp3(gf, A, 3));
	}

	void COrthogonalArrayTest::testAddelkemp3Range()
	{
        std::vector<int> q = {2,3,4,5,7,9,11,13,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {2,3,4,5,7};
        std::vector<int> ncol(q.size());
        std::transform(q.begin(), q.end(), ncol.begin(), multiplyByTwo);
		std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::addelkemp3);
        testRange(f, q, ncol);
    }

	void COrthogonalArrayTest::testAddelkempn()
	{
        // should all akodd
		int q = 3; // p == 3, q = 3^1
		int ncol = 4;
		int n = 0;
		int akn = 3;
		oacpp::COrthogonalArray coa;
		coa.addelkempn(akn, q, ncol, &n);
		standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

        // should call akeven
        q = 4; // p == 2, q = 2^2
        ncol = 4;
        n = 0;
        akn = 3;
        coa.addelkempn(akn, q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		ncol = 5;
		n = 0;
		oacpp::COrthogonalArray coa2;
		coa2.addelkempn(akn, q, ncol, &n);
		standardChecks(coa2.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		// design equivalent to Addelkemp3 test
		ncol = 2*q*q + 2*q + 1; // 2*(q^akn - 1) / (q - 1) - 1 = 25
		n = 0;
        oacpp::COrthogonalArray coa3;
        coa3.addelkempn(akn, q, ncol, &n);
		standardChecks(coa3.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		q = 3;
		int p = 2;
		ncol = 7;
		akn = 1;
		// akn < 2
		ASSERT_THROW(oacpp::oaaddelkemp::addelkempncheck(q, p, akn, ncol));
        akn = 3;
		q = 8;
        p = 2;
        ncol = 5;
		// p == 2 && q > 4
		ASSERT_THROW(oacpp::oaaddelkemp::addelkempncheck(q, p, akn, ncol));
        akn = 2;
		p = 3;
		q = 9;
		ncol = 100;
		// ncol > 2*(q^akn - 1) / (q - 1) - 1 = 2*(9^2-1)/(9-1) -1 = 19
		ASSERT_THROW(oacpp::oaaddelkemp::addelkempncheck(q, p, akn, ncol));

		bclib::matrix<int> A = bclib::matrix<int>(2, 2);
		oacpp::GaloisField gf = oacpp::GaloisField(5);
		gf.p = 2;
		//gf.q = 5;
		// addlekemp3check fails
		ASSERT_THROW(oacpp::oaaddelkemp::addelkempn(gf, 3, A, 5));
	}

	void COrthogonalArrayTest::testBose()
	{
		int q = 2;
		int ncol = q;
		int n = 0;
        oacpp::COrthogonalArray coa;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		q = 3;
		ncol = q;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		q = 4;
		ncol = q;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		q = 4;
		ncol = 3;
		coa.bose(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

		std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::bose);
        testException(f, 0, 0);
        testException(f, 1, 1);
        testException(f, 6, 3);
        testException(f, 3, 9);
		
		q = 4;
		ncol = 10;
		// Error that ncol > q + 1
		ASSERT_THROW(oacpp::oaconstruct::bosecheck(q, ncol));
		ncol = -1;
		// Error that ncol <= 0
		ASSERT_THROW(oacpp::oaconstruct::bosecheck(q, ncol));
    }

	void COrthogonalArrayTest::testBoseRange()
	{
        std::vector<int> q = {2,3,4,5,7,9,11,13,16,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {2,3,4,5,7,8,9};
        std::vector<int> ncol(q);
		std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::bose);
        testRange(f, q, ncol);
    }
    
    void COrthogonalArrayTest::testBoseBush()
    {
		int q = 8; // 2^3
		int ncol = 5; // 5 << 2*8+1
		int n = 0;
		oacpp::COrthogonalArray coa = oacpp::COrthogonalArray();
		coa.bosebush(q, ncol, &n);
		standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode(), "Success not returned in testBoseBush (2)");
        bclib::Assert(coa.getMessage() == "", "erroneous message returned in testBoseBush (2)");

        q = 4; // 2^2
        ncol = 8; // 8 < 2*4+1
        n = 0;
        coa.bosebush(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode(), "Success not returned in testBoseBush (2)");
        bclib::Assert(coa.getMessage() == "", "erroneous message returned in testBoseBush (2)");

        q = 8; // 2^3
        ncol = 2*q + 1; // 17 = 2*8 + 1
        n = 0;
        coa.bosebush(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(WARNING_CHECK, coa.getReturnCode(), "Warning not triggered in testBoseBush");
        bclib::Assert(coa.getMessage().length() > 0, "Warning message not available in testBoseBush");

        n = 7;
        // error for q not a power of 2
        ASSERT_THROW(coa.bosebush(3, 5, &n));
		
		q = 2;
		int p = 3;
		ncol = 5;
		// Error when p != 2
		ASSERT_THROW(oacpp::oaconstruct::bosebushcheck(q, p, ncol));
		
		q = 2;
		p = 2;
		ncol = 7;
		// Error when ncol > 2*q + 1
		ASSERT_THROW(oacpp::oaconstruct::bosebushcheck(q, p, ncol));
    }

	void COrthogonalArrayTest::testBoseBushRange()
	{
        //std::vector<int> q = {2,3,4,5,7,11,13,17,19,23,29,31,37,41,43,49}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> pow = {1,2,3,4,5};
        std::vector<int> q(pow.size());
        std::transform(pow.begin(), pow.end(), q.begin(), powerOfTwo);
        std::vector<int> ncol(q.size());
        std::transform(q.begin(), q.end(), ncol.begin(), multiplyByTwo);
		std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::bosebush);
        testRange(f, q, ncol);
    }
	
	void COrthogonalArrayTest::testBush()
	{
		int q = 3;
		int ncol = 3;
		int n = 0;
		oacpp::COrthogonalArray coa;
		coa.bush(q, ncol, &n);
		standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);
        bclib::Assert(3 * 3 * 3, n);

        q = 2;
        ncol = 3;
        n = 0;
        coa.bush(q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(WARNING_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() > 0);
        bclib::Assert(2 * 2 * 2, n);

        q = 2;
		int str = 2;
		ncol = 5;
		// Error when ncol > q + 1
		ASSERT_THROW(oacpp::oaconstruct::bushcheck(q, str, ncol));
		
		q = 2;
		str = 5;
		ncol = 3;
		// Error when str > ncol
		ASSERT_THROW(oacpp::oaconstruct::bushcheck(q, str, ncol));
	}

	void COrthogonalArrayTest::testBushRange()
	{
        // start at 4 since this is strength 3 for the standard bush design
        std::vector<int> q = {4,5,7,9,11,13,16,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        //std::vector<int> q = {4,5};
        std::vector<int> ncol(q);
		std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::bush);
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
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());

        // errors
        // q not an integer power of a prime
        ASSERT_THROW(coa.bosebushl(lambda, 6, ncol, &n));
        // lambda not an integer power of a prime
        ASSERT_THROW(coa.bosebushl(6, q, ncol, &n));
        // lambda and q are not powers of the same prime
        ASSERT_THROW(coa.bosebushl(4, 9, ncol, &n));
		
		int s = 3;
		int p = 6;
		lambda = 2;
		ncol = 7;
		// Error when p is not prime
		ASSERT_THROW(oacpp::oaconstruct::bosebushlcheck(s, p, lambda, ncol));
		
		s = 3;
		p = 3;
		lambda = 2;
		ncol = 20;
		// Error when ncol > lambda * s + 1
		ASSERT_THROW(oacpp::oaconstruct::bosebushlcheck(s, p, lambda, ncol));

        q = 3;
        lambda = 3;
        ncol = 10;
        coa.bosebushl(lambda, q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(WARNING_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() > 0);
        
        q = 4; // 2^2
        lambda = 2;
        ncol = 9;
        coa.bosebushl(lambda, q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(WARNING_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() > 0);

		q = 4; // 2^2
		lambda = 2;
		ncol = 8;
		coa.bosebushl(lambda, q, ncol, &n);
		standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());

		q = 4; // 2^2
		lambda = 2;
		ncol = 10;
		// Error when ncol > lambda * s + 1
		ASSERT_THROW(coa.bosebushl(lambda, q, ncol, &n));
    }

    void COrthogonalArrayTest::testBoseBushlRange()
    {
        std::vector<int> q =      {2,4,3,9,27}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> ncol(q);
        std::vector<int> lambda = {2,2,3,3,3};
		std::function<void(oacpp::COrthogonalArray&, int, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::bosebushl);
        testRange2(f, lambda, q, ncol);
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
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);
        
        // strength must be >= 2
        ASSERT_THROW(coa.busht(1, q, ncol, &n));
    }

    void COrthogonalArrayTest::testBushtRange()
    {
        std::vector<int> q = {4,5,7,9,11,13,16,17,19,23,25,27,29}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> ncol(q);
        std::vector<int> str = {2,2,2,3,3,3,3,3,4,4,4,4,4};
		std::function<void(oacpp::COrthogonalArray&, int, int, int, int*)> f = std::mem_fn(&oacpp::COrthogonalArray::busht);
        testRange2(f, str, q, ncol);
    }
    
    void COrthogonalArrayTest::testOaagree()
    {
        oacpp::COrthogonalArray coa; 
        int n;
        coa.addelkemp3(3, 25, &n);
        int maxagr = coa.oaagree(false);
        bclib::Assert(9, maxagr, "Error in OA Agree");
    }
    
    void COrthogonalArrayTest::testOatriple()
    {
        oacpp::COrthogonalArray coa;
        int n;
        coa.addelkemp3(3, 25, &n);
        int num3 = coa.oatriple(false);
        bclib::Assert(123552, num3, "Error in OA triple");
    }
    
    void COrthogonalArrayTest::testOarand()
    {
        oacpp::COrthogonalArray coa = oacpp::COrthogonalArray();
        int n;
        coa.addelkemp3(3, 25, &n);
        // all between 1 and 168
        int is = 10;
        int js = 100;
        int ks = 101;
        int ls = 17;
        coa.oarand(is, js, ks, ls);
        bclib::Assert(2, coa.getoa().at(0,0), "Error in Oarand");
    }
    
    void COrthogonalArrayTest::testOastr()
    {
        oacpp::COrthogonalArray coa;
        int n;
        coa.addelkemp3(3, 25, &n);
        bclib::Assert(2, coa.oastr(false), "Error in oastr");

        // create an artificial array not even of strength 0
        int q = 4;
        std::vector<int> temp = { 0,5,1,0 };
        bclib::matrix<int> A = bclib::matrix<int>(2, 2, temp);
        int str = 0;
        oacpp::oastrength::OA_strength(q, A, &str, false);
        bclib::Assert(-1, str, "Artificial array should not even be strength 0");

        // create an artificial strength 0 array
        q = 4;
        temp = { 0,1,0,0 };
        A = bclib::matrix<int>(2, 2, temp);
        str = 0;
        oacpp::oastrength::OA_strength(q, A, &str, false);
        bclib::Assert(0, str, "Artificial array should be strength 0");

        // create an artificial strength 1 array
        q = 2;
        temp = { 0,1,1,0 };
        A = bclib::matrix<int>(2, 2, temp);
        str = 0;
        oacpp::oastrength::OA_strength(q, A, &str, false);
        bclib::Assert(1, str, "Artificial array should be strength 1");
    }

    void COrthogonalArrayTest::testOastr1()
    {
        oacpp::COrthogonalArray coa;
        int n;
        coa.addelkemp3(3, 25, &n);
        bclib::Assert(coa.oastr1(false), "Error in oastr1");

		oacpp::COrthogonalArray coa2;
		coa2.bose(2, 1, &n);
		bclib::Assert(coa2.oastr1(false), "Error 2 in oastr1");

        int q = 2;
        std::vector<int> temp = { 1,1,1,1 };
        bclib::matrix<int> A = bclib::matrix<int>(2, 2, temp);
        int test = oacpp::oastrength::OA_str1(q, A, false);
        bclib::Assert(FAILURE_CHECK, test, "error in testOastr1");

    }

    void COrthogonalArrayTest::testOastr2()
    {
        oacpp::COrthogonalArray coa;
        int n;
        coa.addelkemp3(3, 25, &n);
        bclib::Assert(coa.oastr2(false), "Error 1 in oastr2 (1)");

		oacpp::COrthogonalArray coa2;
		coa2.bose(2, 1, &n);
		bclib::Assert(coa2.oastr2(false), "Error 2 in oastr2 (2)");

		oacpp::COrthogonalArray coa3;
		coa3.bosebush(2, 4, &n);
		bclib::Assert(coa3.oastr2(false), "Error 3 in oastr2 (3)");

        int q = 3;
        std::vector<int> temp = { 1,1,1,1,1,1 };
        bclib::matrix<int> A = bclib::matrix<int>(6, 1, temp);
        int test = oacpp::oastrength::OA_str2(q, A, false); // Array only has one column
        bclib::Assert(FAILURE_CHECK, test, "error in oastr2 (4)");

        q = 3;
        temp = { 1,1,1,1,1,1 };
        A = bclib::matrix<int>(3, 2, temp);
        test = oacpp::oastrength::OA_str2(q, A, false); // Array has rows that are not a multiple of q^2
        bclib::Assert(FAILURE_CHECK, test, "error in oastr2 (5)");

        q = 3;
        temp.clear();
        temp.resize(18);
        std::fill(temp.begin(), temp.end(), 1);
        A = bclib::matrix<int>(9, 2, temp);
        test = oacpp::oastrength::OA_str2(q, A, false); // Array has q^2 rows but is not strength 2
        bclib::Assert(FAILURE_CHECK, test, "error in oastr2 (6)");
    }

    void COrthogonalArrayTest::testOastr3()
    {
        oacpp::COrthogonalArray coa;
        int n;
        coa.addelkemp3(3, 25, &n);
        bclib::Assert(!coa.oastr3(false), "Error 1 in oastr3 (1)");

		oacpp::COrthogonalArray coa2;
		coa2.bose(2, 1, &n);
		bclib::Assert(!coa2.oastr3(false), "Error 2 in oastr3 (2)");

		oacpp::COrthogonalArray coa3;
		coa3.bosebush(2, 4, &n);
		bclib::Assert(coa3.oastr3(false), "Error 3 in oastr3 (3)");

        int q = 3;
        std::vector<int> temp = { 1,1,1,1,1,1 };
        bclib::matrix<int> A = bclib::matrix<int>(6, 1, temp);
        int test = oacpp::oastrength::OA_str3(q, A, false); // Array only has one column, needs at least 3
        bclib::Assert(FAILURE_CHECK, test, "error in oastr3 (4)");

        q = 3;
        temp.resize(9);
        std::fill(temp.begin(), temp.end(), 1);
        A = bclib::matrix<int>(3, 3, temp);
        test = oacpp::oastrength::OA_str3(q, A, false); // Array has rows that are not a multiple of q^3
        bclib::Assert(FAILURE_CHECK, test, "error in oastr3 (5)");

        q = 3;
        temp.resize(81);
        std::fill(temp.begin(), temp.end(), 1);
        A = bclib::matrix<int>(27, 3, temp);
        test = oacpp::oastrength::OA_str3(q, A, false); // Array has q^3 rows but is not strength 2
        bclib::Assert(FAILURE_CHECK, test, "error in oastr3 (6)");
    }

    void COrthogonalArrayTest::testOastr4()
    {
        oacpp::COrthogonalArray coa;
        int n;
        coa.addelkemp3(3, 25, &n);
        bclib::Assert(!coa.oastr4(false), "Error 1 in oastr4");

		oacpp::COrthogonalArray coa2;
		coa2.bose(2, 1, &n);
		bclib::Assert(!coa2.oastr4(false), "Error 2 in oastr4");

		oacpp::COrthogonalArray coa3;
		coa3.bosebush(2, 4, &n);
		bclib::Assert(!coa3.oastr4(false), "Error 3 in oastr4");

        int q = 2;
        std::vector<int> temp = { 1,1,1,1,1,1 };
        bclib::matrix<int> A = bclib::matrix<int>(6, 1, temp);
        int test = oacpp::oastrength::OA_str4(q, A, false); // Array only has one column, needs at least 4
        bclib::Assert(FAILURE_CHECK, test, "error in oastr4 (4)");

        q = 2;
        temp.resize(40);
        std::fill(temp.begin(), temp.end(), 1);
        A = bclib::matrix<int>(10, 4, temp);
        test = oacpp::oastrength::OA_str4(q, A, false); // Array has rows that are not a multiple of q^4
        bclib::Assert(FAILURE_CHECK, test, "error in oastr4 (5)");

        q = 2;
        temp.resize(64);
        std::fill(temp.begin(), temp.end(), 1);
        A = bclib::matrix<int>(16, 4, temp);
        test = oacpp::oastrength::OA_str4(q, A, false); // Array has q^4 rows but is not strength 2
        bclib::Assert(FAILURE_CHECK, test, "error in oastr4 (6)");

        q = 3;
        int ncol = 4;
        int str = 4;
        n = 0;
        coa.busht(str, q, ncol, &n);
        standardChecks(coa.getoa(), q, ncol);
        bclib::Assert(SUCCESS_CHECK, coa.getReturnCode());
        bclib::Assert(coa.getMessage().length() == 0);

        test = oacpp::oastrength::OA_str4(q, const_cast<bclib::matrix<int>&>(coa.getoa()), false);
        bclib::Assert(SUCCESS_CHECK, test, "error in oastr4 (7)");
    }

	void COrthogonalArrayTest::testOastrt()
	{
		oacpp::COrthogonalArray coa;
		int n;
		coa.addelkemp3(3, 25, &n);
		bclib::Assert(!coa.oastrt(5, false), "Error 1 in oastrt (1)");

		oacpp::COrthogonalArray coa2;
		coa2.bose(2, 1, &n);
		bclib::Assert(!coa2.oastrt(5, false), "Error 2 in oastrt (2)");

		oacpp::COrthogonalArray coa3;
		coa3.bosebush(2, 4, &n);
		bclib::Assert(!coa3.oastrt(5, false), "Error 3 in oastrt (3)");

        // negative t should fail
        bclib::Assert(FAILURE_CHECK, coa3.oastrt(-1, false), "Error 4 in oastrt (4)");
        // t=0 should return success
        bclib::Assert(SUCCESS_CHECK, coa3.oastrt(0, false), "Error 5 in oastrt (5)");
    }
} // end namespace
