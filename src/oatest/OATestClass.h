/**
 * @file OATestClass.h
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

#ifndef OATESTCLASS_H
#define OATESTCLASS_H

#include "OACommonDefines.h"
#include "matrix.h"
#include "TestClass.h"
#include "simpleAssert.h"

#ifdef _OPENMP
#include <omp.h>
#define NUM_THREADS_USED 3
#define PARALLEL_CHUNK_SIZE 1
#else
/** number of threads to use in the test runner */
#define NUM_THREADS_USED 1
/** size of the chunks of work performed in parallel */
#define PARALLEL_CHUNK_SIZE 1
#endif

/**
 * Macro to create an individual test and instantiate it's class if it 
 * inherits from TestClass.h
 */
#define CREATE_TEST_OA(x) \
	tests.push_back(dynamic_cast<oaTest::OATestClass*>(new x()))

/**
 * @namespace oaTest Orthogonal Array Test
 */
namespace oaTest
{
    /**
     * An abstract test class
     */
	class OATestClass : public bclib::TestClass
	{
	public:
        /**
         * Run a test suite for a test class derived from this class
         */
		virtual void Run(){};
        /**
         * Is the dot product of the columns of an orthogonal array a constant value?
         * @param A an orthogonal array matrix
         * @return the result of the test
         */
        bool isDotProductConstant(bclib::matrix<int> A);
        /**
         * A set of standard tests to apply to an orthogonal array
         * @param A an orthogonal array matrix
         * @param expectedq the expected <code>q</code> for the matrix
         * @param expectedCols the expected number of columns in the matrix
         */
        void standardChecks(bclib::matrix<int> A, int expectedq, int expectedCols);
	};
    
    /**
     * a function to multiply by two for use in a standard template as a function
     * @param a number
     * @return number multiplied by two
     */
    inline
    int multiplyByTwo(int a)
    {
        return a*2;
    }
    
    /**
     * A function to take 2 to the power of a number
     * @param a number
     * @return two exponentiated by the number
     */
    inline
    int powerOfTwo(int a)
    {
        return static_cast<int>(std::pow<int>(2,a));
    }
}

#endif
