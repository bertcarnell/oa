/**
 * @file matrixTest.h
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

#ifndef MATRIXTEST_H
#define	MATRIXTEST_H

#include "OATestClass.h"
#include "matrix.h"

namespace oaTest {
    /**
     * A class to test the matrix implementation
     */
	class matrixTest : public OATestClass
	{
		void Run();
        /**
         * @test Test the matrix constructor
         * @see oacpp::matrix
         */
		void testConstructor();
        /**
         * @test Test the matrix property accessor methods
         * @see oacpp::matrix
         */
        void testAccessor();
        /**
         * @test Test the matrix operators
         * @see oacpp::matrix
         */
        void testOperators();
	};
}

#endif	/* MATRIXTEST_H */

