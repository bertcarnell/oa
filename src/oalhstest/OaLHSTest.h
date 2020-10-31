/**
 * @file OaLHSTest.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2019, Robert Carnell
 * 
 * License: <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
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

#ifndef OALHSTEST_H
#define	OALHSTEST_H

#include "TestClass.h"
#include "oaLHS.h"

namespace oalhs_test {
	/**
	 * Class to test the oaLHS functions
	 */
	class oaLHSTest : public bclib::TestClass
	{
    public:
	    /** Run the test suite */
		void Run();
		/** @test Test the orthogonal array latin hypercube code */
		void testOaLHS();
		/** @test Test the orthogonal array latin hypercube code with additional information */
		void testOaLHS_2();
		/** @test Test generating orthogonal array latin hypercubes */
        void testGenerateOALHS();
        
		/**
		 * Check to determine of a lhs is valid.
		 * @param result the matrix to check
		 * @return boolean result
		 */
        bool isValidLHS(const bclib::matrix<int> & result);
		/**
		 * Check to determin if a double valued lhs is valid
		 * @param result the matrix to check
		 * @return boolean result of the check
		 */
        bool isValidLHS(const bclib::matrix<double> & result);
	};
}



#endif	/* OALHSTEST_H */

