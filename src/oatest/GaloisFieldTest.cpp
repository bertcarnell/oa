/**
 * @file GaloisFieldTest.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2020, Robert Carnell
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

#include "GaloisFieldTest.h"

namespace oaTest
{
    void GaloisFieldTest::Run()
    {
        printf("\tGaloisFieldTest...");
        testGaloisField();
        testPolySum();
        testPolyProd();
        printf("passed\n");
    }

    std::vector<int> GaloisFieldTest::helpersum(int i, int j, const oacpp::GaloisField & gf)
    {
        std::vector<int> sum = std::vector<int>(gf.n);
        oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(i), gf.poly.getrow(j), sum);
        return sum;
    }

    void GaloisFieldTest::checkField(const oacpp::GaloisField & gf)
    {
        checkAssociative(gf);
        checkCommutative(gf);
        checkIdentity(gf, gf.poly.getrow(0), gf.poly.getrow(1));
        checkInverse(gf, gf.poly.getrow(0), gf.poly.getrow(1));
        checkDistributive(gf);
    }

    void GaloisFieldTest::checkAssociative(const oacpp::GaloisField & gf)
    {
        std::vector<int> sum1 = std::vector<int>(gf.u_n);
        std::vector<int> sum2 = std::vector<int>(gf.u_n);
        std::vector<int> sum3 = std::vector<int>(gf.u_n);
        std::vector<int> sum4 = std::vector<int>(gf.u_n);
        std::vector<int> prod1 = std::vector<int>(gf.u_n);
        std::vector<int> prod2 = std::vector<int>(gf.u_n);
        std::vector<int> prod3 = std::vector<int>(gf.u_n);
        std::vector<int> prod4 = std::vector<int>(gf.u_n);
        size_t q = static_cast<size_t>(gf.q);
        for (size_t i = 0; i < q; i++)
        {
            for (size_t j = 0; j < q; j++)
            {
                for (size_t k = 0; k < q; k++)
                {
                    oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(i), gf.poly.getrow(j), sum1);
                    oacpp::GaloisField::polySum(gf.p, gf.u_n, sum1, gf.poly.getrow(k), sum2);
                    oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(j), gf.poly.getrow(k), sum3);
                    oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(i), sum3, sum4);
                    bclib::Assert(sum2 == sum4, "Sum Associative Error");

                    oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), gf.poly.getrow(j), prod1);
                    oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, prod1, gf.poly.getrow(k), prod2);
                    oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(j), gf.poly.getrow(k), prod3);
                    oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), prod3, prod4);
                    bclib::Assert(prod2 == prod4, "Product Associative Error");
                }
            }
        }
    }

    void GaloisFieldTest::checkCommutative(const oacpp::GaloisField & gf)
    {
        std::vector<int> sum1 = std::vector<int>(gf.u_n);
        std::vector<int> sum2 = std::vector<int>(gf.u_n);
        std::vector<int> prod1 = std::vector<int>(gf.u_n);
        std::vector<int> prod2 = std::vector<int>(gf.u_n);
        for (size_t i = 0; i < gf.u_q; i++)
        {
            for (size_t j = 0; j < gf.u_q; j++)
            {
                oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(i), gf.poly.getrow(j), sum1);
                oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(j), gf.poly.getrow(i), sum2);
                bclib::Assert(sum1 == sum2, "Addition Commutative Error");

                oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), gf.poly.getrow(j), prod1);
                oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(j), gf.poly.getrow(i), prod2);
                bclib::Assert(prod1 == prod2, "Product Communitative Error");
            }
        }
    }

    void GaloisFieldTest::checkIdentity(const oacpp::GaloisField & gf, const std::vector<int> & zero, const std::vector<int> & one)
    {
        std::vector<int> sum = std::vector<int>(gf.u_n);
        std::vector<int> prod = std::vector<int>(gf.u_n);
        for (size_t i = 0; i < gf.u_q; i++)
        {
            oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(i), zero, sum);
            oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), one, prod);
            bclib::Assert(gf.poly.getrow(i) == sum, "Additive Identity");
            bclib::Assert(gf.poly.getrow(i) == prod, "Multiplicative Identity");
        }
    }

    void GaloisFieldTest::checkInverse(const oacpp::GaloisField & gf, const std::vector<int> & zero, const std::vector<int> & one)
    {
        std::vector<int> sum = std::vector<int>(gf.u_n);
        std::vector<int> prod = std::vector<int>(gf.u_n);
        for (size_t i = 0; i < gf.u_q; i++)
        {
            oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(i), gf.poly.getrow(gf.neg[i]), sum);
            bclib::Assert(sum == zero, "Additive Inverse or Negative");
            if (gf.inv[i] != -1)
            {
                oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), gf.poly.getrow(gf.inv[i]), prod);
                bclib::Assert(prod == one, "Multiplicative Inverse");
            }
        }
    }

    void GaloisFieldTest::checkDistributive(const oacpp::GaloisField & gf)
    {
        std::vector<int> sum1 = std::vector<int>(gf.u_n); // (b+c)
        std::vector<int> prod1 = std::vector<int>(gf.u_n); // a * (b+c)
        std::vector<int> prod2 = std::vector<int>(gf.u_n); // a*b
        std::vector<int> prod3 = std::vector<int>(gf.u_n); // a*c
        std::vector<int> sum2 = std::vector<int>(gf.u_n); // a*b + a*c
        for (size_t i = 0; i < gf.u_q; i++)
        {
            for (size_t j = 0; j < gf.u_q; j++)
            {
                for (size_t k = 0; k < gf.u_q; k++)
                {
                    oacpp::GaloisField::polySum(gf.p, gf.u_n, gf.poly.getrow(j), gf.poly.getrow(k), sum1);
                    oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), sum1, prod1);
                    oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), gf.poly.getrow(j), prod2);
                    oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(i), gf.poly.getrow(k), prod3);
                    oacpp::GaloisField::polySum(gf.p, gf.u_n, prod2, prod3, sum2);
                    bclib::Assert(sum2 == prod1, "Distributive Error");
                }
            }
        }

    }

    void GaloisFieldTest::testGaloisField()
    {
        oacpp::GaloisField gf = oacpp::GaloisField(3);

        // q = p^n
        // 3 = 3^1
        bclib::Assert(gf.n == 1);
        bclib::Assert(gf.p == 3);
        bclib::Assert(gf.q == 3);
        checkField(gf);

        gf = oacpp::GaloisField(9);

        // q = p^n
        // 9 = 3^2
        bclib::Assert(gf.n == 2);
        bclib::Assert(gf.p == 3);
        bclib::Assert(gf.q == 9);
        // characteristic polynomial of degree n-1=1
        // 1 + 2x
        bclib::Assert(gf.xton[0] == 1 && gf.xton[1] == 2);
        // polynomial field (a,b) a*1 + b*x
        // 0,0 1,0 2,0 0,1 1,1 2,1 0,2 1,2 2,2
        // 0, 1, 2, x, 1+x 2+x 2x, 1+2x, 2+2x
        bclib::Assert(gf.poly.rowsize() == 9 && gf.poly.colsize() == 2);
        bclib::Assert(gf.poly(0, 0) == 0 && gf.poly(8, 1) == 2);

        checkField(gf);

        gf = oacpp::GaloisField(2);
        checkField(gf);
        gf = oacpp::GaloisField(4);
        checkField(gf);
        gf = oacpp::GaloisField(8);
        checkField(gf);
        gf = oacpp::GaloisField(16);
        checkField(gf);
        gf = oacpp::GaloisField(32);
        checkField(gf);
        gf = oacpp::GaloisField(27);
        checkField(gf);
        gf = oacpp::GaloisField(5);
        checkField(gf);
        gf = oacpp::GaloisField(25);
        checkField(gf);
        gf = oacpp::GaloisField(7);
        checkField(gf);
        gf = oacpp::GaloisField(11);
        checkField(gf);

        ASSERT_NOTHROW(gf = oacpp::GaloisField(3));
        ASSERT_THROW(gf = oacpp::GaloisField(-3));
        ASSERT_THROW(gf = oacpp::GaloisField(1));
        ASSERT_THROW(gf = oacpp::GaloisField(100));
        ASSERT_THROW(gf = oacpp::GaloisField(oacpp::primes::ipow(2, 30)));
    }

    void GaloisFieldTest::testPolySum()
    {
        std::vector<int> sum = std::vector<int>();

        oacpp::GaloisField gf = oacpp::GaloisField(3);
        sum = helpersum(0, 1, gf);
        bclib::Assert(sum[0] == 1);

        gf = oacpp::GaloisField(9);
        // characteristic polynomial of degree n-1=1
        // 1 + 2x
        // polynomial field (a,b) a*1 + b*x
        // 0,0 1,0 2,0 0,1 1,1 2,1 0,2 1,2 2,2
        // 0, 1, 2, x, 1+x 2+x 2x, 1+2x, 2+2x

        // 0,0 plus 1,0
        // 0 + 1 % 3 == 1 which is 1,0 in the vector
        sum = helpersum(0, 1, gf);
        bclib::Assert(sum[0] == 1 && sum[1] == 0);
        // 2,2 plus 2,0
        // 2+2x + 2 = 4+2x = 4%%3 + 2x = 1 + 2x
        sum = helpersum(8, 2, gf);
        bclib::Assert(sum[0] == 1 && sum[1] == 2);

        gf = oacpp::GaloisField(8);
        // n=3, p=2, q=8
        // characteristic polynomial 1 + x^2
        // polynomial field:
        // 0, 1, x, 1+x, x^2, 1+x^2, x+x^2, 1+x+x^2
        sum = helpersum(0, 1, gf);
        bclib::Assert(sum[0] == 1 && sum[1] == 0 && sum[2] == 0);
        // x+x^2 + 1+x+x^2 = 1+2x+2x^2 = 1
        sum = helpersum(6, 7, gf);
        bclib::Assert(sum[0] == 1 && sum[1] == 0 && sum[2] == 0);
    }

    void GaloisFieldTest::testPolyProd()
    {
        oacpp::GaloisField gf = oacpp::GaloisField(3);
        std::vector<int> prod = std::vector<int>(gf.u_n);

        oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(0), gf.poly.getrow(1), prod); // 0*1 %% 3
        bclib::Assert(prod == gf.poly.getrow(0));

        oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(1), gf.poly.getrow(2), prod); // 1*2 %% 3
        bclib::Assert(prod == gf.poly.getrow(2));

        oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(2), gf.poly.getrow(2), prod); // 2*2 %% 3
        bclib::Assert(prod == gf.poly.getrow(1));

        gf = oacpp::GaloisField(9);
        prod.clear();
        prod.resize(gf.u_n);
        oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(0), gf.poly.getrow(1), prod); // 0*1 %% 3
        bclib::Assert(prod == gf.poly.getrow(0));

        oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(1), gf.poly.getrow(8), prod); // 1*(2+2x) %% 1+2x
        bclib::Assert(prod == gf.poly.getrow(8));

        oacpp::GaloisField::polyProd(gf.p, gf.u_n, gf.xton, gf.poly.getrow(2), gf.poly.getrow(3), prod); // 2*x %% 1+2x
        bclib::Assert(prod == gf.poly.getrow(6));
    }
}

