/**
 * @file runifTest.h
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

#ifndef RUNIFTEST_H
#define	RUNIFTEST_H

#include "OATestClass.h"
#include "runif.h"

namespace oaTest 
{
	/**
	 * Class to test the runif methods
	 */
	class runifTest : public OATestClass
	{
		/**
		 * Test runner
		 */
		void Run();
		/**
		 * @test Test the seed methods
		 */
		void testSeed();
		/**
		 * @test Test the oacpp::RUnif class
		 */
		void testRunif();
		/*
		 * @test Test the oacpp::RUnif::mod function
		 */
		void testMod();
	};
}


#endif	/* RUNIFTEST_H */

