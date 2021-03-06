/**
 * @file rutilsTest.h
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

#ifndef RUTILSTEST_H
#define	RUTILSTEST_H

#include "OATestClass.h"
#include "rutils.h"

namespace oaTest {
	/**
	 * Test of utilities
	 */
	class rutilsTest : public OATestClass
	{
		void Run();
        /**
         * @test Test the oacpp::findRanks algorithm to find the ranks of vector of numbers
         */
		void testFindRanks();
		/**
		 * @test Test the oacpp::rutils::unifperm algorithm for a uniform permutation
		 */
        void testUnifPerm();
	};
}

#endif	/* RUTILSTEST_H */
