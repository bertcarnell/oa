/**
 * @file galoisTest.h
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

#ifndef GALOISTEST_H
#define	GALOISTEST_H

#include "OATestClass.h"
#include "galois.h"
#include "primes.h"

namespace oaTest {
    /**
     * A class to test the Galois Fields implementation
     */
    class galoisTest : public OATestClass
    {
        void Run();

        /**
         * @test Test GF
         * @see oacpp::GF
         */
        void testGF();

        // c++11 RVO allows return by value without copy
        std::vector<int> helpersum(int i, int j, const oacpp::GF & gf);

        // methods to verify all properties of a field (in the mathematical sense)
        void checkField(const oacpp::GF & gf);
        void checkAssociative(const oacpp::GF & gf);
        void checkCommutative(const oacpp::GF & gf);
        void checkIdentity(const oacpp::GF & gf, const std::vector<int> & zero, const std::vector<int> & one);
        void checkInverse(const oacpp::GF & gf, const std::vector<int> & zero, const std::vector<int> & one);
        void checkDistributive(const oacpp::GF & gf);

        /**
         * @test Test GF_poly_sum
         * @see oacpp::galoisfield::GF_poly_sum
         */
        void testGF_poly_sum();

        /**
         * @test Test GF_poly_sum
         * @see oacpp::galoisfield::GF_poly_sum
         */
        void testGF_poly_prod();
    };
}

#endif	/* GALOISTEST_H */

