/**
 * @file COrthogonalArrayTest.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#ifndef CORTHOGONALARRAYTEST_H
#define	CORTHOGONALARRAYTEST_H

#include <functional> // c++0x
#include "TestClass.h"
#include "COrthogonalArray.h"
#include "rutils.h"

namespace oaTest {
	class COrthogonalArrayTest : public TestClass
	{
		void Run();
        void testRange(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            std::vector<int> & q, std::vector<int> & ncol);
        void testException(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            int q, int ncol);
		void testAddelkemp();
        void testAddelkempRange();
        void testAddelkemp3();
        void testAddelkemp3Range();
        void testAddelkempn();
        void testBose();
        void testBoseRange();
        void testBoseBushRange();
        void testBushRange();
	};
}


#endif	/* CORTHOGONALARRAYTEST_H */

