#include <cstdlib>
#include <cstdio>
#include <vector>
#include "TestClass.h"
#include "addelkempTest.h"
#include "addelkemp3Test.h"

#define CREATE_TEST(x) \
	tests.push_back(dynamic_cast<TestClass*>(new x()))

using namespace oaTest;

int main(int argc, const char* argv[] )
{
	printf("Starting lhsTest...\n");
	std::vector<TestClass*> tests = std::vector<TestClass*>();
	CREATE_TEST(addelkempTest);
	CREATE_TEST(addelkemp3Test);

	for (size_t i = 0; i < tests.size(); i++)
	{
		try{
			tests[i]->Run();
		} catch (std::exception * e){
			printf(e->what());
		}
	}
}
