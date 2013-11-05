/**
 * @file main.cpp
 * @author Robert Carnell
 * @copyright Robert Carnell 2013
 * 
 * License:
 */

#include <cstdlib>
#include <cstdio>
#include <vector>
#include "TestClass.h"
#include "rutilsTest.h"
#include "matrixTest.h"
#include "COrthogonalArrayTest.h"

#define CREATE_TEST(x) \
	tests.push_back(dynamic_cast<TestClass*>(new x()))

using namespace oaTest;

/*struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_+i << '\n'; }
    int num_;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
 
int main()
{
    // store a free function
    std::function<void(int)> f_display = print_num;
    f_display(-9);
 
    // store a lambda
    std::function<void()> f_display_42 = []() { print_num(42); };
    f_display_42();
 
    // store the result of a call to std::bind
    std::function<void()> f_display_31337 = std::bind(print_num, 31337);
    f_display_31337();
 
    // store a call to a member function
    std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
    Foo foo(314159);
    f_add_display(foo, 1);
 
    // store a call to a function object
    std::function<void(int)> f_display_obj = PrintNum();
    f_display_obj(18);
}*/

int main(int argc, const char* argv[] )
{
	printf("Starting oatest...\n");
	std::vector<TestClass*> tests = std::vector<TestClass*>();
    CREATE_TEST(COrthogonalArrayTest);
    CREATE_TEST(rutilsTest);
    CREATE_TEST(matrixTest);

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
