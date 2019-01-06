/**
 * @file main.cpp
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

#include "OATestClass.h"
#include "rutilsTest.h"
#include "matrixTest.h"
#include "primesTest.h"
#include "COrthogonalArrayTest.h"
#include "runifTest.h"
#include "gfieldsTest.h"

using namespace oaTest;

int main(int argc, const char* argv[] )
{
#ifdef _OPENMP
    omp_set_num_threads(NUM_THREADS_USED);
#endif

	printf("Starting oatest with %d thread(s)...\n", NUM_THREADS_USED);
	std::vector<OATestClass*> tests = std::vector<OATestClass*>();
    CREATE_TEST_OA(primesTest);
	CREATE_TEST_OA(gfieldsTest);
    CREATE_TEST_OA(COrthogonalArrayTest);
    CREATE_TEST_OA(rutilsTest);
    CREATE_TEST_OA(matrixTest);
	CREATE_TEST_OA(runifTest);

	for (size_t i = 0; i < tests.size(); i++)
	{
		try{
			tests[i]->Run();
		} catch (std::exception & e){
            printf("\n%s\n", e.what());
		} catch (...)
        {
            printf("\nUncaught exception in main\n");
        }
	}
}
