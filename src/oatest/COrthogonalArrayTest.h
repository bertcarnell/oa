#ifndef CORTHOGONALARRAYTEST_H
#define	CORTHOGONALARRAYTEST_H

/**
 * @file COrthogonalArrayTest.h
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

#include <functional> // c++0x
#include "OATestClass.h"
#include "COrthogonalArray.h"

namespace oaTest {

	/*!
	 * Test runner for tests of the orthogonal array generation package
	 *
	 */
	class COrthogonalArrayTest : public OATestClass
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
         * @test Test the oacpp::COrthogonalArray::bosebush algorithm
         */
        void testBoseBush();
        /**
         * @test Test the oacpp::COrthogonalArray::bosebush algorithm with a range of values
         */
        void testBoseBushRange();
		/**
		 * @test Test the oacpp::COrthogonalArray::bush algorithm
		 */
		void testBush();
        /**
         * @test Test the oacpp::COrthogonalArray::bush algorithm with a range of values
         */
        void testBushRange();
        
        /**
         * @test Test the oacpp::COrthogonalArray::bosebushl algorithm
         */
        void testBoseBushl();
        
        /**
         * @test Test the oacpp::COrthogonalArray::bosebushl algorithm with a range of values
         */
        void testBoseBushlRange();
        
        /**
         * @test Test the oacpp::COrthogonalArray::busht algorithm
         */
        void testBusht();
        
        /**
         * @test Test the oacpp::COrthogonalArray::busht algorithm with a range of values
         */
        void testBushtRange();
        
        /**
         * @test Test the oacpp::COrthogonalArray::oaagree
         */
        void testOaagree();
        
        /**
         * @test Test the oacpp::COrthogonalArray::oatriple
         */
        void testOatriple();
        
		/**
		 * @test Test the oacpp::COrthongalArray::oarand
		 */
        void testOarand();

		/**
		 * @test Test the oacpp::COrthongalArray::oastr
		 */
		void testOastr();

		/**
		 * @test Test the oacpp::COrthongalArray::oastr1
		 */
		void testOastr1();

		/**
		 * @test Test the oacpp::COrthongalArray::oastr2
		 */
		void testOastr2();

		/**
		 * @test Test the oacpp::COrthongalArray::oastr3
		 */
		void testOastr3();

		/**
		 * @test Test the oacpp::COrthongalArray::oastr4
		 */
		void testOastr4();

		/**
		 * @test Test the oacpp::COrthongalArray::oastrt
		 */
		void testOastrt();
    private:
        void testRange(
            const std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            const std::vector<int> & q, const std::vector<int> & ncol);
        void testRange2(
            std::function<void(oacpp::COrthogonalArray&, int, int, int, int*)> & f,
            std::vector<int> & int1,
            std::vector<int> & q, 
            std::vector<int> & ncol);
        void testException(
            const std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            int q, int ncol);
	};
}

#endif	/* CORTHOGONALARRAYTEST_H */
