#include "addelkempTest.h"

namespace oaTest{
	void addelkempTest::Run()
	{
		printf("\addelkempTest...");
		testAddelkemp();
		printf("passed\n");
	}

	void addelkempTest::testAddelkemp()
	{
		int q = 2;
		int ncol = 2*q;
		int n = 2*q*q;
		std::vector<int> A = std::vector<int>(n*ncol);
		int result = addelkemp_main(&q, &ncol, &n, A.data());

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
		ncol = 2*q;
		n = 2*q*q;
		A.resize(n*ncol);
		result = addelkemp_main(&q, &ncol, &n, A.data());

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
		ncol = 3;
		n = 2*q*q;
		A.resize(n*ncol);
		result = addelkemp_main(&q, &ncol, &n, A.data());

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
