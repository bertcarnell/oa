#include "TestClass.h"

namespace oaTest
{
	void TestClass::Assert(bool test, std::string msg)
	{
		if (!test)
			throw new std::exception(msg.append("\n\n").c_str());
	}
}
