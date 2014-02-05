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
        Assert(s.is == 1, "");
        Assert(s.js == 2, "");
        Assert(s.ks == 3, "");
        Assert(s.ls == 4, "");
        ran.seed(5,6,7,8);
        s = ran.getSeedSet();
        Assert(s.is == 5, "");
        Assert(s.js == 6, "");
        Assert(s.ks == 7, "");
        Assert(s.ls == 8, "");
    }
    
    void runifTest::testRunif()
    {
        oacpp::RUnif ran(1,2,3,4);
        oacpp::SeedSet s = ran.getSeedSet();
        Assert(s.is == 1, "");
        Assert(s.js == 2, "");
        Assert(s.ks == 3, "");
        Assert(s.ls == 4, "");
        std::vector<double> x(3);
        ran.runif(x, 3);
        Assert(s.is != 1, "");
        Assert(s.js != 2, "");
        Assert(s.ks != 3, "");
        Assert(s.ls != 4, "");
        std::vector<double> x2(3);
        ran.runif(x2, 3);
        for (size_t i = 0; i < 3; i++)
        {
            Assert(x[i] != x2[i], "random equality");
        }
        ran.seed(1,2,3,4);
        std::vector<double> x3(3);
        ran.runif(x3, 3);
        for (size_t i = 0; i < 3; i++)
        {
            Assert(x[i] == x3[i], "random equality");
        }
        
    }
} // end Namespace
