#include <cstdlib>
#include "TestClass.h"
#include "OaLHSTest.h"

using namespace oalhs_test;

int main(int argc, char** argv)
{
    START_TESTS("Starting Simple Tests...\n");
	CREATE_TEST(oaLHSTest);
    EXECUTE_TESTS(0);
}

