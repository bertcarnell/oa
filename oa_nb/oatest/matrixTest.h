/**
 * @file matrixTest.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#ifndef MATRIXTEST_H
#define	MATRIXTEST_H

#include "TestClass.h"
#include "matrix.h"

namespace oaTest {
	class matrixTest : public TestClass
	{
		void Run();
		void testConstructor();
        void testAccessor();
        void testOperators();
	};
}

#endif	/* MATRIXTEST_H */

