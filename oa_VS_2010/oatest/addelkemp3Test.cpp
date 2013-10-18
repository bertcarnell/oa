#include "addelkemp3Test.h"

namespace oaTest{
	void addelkemp3Test::Run()
	{
		printf("\taddelkemp3Test...");
		testAddelkemp3();
		printf("passed\n");
	}

	void addelkemp3Test::testAddelkemp3()
	{
		int q = 2;
		//int ncol = 2*q*q + 2*q +1;
		int ncol = 2*q*q + 2*q + 1;
		int n = 2*q*q*q;
		std::vector<int> A = std::vector<int>(n*ncol);
		int result = addelkemp3_main(&q, &ncol, &n, A.data());

		Assert(result == 0, "Error 1");
		for (int col = 0; col < ncol; col++)
		{
			for (int row = 0; row < n; row++)
			{
				Assert(A[col*n+row] == 0 || A[col*n+row] == 1, "Error 5");
			}
		}
		Assert(oa::dotProduct(A, n, ncol), "Error 6");

		q = 3;
		ncol = 2*q*q + 2*q +1;
		n = 2*q*q*q;
		A.resize(n*ncol);
		result = addelkemp3_main(&q, &ncol, &n, A.data());

		Assert(result == 0, "Error 6");
		for (int col = 0; col < ncol; col++)
		{
			for (int row = 0; row < n; row++)
			{
				Assert(A[col*n+row] == 0 || A[col*n+row] == 1 || A[col*n+row] == 2, "Error 10");
			}
		}
		Assert(oa::dotProduct(A, n, ncol), "Error 11");

		q = 3;
		ncol = 9;
		n = 2*q*q*q;
		A.resize(n*ncol);
		result = addelkemp3_main(&q, &ncol, &n, A.data());

		Assert(result == 0, "Error 11");
		for (int col = 0; col < ncol; col++)
		{
			for (int row = 0; row < n; row++)
			{
				Assert(A[col*n+row] == 0 || A[col*n+row] == 1 || A[col*n+row] == 2, "Error 12");
			}
		}
		Assert(oa::dotProduct(A, n, ncol), "Error 13");

	}
}
