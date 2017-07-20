#ifndef UTIL_B_SPLINE_BASIS_TEST_H
#define UTIL_B_SPLINE_BASIS_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/math/Rational.h>
#include <util/math/BSplineBasis.h>

#include <fstream>

using namespace Util;

class BSplineBasisTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {}
  
   void testConstructor()
   {
      printMethod(TEST_FUNC);
      bool verbose = true;
      BSplineBasis s(5, verbose);
   }
 
   void testPolynomial()
   {
      printMethod(TEST_FUNC);
      BSplineBasis s(3);

      Polynomial<double> const & p = s[2];
      std::cout << p << std::endl;
   }

   void testEvaluate()
   {
      printMethod(TEST_FUNC);
      BSplineBasis s(3);

      std::cout << std::endl;
      std::cout << "B_3(0.999999) = " << s(0.999999) << std::endl;
      std::cout << "B_3(1.000001) = " << s(1.000001) << std::endl;
      std::cout << "B_3(2.999999) = " << s(2.999999) << std::endl;
      std::cout << "B_3(3.000001) = " << s(3.000001) << std::endl;
      std::cout << "B_3(4.1)      = " << s(4.1) << std::endl;
      std::cout << "B_3(-0.1)     = " << s(-0.1) << std::endl;
   }

};

TEST_BEGIN(BSplineBasisTest)
TEST_ADD(BSplineBasisTest, testConstructor)
TEST_ADD(BSplineBasisTest, testPolynomial)
TEST_ADD(BSplineBasisTest, testEvaluate)
TEST_END(BSplineBasisTest)

#endif
