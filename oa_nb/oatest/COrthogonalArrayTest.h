#ifndef CORTHOGONALARRAYTEST_H
#define	CORTHOGONALARRAYTEST_H

/**
 * @file COrthogonalArrayTest.h
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

#include <functional> // c++0x
#include "TestClass.h"
#include "COrthogonalArray.h"

namespace oaTest {
	class COrthogonalArrayTest : public TestClass 
    {
    public:
		void Run();
        /**
         * @test Test the oacpp::COrthogonalArray::addelkemp algorithm
         */
		void testAddelkemp();
        /**
         * @test Test the oacpp::COrthogonalArray::addelkemp algorithm with a range of values
         */
        void testAddelkempRange();
        /**
         * @test Test the oacpp::COrthogonalArray::addelkemp3 algorithm
         */
        void testAddelkemp3();
        /**
         * @test Test the oacpp::COrthogonalArray::addelkemp3 algorithm with a range of values
         */
        void testAddelkemp3Range();
        /**
         * @test Test the oacpp::COrthogonalArray::addelkempn algorithm
         */
        void testAddelkempn();
        /**
         * @test Test the oacpp::COrthogonalArray::bose algorithm
         */
        void testBose();
        /**
         * @test Test the oacpp::COrthogonalArray::bose algorithm with a range of values
         */
        void testBoseRange();
        /**
         * @test Test the oacpp::COrthogonalArray::bosebush algorithm with a range of values
         */
        void testBoseBushRange();
        /**
         * @test Test the oacpp::COrthogonalArray::bush algorithm with a range of values
         */
        void testBushRange();
        /**
         * @test Test the oacpp::COrthogonalArray::bosebushl algorithm
         */
        void testBoseBushl();
        /**
         * @test Test the oacpp::COrthogonalArray::busht algorithm
         */
        void testBusht();
    private:
        void testRange(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            std::vector<int> & q, std::vector<int> & ncol);
        void testException(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            int q, int ncol);
	};
}

#endif	/* CORTHOGONALARRAYTEST_H */
