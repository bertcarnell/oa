/**
 * @file rutilsTest.cpp
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

#include "rutilsTest.h"

namespace oaTest{
	void rutilsTest::Run()
	{
		printf("\trutilsTest...");
		testFindRanks();
        testUnifPerm();
		printf("passed\n");
	}

	void rutilsTest::testFindRanks()
	{
        std::vector<double> v(5);
        std::vector<int> ind(5);
        
        v[0] = 1.0; v[1] = 4.3; v[2] = 2.2; v[3] = 5.5; v[4] = 0.4;
        oacpp::rutils::findranks_slow<double>(v, ind);
        bclib::Assert(ind[0] == 2 && ind[1] == 4 && ind[2] == 3 && ind[3] == 5 && ind[4] == 1, "testFindRanks Error 1");
        ind.clear();
        ind.resize(5);
        oacpp::rutils::findranks<double>(v, ind);
        bclib::Assert(ind[0] == 2 && ind[1] == 4 && ind[2] == 3 && ind[3] == 5 && ind[4] == 1, "testFindRanks Error 1.2");
        
        v[0] = 0.1; v[1] = 0.2; v[2] = 0.3; v[3] = 0.4; v[4] = 0.5;
        oacpp::rutils::findranks<double>(v, ind);
        bclib::Assert(ind[0] == 1 && ind[1] == 2 && ind[2] == 3 && ind[3] == 4 && ind[4] == 5, "testFindRanks Error 2");
        
        v[4] = 0.1; v[3] = 0.2; v[2] = 0.3; v[1] = 0.4; v[0] = 0.5;
        oacpp::rutils::findranks<double>(v, ind);
        bclib::Assert(ind[0] == 5 && ind[1] == 4 && ind[2] == 3 && ind[3] == 2 && ind[4] == 1, "testFindRanks Error 3");

        v[4] = 0.0; v[3] = 0.0; v[2] = 0.0; v[1] = 0.0; v[0] = 0.0;
        oacpp::rutils::findranks<double>(v, ind);
        bclib::Assert(ind[0] == 1 && ind[1] == 2 && ind[2] == 3 && ind[3] == 4 && ind[4] == 5, "testFindRanks Error 4");
        
        std::vector<int> ind2(6);
        // resize
        oacpp::rutils::findranks_slow<double>(v, ind2);
        bclib::Assert(v.size() == ind2.size(), "testFindRanks Error 5");

        std::vector<int> ind3(8);
        oacpp::rutils::findranks<double>(v, ind3);
        bclib::Assert(v.size() == ind3.size(), "testFindRanks Error 6");
    }
    
    void rutilsTest::testUnifPerm()
    {
        int q = 10;
        std::vector<int> pi(q);
        oacpp::RUnif ran = oacpp::RUnif();
        ran.seed(10,20,30,40);
        oacpp::rutils::unifperm(pi, q, ran);
        // test that each integer is available 0 to q-1
        for (int i = 0; i < q; i++)
        {
            bclib::Assert(std::find(pi.begin(), pi.end(), i) != pi.end(), "integer found when required");
            std::vector<int>::iterator it = std::find(pi.begin(), pi.end(), i);
            bclib::Assert(*it == static_cast<int>(i), "integer not found properly");
        }
        // test that other integers are not found
        bclib::Assert(std::find(pi.begin(), pi.end(), -1) == pi.end(), "not found");
        bclib::Assert(std::find(pi.begin(), pi.end(), q) == pi.end(), "not found");
        bclib::Assert(std::find(pi.begin(), pi.end(), q+1) == pi.end(), "not found");
        bclib::Assert(std::accumulate(pi.begin(), pi.end(), 0) == static_cast<int>((q-1)*q / 2), "wrong sum");
        
        oacpp::RUnif ran2 = oacpp::RUnif();
        ran2.seed(1,2,3,4);
        std::vector<int> pi2(q);
        oacpp::rutils::unifperm(pi2, q, ran2);
        // assert that at least one difference exists
        bool test = false;
        for (size_t i = 0; i < q; i++)
        {
            test = test | (pi[i] != pi2[i]);
        }
        bclib::Assert(test, "at least one difference does not exist");
        
        oacpp::RUnif ran3 = oacpp::RUnif();
        ran3.seed(10,20,30,40);
        std::vector<int> pi3(q);
        oacpp::rutils::unifperm(pi3, q, ran3);
        // assert that all are equal
        test = true;
        for (size_t i = 0; i < q; i++)
        {
            test = test & (pi[i] == pi3[i]);
        }
        bclib::Assert(test, "no differences does not exist");

        oacpp::RUnif ran4 = oacpp::RUnif(10, 20, 30, 40);
        bclib::Assert(ran4.getSeedSet().is == 10);
        
        oacpp::SeedSet ss;
        ss.is = 10;
        ss.js = 20;
        ss.ks = 30;
        ss.ls = 40;
        oacpp::RUnif ran5 = oacpp::RUnif(ss);
        bclib::Assert(ran5.getSeedSet().js == 20);
        
        oacpp::RUnif ran6 = oacpp::RUnif();
        ran6.seed(ss);
        bclib::Assert(ran6.getSeedSet().ks == 30);
    }
}
