/**
 * @file testClass.h
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

#ifndef TESTCLASS_H
#define TESTCLASS_H

#define CREATE_TEST(x) \
	tests.push_back(dynamic_cast<TestClass*>(new x()))
#define PARALLEL_CHUNK_SIZE 1
#define NUM_THREADS_USED 3

#include "CommonDefines.h"
#include <omp.h>
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
    
    inline
    int multiplyByTwo(int a)
    {
        return a*2;
    }
    inline
    int powerOfTwo(int a)
    {
        return std::pow<int>(2,a);
    }
}

#endif
