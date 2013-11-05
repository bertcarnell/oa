/**
 * @file COrthogonalArrayTest.cpp
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#include "COrthogonalArrayTest.h"

namespace oaTest{
    int multiplyByTwo(int a){return a*2;}
    int powerOfTwo(int a){return std::pow<int>(2,a);}

	void COrthogonalArrayTest::Run()
	{
		printf("\tCOrthogonalArray...");
		testAddelkemp();
        testAddelkempRange();
		testAddelkemp3();
        testAddelkemp3Range();
        //testAddelkempn(); // Unknown exception
        testBose();
        testBoseRange();
        testBoseBushRange();
        //testBushRange();
		printf("passed\n");
	}
    
    void COrthogonalArrayTest::testRange(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            std::vector<int> & q, std::vector<int> & ncol)
	{
        assert(q.size() == ncol.size());
        oacpp::COrthogonalArray coa;
        int n = 0;
        for (int i = 0; i < q.size(); i++)
        {
            try
            {
                f(coa, q[i], ncol[i], &n);
                standardChecks(coa.getoa(), q[i], ncol[i]);
            }
            catch (std::exception & e)
            {
                std::printf("\n ** q=%d ncol=%d *****\n", q[i], ncol[i]);
                std::printf("%s\n", e.what());
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
        //std::vector<int> q = {2,3,4,5,7,11,13,17,19,23,29,31,37,41,43,49}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> q = {2,3,4,5,7};
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
        //std::vector<int> q = {2,3,4,5,7,11,13,17,19,23,29,31,37,41,43,49}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> q = {2,3,4,5,7};
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
        //std::vector<int> q = {2,3,4,5,7,11,13,17,19,23,29,31,37,41,43,49}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> q = {2,3,4,5,7,8,9};
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
        //std::vector<int> q = {2,3,4,5,7,11,13,17,19,23,29,31,37,41,43,49}; // requires -std=c++0x in gcc >= 4.6.3
        std::vector<int> q = {2,3,4,5,7,11};
        std::vector<int> ncol(q);
        std::function<void(oacpp::COrthogonalArray&, int, int, int*)> f = &oacpp::COrthogonalArray::bush;
        testRange(f, q, ncol);
    }
} // end namespace
