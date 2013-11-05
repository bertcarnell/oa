/**
 * @file testClass.cpp
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */
#include "TestClass.h"

namespace oaTest
{
	void TestClass::Assert(bool test, std::string msg)
	{
		if (!test)
        {
			throw std::runtime_error(msg.append("\n\n").c_str());
        }
	}

    bool TestClass::isDotProductConstant(oacpp::matrix<int> A, int nrows, int ncols)
    {
        int sum = 0;
        int baseSum = -1;
        //bool ret = true;
        for (size_t col1 = 0; col1 < ncols - 1; col1++)
        {
            for (size_t col2 = col1 + 1; col2 < ncols; col2++)
            {
                sum = 0;
                for (size_t row = 0; row < nrows; row++)
                {
                    sum += A(row, col1) * A(row, col2);
                }
                if (baseSum < 1)
                {
                    baseSum = sum;
                }
                else if (baseSum != sum)
                {
                    return false;
                }
                // else continue to check
            }
        }
        return true;
    }
    
    void TestClass::standardChecks(oacpp::matrix<int> A, int expectedq, int expectedCols)
    {
        Assert(A.colsize() == expectedCols, "A has the wrong col size");
        int n = A.rowsize();

		for (int col = 0; col < expectedCols; col++)
		{
			for (int row = 0; row < n; row++)
			{
				Assert(A(row, col) >= 0 && A(row,col) <= expectedq - 1, "Values in A do not match  q");
			}
		}
		Assert(isDotProductConstant(A, n, expectedCols), "Dot product is not consistent in A");
    }
}
