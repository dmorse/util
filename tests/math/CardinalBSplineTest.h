#ifndef UTIL_CARDINAL_B_SPLINE_TEST_H
#define UTIL_CARDINAL_B_SPLINE_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/math/Rational.h>
#include <util/math/CardinalBSpline.h>

#include <fstream>

using namespace Util;

class CardinalBSplineTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {}
  
   void testConstructor()
   {
      printMethod(TEST_FUNC);
      int degree = 5;
      bool verbose = true;
      CardinalBSpline s(degree, verbose);
   }
 
   void testPolynomial()
   {
      printMethod(TEST_FUNC);
      int degree = 3;
      CardinalBSpline s(degree);

      Polynomial<double> const & p = s[2];
      std::cout << p << std::endl;
   }

   void testEvaluate()
   {
      printMethod(TEST_FUNC);
      CardinalBSpline s(3);

      std::cout << std::endl;
      std::cout << "B_3(0.999999) = " << s(0.999999) << std::endl;
      std::cout << "B_3(1.000001) = " << s(1.000001) << std::endl;
      std::cout << "B_3(2.999999) = " << s(2.999999) << std::endl;
      std::cout << "B_3(3.000001) = " << s(3.000001) << std::endl;
      std::cout << "B_3(4.1)      = " << s(4.1) << std::endl;
      std::cout << "B_3(-0.1)     = " << s(-0.1) << std::endl;
   }

};

TEST_BEGIN(CardinalBSplineTest)
TEST_ADD(CardinalBSplineTest, testConstructor)
TEST_ADD(CardinalBSplineTest, testPolynomial)
TEST_ADD(CardinalBSplineTest, testEvaluate)
TEST_END(CardinalBSplineTest)

#endif
