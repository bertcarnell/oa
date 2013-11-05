/**
 * @file rutilsTest.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#ifndef RUTILSTEST_H
#define	RUTILSTEST_H

#include <cstdlib>
#include "TestClass.h"
#include "rutils.h"

namespace oaTest {
	class rutilsTest : public TestClass
	{
		void Run();
		void testFindRanks();
	};
}

#endif	/* RUTILSTEST_H */
