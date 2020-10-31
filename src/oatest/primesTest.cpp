/**
 * @file primesTest.cpp
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

#include "primesTest.h"

namespace oaTest
{
	void primesTest::Run()
	{
		printf("\tprimesTest...");
		testIsPrime();
		testPrimePow();
		printf("passed\n");
	}

	void primesTest::testIsPrime()
	{
		bclib::Assert(oacpp::primes::isprime(0) == ISPRIMEFALSE, "error 0 prime");
		bclib::Assert(oacpp::primes::isprime(1) == ISPRIMEFALSE, "error 1 prime");
		bclib::Assert(oacpp::primes::isprime(2) == ISPRIMETRUE, "error 2 prime");
        bclib::Assert(oacpp::primes::isprime(3) == ISPRIMETRUE, "error 3 prime");
        bclib::Assert(oacpp::primes::isprime(4) == ISPRIMEFALSE, "error 4 not prime");
        bclib::Assert(oacpp::primes::isprime(5) == ISPRIMETRUE, "error 5 prime");
        bclib::Assert(oacpp::primes::isprime(6) == ISPRIMEFALSE, "error 6 not prime");
    }

	void primesTest::testPrimePow()
	{
		int p = 0;
		int n = 0;
		int isit = 0;
		oacpp::primes::primepow(8, &p, &n, &isit);
		bclib::Assert(p == 2 && n == 3 && isit == 1);

		p = n = isit = 0;
		oacpp::primes::primepow(23, &p, &n, &isit);
		bclib::Assert(p == 23 && n == 1 && isit == 1);

		// Not Prime
		p = n = isit = 0;
		oacpp::primes::primepow(6, &p, &n, &isit);
		bclib::Assert(p == 0 && n == 1 && isit == 0);

		// q < 1
		p = n = isit = 0;
		oacpp::primes::primepow(-1, &p, &n, &isit);
		bclib::Assert(p == 0 && n == 0 && isit == 0);
	}
}

