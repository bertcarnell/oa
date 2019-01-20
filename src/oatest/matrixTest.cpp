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

/**
 * Macro to assert that an out of range error was thrown
 */
#define ASSERT_THROW_RANGE(X) \
        try \
        { \
            X; \
            bclib::Assert(false, "not executed if above throws"); \
        } \
        catch (std::out_of_range &) \
        { \
            bclib::Assert(true, "correct item thrown"); \
        } \
        catch (...) \
        { \
            bclib::Assert(false, "any other throw is incorrect"); \
        }


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
        //bclib::matrix<int> A();
        bclib::matrix<double> B;
        B = bclib::matrix<double>();
        
        //Assert(A.rowsize() == 0, "default constructor");
        //Assert(A.colsize() == 0, "default constructor");
        //Assert(A.data() == 0, "default constructor");
        bclib::Assert(B.rowsize() == 0, "default constructor1");
        bclib::Assert(B.colsize() == 0, "default constructor2");
        bclib::Assert(B.data() == 0, "default constructor3");

        bclib::matrix<long> C(2,3);
        bclib::Assert(C.rowsize() == 2, "size constructor1");
        bclib::Assert(C.colsize() == 3, "size constructor2");
        bclib::Assert(C.data() != 0, "size constructor3");
        for (size_t i = 0; i < 2; i++)
        {
            for (size_t j = 0; j < 3; j++)
            {
                bclib::Assert(C(i,j) == (long) 0, "loop");
            }
        }
        
        float arr[20];
        for (size_t i = 0; i < 20; i++)
        {
            arr[i] = static_cast<float>(i);
        }
        bclib::matrix<float> D(4,5,arr);
        bclib::Assert(D.rowsize() == 4, "size constructor4");
        bclib::Assert(D.colsize() == 5, "size constructor5");
        bclib::Assert(D.data() != 0, "temp1");
        int k = 0;
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 5; j++)
            {
                bclib::Assert(D(i,j) == static_cast<float>(k), "temp2");
                k++;
            }
        }
        int vec[3] = {2,5,9};
        bclib::matrix<int> E(1,3,vec);
        bclib::Assert(E.rowsize() == 1, "size constructor6");
        bclib::Assert(E.colsize() == 3, "size constructor7");
        int * F = E.data();
        bclib::Assert(F[1] == 5, "temp3");
        bclib::Assert(E(0,0) == 2, "temp4");
        bclib::Assert(E(0,1) == 5, "temp5");
        bclib::Assert(E(0,2) == 9, "temp6");
        
        std::vector<int> G = {2,20,200,2000,2,20}; // c++0x
        bclib::matrix<int> H(3,2,G);
        bclib::Assert(H.rowsize() == 3, "size constructor8");
        bclib::Assert(H.colsize() == 2, "size constructor9");
        bclib::Assert(H(0,0) == 2, "temp7");
        bclib::Assert(H(0,1) == 20, "temp8");
        bclib::Assert(H(1,0) == 200, "temp9");
        bclib::Assert(H(1,1) == 2000, "temp11");
        bclib::Assert(H(2,0) == 2, "temp22");
        bclib::Assert(H(2,1) == 20, "temp33");
        
        bclib::matrix<int> K(E);
        bclib::Assert(K.rowsize() == 1, "size constructor11");
        bclib::Assert(K.colsize() == 3, "size constructor22");
        bclib::Assert(K(0,0) == 2, "temp44");
        bclib::Assert(K(0,1) == 5, "temp55");
        bclib::Assert(K(0,2) == 9, "temp66");
        
        H.fill(8);
        bclib::Assert(H.rowsize() == 3, "size constructor8");
        bclib::Assert(H.colsize() == 2, "size constructor9");
        bclib::Assert(H(0,0) == 8, "temp_7");
        bclib::Assert(H(0,1) == 8, "temp_8");
        bclib::Assert(H(1,0) == 8, "temp_9");
        bclib::Assert(H(1,1) == 8, "temp_11");
        bclib::Assert(H(2,0) == 8, "temp_22");
        bclib::Assert(H(2,1) == 8, "temp_33");
        
        H.clear();
        bclib::Assert(H.rowsize() == 0, "size constructor8");
        bclib::Assert(H.colsize() == 0, "size constructor9");
    }
    
    void matrixTest::testAccessor()
    {
        std::vector<int> G = {2,20,200,2000,1,3}; // c++0x
        bclib::matrix<int> H(3,2,G);
        bclib::matrix<double> A;
        bclib::Assert(H.rowsize() == 3, "size constructor8");
        bclib::Assert(H.colsize() == 2, "size constructor9");
        bclib::Assert(H(0,0) == 2, "temp.7");
        bclib::Assert(H(0,1) == 20, "temp.8");
        bclib::Assert(H(1,0) == 200, "temp.9");
        bclib::Assert(H(1,1) == 2000, "temp.11");
        bclib::Assert(H(2,0) == 1, "temp.22");
        bclib::Assert(H(2,1) == 3, "temp.33");
        
        bclib::Assert(H.isEmpty() == false, "is empty false");
        bclib::Assert(A.isEmpty() == true, "is empty true");
        
        bclib::matrix<int> Hcol = H.getColumnMatrix(0);
        bclib::Assert(Hcol.rowsize() == 3, "get col matrix");
        bclib::Assert(Hcol.colsize() == 1, "get col matrix");
        bclib::Assert(Hcol(0,0) == 2, "one1");
        bclib::Assert(Hcol(1,0) == 200, "two1");
        bclib::Assert(Hcol(2,0) == 1, "three1");
        Hcol = H.getColumnMatrix(1);
        bclib::Assert(Hcol.rowsize() == 3, "get col matrix");
        bclib::Assert(Hcol.colsize() == 1, "get col matrix");
        bclib::Assert(Hcol(0,0) == 20, "one2");
        bclib::Assert(Hcol(1,0) == 2000, "two2");
        bclib::Assert(Hcol(2,0) == 3, "three2");
        std::vector<int> Hcolvec = H.getcol(0);
        bclib::Assert(Hcolvec.size() == 3, "get col vec");
        bclib::Assert(Hcolvec[0] == 2, "one3");
        bclib::Assert(Hcolvec[1] == 200, "two3");
        bclib::Assert(Hcolvec[2] == 1, "three3");
        
        bclib::matrix<int> Hrow = H.getRowMatrix(0);
        bclib::Assert(Hrow.rowsize() == 1, "get row matrix");
        bclib::Assert(Hrow.colsize() == 2, "get row matrix");
        bclib::Assert(Hrow(0,0) == 2, "one4");
        bclib::Assert(Hrow(0,1) == 20, "two4");
        Hrow = H.getRowMatrix(1);
        bclib::Assert(Hrow.rowsize() == 1, "get row matrix");
        bclib::Assert(Hrow.colsize() == 2, "get row matrix");
        bclib::Assert(Hrow(0,0) == 200, "one5");
        bclib::Assert(Hrow(0,1) == 2000, "two5");
        std::vector<int> Hrowvec = H.getrow(0);
        bclib::Assert(Hrowvec.size() == 2, "get row vec");
        bclib::Assert(Hrowvec[0] == 2, "one6");
        bclib::Assert(Hrowvec[1] == 20, "two6");
        
        std::vector<int> A1 = {1,2,3,4,5,6}; // c++0x
        bclib::matrix<int> A2(3,2,A1);
        bclib::Assert(A2.at(0,0) == 1, "pass2");
        bclib::Assert(A2.at(1,1) == 4, "pass4");
        ASSERT_THROW_RANGE(A2.at(5,6))
        ASSERT_THROW_RANGE(A2.at(20))
        ASSERT_THROW_RANGE(A2.getColumnMatrix_at(7))
        ASSERT_THROW_RANGE(A2.getRowMatrix_at(4))
        ASSERT_THROW_RANGE(A2.getcol_at(6))
        ASSERT_THROW_RANGE(A2.getrow_at(10))
    }

    void matrixTest::testOperators()
    {
        std::vector<int> Avec = {1,2,3,4,5,6};
        bclib::matrix<int> A(3,2,Avec);
        bclib::matrix<int> B = A;
        bclib::matrix<int> D(2,3,Avec);
        bclib::matrix<int> E(3,2,Avec);
        bclib::matrix<int> F(3,2,Avec);
        F(0,0) = 4;
        bclib::Assert(F(1,1) == 4, "G");
        bclib::Assert(B.rowsize() == 3, "A");
        bclib::Assert(B.colsize() == 2, "B");
        bclib::Assert(B(0,0) == 1, "C");
        bclib::Assert(B(1,1) == 4, "D");
        
        bclib::Assert(A == E, "E");
        bclib::Assert(A == B, "H");
        bclib::Assert(!(A == D), "F");
        bclib::Assert(!(A == F), "I");
    }
}
