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
        void testRange(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            std::vector<int> & q, std::vector<int> & ncol);
        void testException(
            std::function<void(oacpp::COrthogonalArray&, int, int, int*)> & f,
            int q, int ncol);
		void testAddelkemp();
        void testAddelkempRange();
        void testAddelkemp3();
        void testAddelkemp3Range();
        void testAddelkempn();
        void testBose();
        void testBoseRange();
        void testBoseBushRange();
        void testBushRange();
	};
}

#endif	/* CORTHOGONALARRAYTEST_H */
