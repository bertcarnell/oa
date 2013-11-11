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

#include "CommonDefines.h"
#include "matrix.h"

#ifdef _OPENMP
#include <omp.h>
#define NUM_THREADS_USED 3
#define PARALLEL_CHUNK_SIZE 1
#else
#define NUM_THREADS_USED 1
#define PARALLEL_CHUNK_SIZE 1
#endif

/**
 * @namespace oaTest Orthogonal Array Test
 */
namespace oaTest
{
    /**
     * An abstract test class
     */
	class TestClass
	{
	public:
        /**
         * Run a test suite for a test class derived from this class
         */
		virtual void Run(){};
        /**
         * Assert a test statement
         * @param test a statement to test
         * @param msg a message to print if the test statement is <code>false</code>
         */
		void Assert(bool test, std::string msg);
        /**
         * Is the dot product of the columns of an orthogonal array a constant value?
         * @param A an orthogonal array matrix
         * @return the result of the test
         */
        bool isDotProductConstant(oacpp::matrix<int> A);
        /**
         * A set of standard tests to apply to an orthogonal array
         * @param A an orthogonal array matrix
         * @param expectedq the expected <code>q</code> for the matrix
         * @param expectedCols the expected number of columns in the matrix
         */
        void standardChecks(oacpp::matrix<int> A, int expectedq, int expectedCols);
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
        return std::pow<int>(2,a);
    }
}

#endif
