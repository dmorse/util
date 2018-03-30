#ifndef UTIL_CARDINAL_B_SPLINE_TEST_H
#define UTIL_CARDINAL_B_SPLINE_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/math/Rational.h>
#include <util/math/CardinalBSpline.h>
#include <util/misc/Memory.h>

#include <fstream>

using namespace Util;

class CardinalBSplineTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {  Binomial::clear(); }
  
   void testConstructor()
   {
      printMethod(TEST_FUNC);
      int degree = 5;
      bool noisy = verbose();
      // bool noisy = true;
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
     TEST_ASSERT(Memory::total() == 0);

     CardinalBSpline s4(4);
     double shift = 0.0;
     double sum4a = computeSum(s4, shift);
     //std::cout << "sum_i b(i) = " << sum4a << std::endl;
     TEST_ASSERT(std::fabs(sum4a - 1.0) < 1.0E-7);

     shift = 0.2786538012;
     double sum4b = computeSum(s4, shift);
     //std::cout << "sum_i b(i+y) = " << sum4b << std::endl;
     TEST_ASSERT(std::fabs(sum4b - 1.0) < 1.0E-7);

     shift = -0.786538012;
     double sum4c = computeSum(s4, shift);
     //std::cout << "sum_i b(i+y) = " << sum4c << std::endl;
     TEST_ASSERT(std::fabs(sum4c - 1.0) < 1.0E-7);

     CardinalBSpline s5(5);
     shift = 0.0;
     double sum5a = computeSum(s5, shift);
     //std::cout << "sum_i b(i) = " << sum5a << std::endl;
     TEST_ASSERT(std::fabs(sum5a - 1.0) < 1.0E-7);

     shift = 0.2786538012;
     double sum5b = computeSum(s5, shift);
     //std::cout << "sum_i b(i+y) = " << sum5b << std::endl;
     TEST_ASSERT(std::fabs(sum5b - 1.0) < 1.0E-7);

     shift = -0.786538012;
     double sum5c = computeSum(s5, shift);
     //std::cout << "sum_i b(i+y) = " << sum5c << std::endl;
     TEST_ASSERT(std::fabs(sum5c - 1.0) < 1.0E-7);

   }

   // Compute sum_i b(i + shift) over all integer i.
   double computeSum(CardinalBSpline b, double shift) 
   {
      double sum = 0.0;
      for (int i = -3; i <= b.degree() + 3; ++i) {
         sum += b(double(i) + shift);
      }
      return sum;
   }

};

TEST_BEGIN(CardinalBSplineTest)
TEST_ADD(CardinalBSplineTest, testConstructor)
TEST_ADD(CardinalBSplineTest, testPolynomial)
TEST_ADD(CardinalBSplineTest, testEvaluate)
TEST_ADD(CardinalBSplineTest, testSum)
TEST_END(CardinalBSplineTest)

#endif
