#ifndef OALHSTEST_H
#define	OALHSTEST_H

#include "TestClass.h"
#include "oaLHS.h"

namespace oalhs_test {
	class oaLHSTest : public bclib::TestClass
	{
    public:
		void Run(); /**< Run the test suite */
		void testOaLHS(); /**< Test */
		void testOaLHS_2(); /**< Test */
        void testGenerateOALHS(); /**< Test */
        
        bool isValidLHS(const bclib::matrix<int> & result);
        bool isValidLHS(const bclib::matrix<double> & result);
	};
}



#endif	/* OALHSTEST_H */

