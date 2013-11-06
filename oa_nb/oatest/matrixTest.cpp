/**
 * @file matrixTest.cpp
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

#include "matrixTest.h"

namespace oaTest {
  	void matrixTest::Run()
	{
		std::printf("\tmatrixTest...");
		testConstructor();
        testAccessor();
        testOperators();
		std::printf("passed\n");
	}

    void matrixTest::testConstructor()
    {
        oacpp::matrix<int> A();
        oacpp::matrix<double> B;
        B = oacpp::matrix<double>();
        
        //Assert(A.rowsize() == 0, "default constructor");
        //Assert(A.colsize() == 0, "default constructor");
        //Assert(A.data() == 0, "default constructor");
        Assert(B.rowsize() == 0, "default constructor1");
        Assert(B.colsize() == 0, "default constructor2");
        Assert(B.data() == 0, "default constructor3");

        oacpp::matrix<long> C(2,3);
        Assert(C.rowsize() == 2, "size constructor1");
        Assert(C.colsize() == 3, "size constructor2");
        Assert(C.data() != 0, "size constructor3");
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                Assert(C(i,j) == (long) 0, "loop");
            }
        }
        
        float arr[20];
        for (size_t i = 0; i < 20; i++)
        {
            arr[i] = i;
        }
        oacpp::matrix<float> D(4,5,arr);
        Assert(D.rowsize() == 4, "size constructor4");
        Assert(D.colsize() == 5, "size constructor5");
        Assert(D.data() != 0, "temp1");
        int k = 0;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                Assert(D(i,j) == static_cast<float>(k), "temp2");
                k++;
            }
        }
        int vec[3] = {2,5,9};
        oacpp::matrix<int> E(1,3,vec);
        Assert(E.rowsize() == 1, "size constructor6");
        Assert(E.colsize() == 3, "size constructor7");
        int * F = E.data();
        Assert(F[1] == 5, "temp3");
        Assert(E(0,0) == 2, "temp4");
        Assert(E(0,1) == 5, "temp5");
        Assert(E(0,2) == 9, "temp6");
        
        std::vector<int> G = {2,20,200,2000,2,20}; // c++0x
        oacpp::matrix<int> H(3,2,G);
        Assert(H.rowsize() == 3, "size constructor8");
        Assert(H.colsize() == 2, "size constructor9");
        Assert(H(0,0) == 2, "temp7");
        Assert(H(0,1) == 20, "temp8");
        Assert(H(1,0) == 200, "temp9");
        Assert(H(1,1) == 2000, "temp11");
        Assert(H(2,0) == 2, "temp22");
        Assert(H(2,1) == 20, "temp33");
        
        oacpp::matrix<int> K(E);
        Assert(K.rowsize() == 1, "size constructor11");
        Assert(K.colsize() == 3, "size constructor22");
        Assert(K(0,0) == 2, "temp44");
        Assert(K(0,1) == 5, "temp55");
        Assert(K(0,2) == 9, "temp66");
        
        H.fill(8);
        Assert(H.rowsize() == 3, "size constructor8");
        Assert(H.colsize() == 2, "size constructor9");
        Assert(H(0,0) == 8, "temp_7");
        Assert(H(0,1) == 8, "temp_8");
        Assert(H(1,0) == 8, "temp_9");
        Assert(H(1,1) == 8, "temp_11");
        Assert(H(2,0) == 8, "temp_22");
        Assert(H(2,1) == 8, "temp_33");
        
        H.clear();
        Assert(H.rowsize() == 0, "size constructor8");
        Assert(H.colsize() == 0, "size constructor9");
    }
    
    void matrixTest::testAccessor()
    {
        std::vector<int> G = {2,20,200,2000,1,3}; // c++0x
        oacpp::matrix<int> H(3,2,G);
        oacpp::matrix<double> A;
        Assert(H.rowsize() == 3, "size constructor8");
        Assert(H.colsize() == 2, "size constructor9");
        Assert(H(0,0) == 2, "temp.7");
        Assert(H(0,1) == 20, "temp.8");
        Assert(H(1,0) == 200, "temp.9");
        Assert(H(1,1) == 2000, "temp.11");
        Assert(H(2,0) == 1, "temp.22");
        Assert(H(2,1) == 3, "temp.33");
        
        Assert(H.element(1,1) == 2000, "element matrix access");
        Assert(H.element(3) == 2000, "element vector access");
        Assert(H.isEmpty() == false, "is empty false");
        Assert(A.isEmpty() == true, "is empty true");
        
        oacpp::matrix<int> Hcol = H.getColumnMatrix(0);
        Assert(Hcol.rowsize() == 3, "get col matrix");
        Assert(Hcol.colsize() == 1, "get col matrix");
        Assert(Hcol(0,0) == 2, "one1");
        Assert(Hcol(1,0) == 200, "two1");
        Assert(Hcol(2,0) == 1, "three1");
        Hcol = H.getColumnMatrix(1);
        Assert(Hcol.rowsize() == 3, "get col matrix");
        Assert(Hcol.colsize() == 1, "get col matrix");
        Assert(Hcol(0,0) == 20, "one2");
        Assert(Hcol(1,0) == 2000, "two2");
        Assert(Hcol(2,0) == 3, "three2");
        std::vector<int> Hcolvec = H.getcol(0);
        Assert(Hcolvec.size() == 3, "get col vec");
        Assert(Hcolvec[0] == 2, "one3");
        Assert(Hcolvec[1] == 200, "two3");
        Assert(Hcolvec[2] == 1, "three3");
        
        oacpp::matrix<int> Hrow = H.getRowMatrix(0);
        Assert(Hrow.rowsize() == 1, "get row matrix");
        Assert(Hrow.colsize() == 2, "get row matrix");
        Assert(Hrow(0,0) == 2, "one4");
        Assert(Hrow(0,1) == 20, "two4");
        Hrow = H.getRowMatrix(1);
        Assert(Hrow.rowsize() == 1, "get row matrix");
        Assert(Hrow.colsize() == 2, "get row matrix");
        Assert(Hrow(0,0) == 200, "one5");
        Assert(Hrow(0,1) == 2000, "two5");
        std::vector<int> Hrowvec = H.getrow(0);
        Assert(Hrowvec.size() == 2, "get row vec");
        Assert(Hrowvec[0] == 2, "one6");
        Assert(Hrowvec[1] == 20, "two6");
    }

    void matrixTest::testOperators()
    {
        std::vector<int> Avec = {1,2,3,4,5,6};
        oacpp::matrix<int> A(3,2,Avec);
        oacpp::matrix<int> B = A;
        oacpp::matrix<int> D(2,3,Avec);
        oacpp::matrix<int> E(3,2,Avec);
        oacpp::matrix<int> F(3,2,Avec);
        F(0,0) = 4;
        Assert(F(1,1) == 4, "G");
        Assert(B.rowsize() == 3, "A");
        Assert(B.colsize() == 2, "B");
        Assert(B(0,0) == 1, "C");
        Assert(B(1,1) == 4, "D");
        
        Assert(A == E, "E");
        Assert(A == B, "H");
        Assert(!(A == D), "F");
        Assert(!(A == F), "I");
        
    }
}
