/**
 * @file testClass.h
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#ifndef CORTHOGONALARRAYTEST_H
#define CORTHOGONALARRAYTEST_H

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <exception>
#include <stdexcept>
#include <string>
#include "matrix.h"

namespace oaTest
{
	class TestClass
	{
	public:
		virtual void Run(){};
		void Assert(bool test, std::string msg);
        bool isDotProductConstant(oacpp::matrix<int> A, int nrows, int ncols);
        void standardChecks(oacpp::matrix<int> A, int expectedq, int expectedCols);
	};
}

#endif
