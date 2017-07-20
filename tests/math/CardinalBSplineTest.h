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
      //bool noisy = verbose();
      bool noisy = true;
      CardinalBSpline s(degree, noisy);

      // Constructor has internal tests for continuity
   }
 
   void testPolynomial()
   {
      printMethod(TEST_FUNC);
      int degree = 3;
      CardinalBSpline s(degree);

      Polynomial<double> const & p = s[2];
      if (verbose()) {
         std::cout << p << std::endl;
      }
   }

   void testEvaluate()
   {
      printMethod(TEST_FUNC);
      CardinalBSpline s(3);

      // Test continuity and domain
      TEST_ASSERT(std::fabs( s(0.999999) - s(1.000001) ) < 0.0001 );
      TEST_ASSERT(std::fabs( s(2.999999) - s(3.000001) ) < 0.0001 );
      TEST_ASSERT(std::fabs( s(4.1) ) < 0.00001 );
      TEST_ASSERT(std::fabs( s(-0.1) ) < 0.00001 );

      Polynomial<double> const & p = s[2];
      TEST_ASSERT( eq( p(2.3), s(2.3)) );

      if (verbose()) {
         std::cout << std::endl;
         std::cout << "B_3(0.999999) = " << s(0.999999) << std::endl;
         std::cout << "B_3(1.000001) = " << s(1.000001) << std::endl;
         std::cout << "B_3(2.999999) = " << s(2.999999) << std::endl;
         std::cout << "B_3(3.000001) = " << s(3.000001) << std::endl;
         std::cout << "B_3(4.1)      = " << s(4.1) << std::endl;
         std::cout << "B_3(-0.1)     = " << s(-0.1) << std::endl;
      }
   }

   void testSum() 
   {
     printMethod(TEST_FUNC);
     CardinalBSpline s(4);

     double sum0 = 0.0;
     for (int i = -2; i <= 7; ++i) {
        sum0 += s(double(i));
     }
     //std::cout << "sum_i b(i) = " << sum0 << std::endl;
     TEST_ASSERT(std::fabs(sum0 - 1.0) < 1.0E-7);

     double shift = 0.2786538012;
     double sum1 = 0.0;
     for (int i = -2; i <= 7; ++i) {
        sum1 += s(double(i) + shift);
     }
     //std::cout << "sum_i b(i+y) = " << sum1 << std::endl;
     TEST_ASSERT(std::fabs(sum1 - 1.0) < 1.0E-7);
     
   }
};

TEST_BEGIN(CardinalBSplineTest)
TEST_ADD(CardinalBSplineTest, testConstructor)
TEST_ADD(CardinalBSplineTest, testPolynomial)
TEST_ADD(CardinalBSplineTest, testEvaluate)
TEST_ADD(CardinalBSplineTest, testSum)
TEST_END(CardinalBSplineTest)

#endif
