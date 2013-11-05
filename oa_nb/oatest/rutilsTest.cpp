/**
 * @file rutilsTest.cpp
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#include "rutilsTest.h"

namespace oaTest{
	void rutilsTest::Run()
	{
		printf("\trutilsTest...");
		testFindRanks();
		printf("passed\n");
	}

	void rutilsTest::testFindRanks()
	{
        std::vector<double> v(5);
        std::vector<int> ind(5);
        
        v[0] = 1.0; v[1] = 4.3; v[2] = 2.2; v[3] = 5.5; v[4] = 0.4;
        oacpp::findranks_slow<double>(v, ind);
        Assert(ind[0] == 2 && ind[1] == 4 && ind[2] == 3 && ind[3] == 5 && ind[4] == 1, "testFindRanks Error 1");
        ind.clear();
        ind.resize(5);
        oacpp::findranks<double>(v, ind);
        Assert(ind[0] == 2 && ind[1] == 4 && ind[2] == 3 && ind[3] == 5 && ind[4] == 1, "testFindRanks Error 1.2");
        
        v[0] = 0.1; v[1] = 0.2; v[2] = 0.3; v[3] = 0.4; v[4] = 0.5;
        oacpp::findranks<double>(v, ind);
        Assert(ind[0] == 1 && ind[1] == 2 && ind[2] == 3 && ind[3] == 4 && ind[4] == 5, "testFindRanks Error 2");
        
        v[4] = 0.1; v[3] = 0.2; v[2] = 0.3; v[1] = 0.4; v[0] = 0.5;
        oacpp::findranks<double>(v, ind);
        Assert(ind[0] == 5 && ind[1] == 4 && ind[2] == 3 && ind[3] == 2 && ind[4] == 1, "testFindRanks Error 3");

        v[4] = 0.0; v[3] = 0.0; v[2] = 0.0; v[1] = 0.0; v[0] = 0.0;
        oacpp::findranks<double>(v, ind);
        Assert(ind[0] == 1 && ind[1] == 2 && ind[2] == 3 && ind[3] == 4 && ind[4] == 5, "testFindRanks Error 4");
    }
}
