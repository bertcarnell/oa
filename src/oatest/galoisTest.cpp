/**
 * @file galoisTest.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2020, Robert Carnell
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

#include "galoisTest.h"

namespace oaTest
{
    void galoisTest::Run()
    {
        printf("\tgaloisTest...");
        testGF();
        testGF_poly_sum();
        testGF_poly_prod();
        printf("passed\n");
    }

    std::vector<int> galoisTest::helpersum(int i, int j, const oacpp::GF & gf)
    {
        std::vector<int> sum = std::vector<int>(gf.n);
        oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(i), gf.poly.getrow(j), sum);
        return sum;
    }

    void galoisTest::checkField(const oacpp::GF & gf)
    {
        checkAssociative(gf);
        checkCommutative(gf);
        checkIdentity(gf, gf.poly.getrow(0), gf.poly.getrow(1));
        checkInverse(gf, gf.poly.getrow(0), gf.poly.getrow(1));
        checkDistributive(gf);
    }

    void galoisTest::checkAssociative(const oacpp::GF & gf)
    {
        std::vector<int> sum1 = std::vector<int>(gf.n);
        std::vector<int> sum2 = std::vector<int>(gf.n);
        std::vector<int> sum3 = std::vector<int>(gf.n);
        std::vector<int> sum4 = std::vector<int>(gf.n);
        std::vector<int> prod1 = std::vector<int>(gf.n);
        std::vector<int> prod2 = std::vector<int>(gf.n);
        std::vector<int> prod3 = std::vector<int>(gf.n);
        std::vector<int> prod4 = std::vector<int>(gf.n);
        size_t q = static_cast<size_t>(gf.q);
        for (size_t i = 0; i < q; i++)
        {
            for (size_t j = 0; j < q; j++)
            {
                for (size_t k = 0; k < q; k++)
                {
                    oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(i), gf.poly.getrow(j), sum1);
                    oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, sum1, gf.poly.getrow(k), sum2);
                    oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(j), gf.poly.getrow(k), sum3);
                    oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(i), sum3, sum4);
                    bclib::Assert(sum2 == sum4, "Sum Associative Error");

                    oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> & >(gf.xton), gf.poly.getrow(i), gf.poly.getrow(j), prod1);
                    oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> & >(gf.xton), prod1, gf.poly.getrow(k), prod2);
                    oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> & >(gf.xton), gf.poly.getrow(j), gf.poly.getrow(k), prod3);
                    oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> & >(gf.xton), gf.poly.getrow(i), prod3, prod4);
                    bclib::Assert(prod2 == prod4, "Product Associative Error");
                }
            }
        }
    }

    void galoisTest::checkCommutative(const oacpp::GF & gf)
    {
        std::vector<int> sum1 = std::vector<int>(gf.n);
        std::vector<int> sum2 = std::vector<int>(gf.n);
        std::vector<int> prod1 = std::vector<int>(gf.n);
        std::vector<int> prod2 = std::vector<int>(gf.n);
        size_t q = static_cast<size_t>(gf.q);
        for (size_t i = 0; i < q; i++)
        {
            for (size_t j = 0; j < q; j++)
            {
                oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(i), gf.poly.getrow(j), sum1);
                oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(j), gf.poly.getrow(i), sum2);
                bclib::Assert(sum1 == sum2, "Addition Commutative Error");

                oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> & >(gf.xton), gf.poly.getrow(i), gf.poly.getrow(j), prod1);
                oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> & >(gf.xton), gf.poly.getrow(j), gf.poly.getrow(i), prod2);
                bclib::Assert(prod1 == prod2, "Product Communitative Error");
            }
        }
    }

    void galoisTest::checkIdentity(const oacpp::GF & gf, const std::vector<int> & zero, const std::vector<int> & one)
    {
        size_t q = static_cast<size_t>(gf.q);
        std::vector<int> sum = std::vector<int>(gf.n);
        std::vector<int> prod = std::vector<int>(gf.n);
        for (size_t i = 0; i < q; i++)
        {
            oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(i), zero, sum);
            oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> &>(gf.xton), gf.poly.getrow(i), one, prod);
            bclib::Assert(gf.poly.getrow(i) == sum, "Additive Identity");
            bclib::Assert(gf.poly.getrow(i) == prod, "Multiplicative Identity");
        }
    }

    void galoisTest::checkInverse(const oacpp::GF & gf, const std::vector<int> & zero, const std::vector<int> & one)
    {
        size_t q = static_cast<size_t>(gf.q);
        std::vector<int> sum = std::vector<int>(gf.n);
        std::vector<int> prod = std::vector<int>(gf.n);
        for (size_t i = 0; i < q; i++)
        {
            oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(i), gf.poly.getrow(gf.neg[i]), sum);
            bclib::Assert(sum == zero, "Additive Inverse or Negative");
            if (gf.inv[i] != -1)
            {
                oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> &>(gf.xton), gf.poly.getrow(i), gf.poly.getrow(gf.inv[i]), prod);
                bclib::Assert(prod == one, "Multiplicative Inverse");
            }
        }
    }

    void galoisTest::checkDistributive(const oacpp::GF & gf)
    {
        std::vector<int> sum1 = std::vector<int>(gf.n); // (b+c)
        std::vector<int> prod1 = std::vector<int>(gf.n); // a * (b+c)
        std::vector<int> prod2 = std::vector<int>(gf.n); // a*b
        std::vector<int> prod3 = std::vector<int>(gf.n); // a*c
        std::vector<int> sum2 = std::vector<int>(gf.n); // a*b + a*c
        size_t q = static_cast<size_t>(gf.q);
        for (size_t i = 0; i < q; i++)
        {
            for (size_t j = 0; j < q; j++)
            {
                for (size_t k = 0; k < q; k++)
                {
                    oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, gf.poly.getrow(j), gf.poly.getrow(k), sum1);
                    oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> &>(gf.xton), gf.poly.getrow(i), sum1, prod1);
                    oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> &>(gf.xton), gf.poly.getrow(i), gf.poly.getrow(j), prod2);
                    oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, const_cast<std::vector<int> &>(gf.xton), gf.poly.getrow(i), gf.poly.getrow(k), prod3);
                    oacpp::galoisfield::GF_poly_sum(gf.p, gf.n, prod2, prod3, sum2);
                    bclib::Assert(sum2 == prod1, "Distributive Error");
                }
            }
        }

    }

    void galoisTest::testGF()
    {
        oacpp::GF gf = oacpp::GF();

        // q = p^n
        // 3 = 3^1
        bclib::Assert(oacpp::galoisfield::GF_getfield(3, gf) == 1);
        bclib::Assert(gf.n == 1);
        bclib::Assert(gf.p == 3);
        bclib::Assert(gf.q == 3);
        checkField(gf);

        // q = p^n
        // 9 = 3^2
        bclib::Assert(oacpp::galoisfield::GF_getfield(9, gf) == 1);
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

        bclib::Assert(oacpp::galoisfield::GF_getfield(2, gf) == 1);
        checkField(gf);
        bclib::Assert(oacpp::galoisfield::GF_getfield(4, gf) == 1);
        checkField(gf);
        bclib::Assert(oacpp::galoisfield::GF_getfield(8, gf) == 1);
        checkField(gf);
        bclib::Assert(oacpp::galoisfield::GF_getfield(16, gf) == 1);
        checkField(gf);
        bclib::Assert(oacpp::galoisfield::GF_getfield(5, gf) == 1);
        checkField(gf);
        bclib::Assert(oacpp::galoisfield::GF_getfield(25, gf) == 1);
        checkField(gf);
    }

    void galoisTest::testGF_poly_sum()
    {
        oacpp::GF gf = oacpp::GF();
        std::vector<int> sum = std::vector<int>();

        oacpp::galoisfield::GF_getfield(3, gf);
        sum = helpersum(0, 1, gf);
        bclib::Assert(sum[0] == 1);

        oacpp::galoisfield::GF_getfield(9, gf);
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

        oacpp::galoisfield::GF_getfield(8, gf);
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

    void galoisTest::testGF_poly_prod()
    {
        oacpp::GF gf = oacpp::GF();

        oacpp::galoisfield::GF_getfield(3, gf);
        std::vector<int> prod = std::vector<int>(gf.n);
        oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, gf.xton, gf.poly.getrow(0), gf.poly.getrow(1), prod); // 0*1 %% 3
        bclib::Assert(prod == gf.poly.getrow(0));

        oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, gf.xton, gf.poly.getrow(1), gf.poly.getrow(2), prod); // 1*2 %% 3
        bclib::Assert(prod == gf.poly.getrow(2));

        oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, gf.xton, gf.poly.getrow(2), gf.poly.getrow(2), prod); // 2*2 %% 3
        bclib::Assert(prod == gf.poly.getrow(1));

        oacpp::galoisfield::GF_getfield(9, gf);
        prod.clear();
        prod.resize(gf.n);
        oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, gf.xton, gf.poly.getrow(0), gf.poly.getrow(1), prod); // 0*1 %% 3
        bclib::Assert(prod == gf.poly.getrow(0));

        oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, gf.xton, gf.poly.getrow(1), gf.poly.getrow(8), prod); // 1*(2+2x) %% 1+2x
        bclib::Assert(prod == gf.poly.getrow(8));

        oacpp::galoisfield::GF_poly_prod(gf.p, gf.n, gf.xton, gf.poly.getrow(2), gf.poly.getrow(3), prod); // 2*x %% 1+2x
        bclib::Assert(prod == gf.poly.getrow(6));
    }
}

