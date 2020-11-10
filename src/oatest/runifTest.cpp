/**
 * @file runifTest.cpp
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

#include "runifTest.h"

namespace oaTest
{
	void runifTest::Run()
	{
		printf("\trunifTest...");
		testSeed();
        testRunif();
		testMod();
		printf("passed\n");
	}

	void runifTest::testSeed()
    {
        oacpp::RUnif ran = oacpp::RUnif();
        ran.seed(1,2,3,4);
        oacpp::SeedSet s = ran.getSeedSet();
        bclib::Assert(s.is == 1, "Seed Error 1");
        bclib::Assert(s.js == 2, "Seed Error 2");
        bclib::Assert(s.ks == 3, "Seed Error 3");
        bclib::Assert(s.ls == 4, "Seed Error 4");
        ran.seed(5,6,7,8);
        s = ran.getSeedSet();
        bclib::Assert(s.is == 5, "Seed Error 5");
        bclib::Assert(s.js == 6, "Seed Error 6");
        bclib::Assert(s.ks == 7, "Seed Error 7");
        bclib::Assert(s.ls == 8, "Seed Error 8");
    }
    
    void runifTest::testRunif()
    {
        // constructors
        oacpp::RUnif ran(1,2,3,10);
        oacpp::RUnif ran_default = oacpp::RUnif(); // seeds are 1,2,3,4
        oacpp::SeedSet temp_seed(1, 2, 3, 5);
        oacpp::RUnif ran_seed(temp_seed);
        
        // test seeds are set correctly
        oacpp::SeedSet s = ran.getSeedSet();
        bclib::Assert(s.is == 1, "Seed Error 9");
        bclib::Assert(s.js == 2, "Seed Error 10");
        bclib::Assert(s.ks == 3, "Seed Error 11");
        bclib::Assert(s.ls == 10, "Seed Error 12");

        s = ran_default.getSeedSet();
        bclib::Assert(s.is == 1, "Seed Error D9");
        bclib::Assert(s.js == 2, "Seed Error D10");
        bclib::Assert(s.ks == 3, "Seed Error D11");
        bclib::Assert(s.ls == 4, "Seed Error D12");

        s = ran_seed.getSeedSet();
        bclib::Assert(s.is == 1, "Seed Error S9");
        bclib::Assert(s.js == 2, "Seed Error S10");
        bclib::Assert(s.ks == 3, "Seed Error S11");
        bclib::Assert(s.ls == 5, "Seed Error S12");

        // test seeds are changed after calling random number generation
        std::vector<double> x(3);
        ran.runif(x, 3);
		s = ran.getSeedSet();
		bclib::Assert(s.is != 1, "Runif Error 1");
        bclib::Assert(s.js != 2, "Runif Error 2");
        bclib::Assert(s.ks != 3, "Runif Error 3");
        bclib::Assert(s.ls != 10, "Runif Error 4");

        // test that another call to the generator does not yield the same numbers
        std::vector<double> x2(3);
        ran.runif(x2, 3);
        for (size_t i = 0; i < 3; i++)
        {
            bclib::Assert(x[i] != x2[i], "random equality");
        }

        // set the seeds back to the beginning and show they generate the same draws
        ran.seed(1,2,3,4);
        std::vector<double> x3(3);
        ran.runif(x3, 3);
        for (size_t i = 0; i < 3; i++)
        {
            bclib::Assert(x[i] == x3[i], "random equality 2");
        }
        
        // seed errors
        ASSERT_THROW(oacpp::RUnif ran4 = oacpp::RUnif(1, 1, 1, 1));
		ASSERT_THROW(oacpp::RUnif ran5 = oacpp::RUnif(2, -1, 3, 4));
		ASSERT_THROW(oacpp::RUnif ran6 = oacpp::RUnif(8, 9, 200, 12));
    }

	void runifTest::testMod()
	{
		bclib::Assert(oacpp::RUnif::mod(10, 2) == 0, "Error1 in testmod");
		bclib::Assert(oacpp::RUnif::mod(10, 3) == 1, "Error 2 in testmod");
        bclib::Assert(1, oacpp::RUnif::mod(-1, 2), "Error 3 in testMod");
	}
} // end Namespace
