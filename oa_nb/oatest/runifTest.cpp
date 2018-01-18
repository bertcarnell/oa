/**
 * @file runifTest.cpp
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

#include "runifTest.h"

namespace oaTest
{
	void runifTest::Run()
	{
		printf("\trunifTest...");
		testSeed();
        testRunif();
		printf("passed\n");
	}

	void runifTest::testSeed()
    {
        oacpp::RUnif ran = oacpp::RUnif();
        ran.seed(1,2,3,4);
        oacpp::SeedSet s = ran.getSeedSet();
        bclib::Assert(s.is == 1, "");
        bclib::Assert(s.js == 2, "");
        bclib::Assert(s.ks == 3, "");
        bclib::Assert(s.ls == 4, "");
        ran.seed(5,6,7,8);
        s = ran.getSeedSet();
        bclib::Assert(s.is == 5, "");
        bclib::Assert(s.js == 6, "");
        bclib::Assert(s.ks == 7, "");
        bclib::Assert(s.ls == 8, "");
    }
    
    void runifTest::testRunif()
    {
        oacpp::RUnif ran(1,2,3,4);
        oacpp::SeedSet s = ran.getSeedSet();
        bclib::Assert(s.is == 1, "");
        bclib::Assert(s.js == 2, "");
        bclib::Assert(s.ks == 3, "");
        bclib::Assert(s.ls == 4, "");
        std::vector<double> x(3);
        ran.runif(x, 3);
        bclib::Assert(s.is != 1, "");
        bclib::Assert(s.js != 2, "");
        bclib::Assert(s.ks != 3, "");
        bclib::Assert(s.ls != 4, "");
        std::vector<double> x2(3);
        ran.runif(x2, 3);
        for (size_t i = 0; i < 3; i++)
        {
            bclib::Assert(x[i] != x2[i], "random equality");
        }
        ran.seed(1,2,3,4);
        std::vector<double> x3(3);
        ran.runif(x3, 3);
        for (size_t i = 0; i < 3; i++)
        {
            bclib::Assert(x[i] == x3[i], "random equality");
        }
        
        // seed errors
        oacpp::RUnif ran4 = oacpp::RUnif(1, 1, 1, 1);
        oacpp::RUnif ran5 = oacpp::RUnif(2, -1, 3, 4);
        oacpp::RUnif ran6 = oacpp::RUnif(8, 9, 200, 12);
    }
} // end Namespace
