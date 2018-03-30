#ifndef UTIL_RATIONAL_TEST_H
#define UTIL_RATIONAL_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/math/Rational.h>
#include <util/misc/Memory.h>

#include <fstream>

using namespace Util;

class RationalTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {}
  
   void testDefaultConstructor()
   {
      printMethod(TEST_FUNC);
      Rational r;
      TEST_ASSERT(r.num() == 0);
      TEST_ASSERT(r.den() == 1);
      TEST_ASSERT(Memory::total() == 0);
   } 

   void testNumDenConstructor1()
   {
      printMethod(TEST_FUNC);
      Rational r(4, 7);
      TEST_ASSERT(r.num() == 4);
      TEST_ASSERT(r.den() == 7);
   } 

   void testNumDenConstructor2()
   {
      printMethod(TEST_FUNC);
      Rational r(12, -3);
      TEST_ASSERT(r.num() == -4);
      TEST_ASSERT(r.den() == 1);
   } 

   void testNumDenConstructor3()
   {
      printMethod(TEST_FUNC);
      Rational r(49, -21);
      TEST_ASSERT(r.num() == -7);
      TEST_ASSERT(r.den() == 3);
      Rational s = -r;
      TEST_ASSERT(s.num() == 7);
      TEST_ASSERT(s.den() == 3);
   }

   void testIntConstructor()
   {
      printMethod(TEST_FUNC);
      Rational r(-21);
      TEST_ASSERT(r.num() == -21);
      TEST_ASSERT(r.den() == 1);
   } 

   void testCopyConstructor()
   {
      printMethod(TEST_FUNC);
      Rational r(49, -21);
      Rational s(r);
      TEST_ASSERT(s.num() == -7);
      TEST_ASSERT(s.den() == 3);
   } 

   void testCopyAssignment()
   {
      printMethod(TEST_FUNC);
      Rational s;
      Rational r(49, -21);
      s = r;
      TEST_ASSERT(s.num() == -7);
      TEST_ASSERT(s.den() == 3);
   } 

   void testIntAssignment()
   {
      printMethod(TEST_FUNC);
      Rational r(-21);
      TEST_ASSERT(r.num() == -21);
      TEST_ASSERT(r.den() == 1);
   } 

   void testCastDouble()
   {
      printMethod(TEST_FUNC);
      Rational r(2, 3);
      double f;
      f = r;
      // std::cout << "f = " << f << std::endl;
      TEST_ASSERT(eq(f, 2.0/3.0));
   } 

   void testEquality()
   {
      printMethod(TEST_FUNC);
      Rational a(-2);
      Rational b(4, -2);
      Rational c(-4,-2);

      TEST_ASSERT(a == b);
      TEST_ASSERT(a == -2);
      TEST_ASSERT(-2 == a);
      TEST_ASSERT(b == -2);
      TEST_ASSERT(a != c);
      TEST_ASSERT(a != 2);
      TEST_ASSERT(2 != a);
      TEST_ASSERT(c == 2);
      TEST_ASSERT(2 == c);
      TEST_ASSERT(c != -2);
      TEST_ASSERT(-2 != c);
   } 

   void testUnaryNegation()
   {
      printMethod(TEST_FUNC);
      Rational r(-7, 3);
      Rational s = -r;
      TEST_ASSERT(s.num() == 7);
      TEST_ASSERT(s.den() == 3);
      Rational t = -s;
      TEST_ASSERT(t == r);
   }

   void testAddSubtractAssignment()
   {
      printMethod(TEST_FUNC);
      Rational a(3, -7);
      Rational b(2, 5);
      Rational c(a);
      a += b;
      TEST_ASSERT(a.num() == -1);
      TEST_ASSERT(a.den() == 35);
      a -= b;
      TEST_ASSERT(a == c);
   } 

   void testAddSubtractIntAssignment()
   {
      printMethod(TEST_FUNC);
      Rational a(3, -7);
      Rational c(a);
      int b = -4;
      a += b;
      TEST_ASSERT(a.num() == -31);
      TEST_ASSERT(a.den() == 7);
      a -= b;
      TEST_ASSERT(a == c);
   } 

   void testAddSubtract()
   {
      printMethod(TEST_FUNC);
      Rational a(3, -7);
      Rational b(2, 5);
      Rational c(a);

      // Add and subtract rationals
      Rational d = a + b;
      TEST_ASSERT(d.num() == -1);
      TEST_ASSERT(d.den() == 35);
      a = d - b;
      TEST_ASSERT(a == c);

      // Add and subtract integers
      d = a + 4;
      TEST_ASSERT(d.num() == 25);
      TEST_ASSERT(d.den() == 7);
      a = d - 4;
      TEST_ASSERT(a == c);
   } 

   void testMultiplyDivideAssignment()
   {
      printMethod(TEST_FUNC);
      Rational a(3, -7);
      Rational b(2, 5);
      Rational c(a);
      a *= b;
      TEST_ASSERT(a.num() == -6);
      TEST_ASSERT(a.den() == 35);
      a /= b;
      TEST_ASSERT(a == c);
   } 

   void testMultiplyDivideIntAssignment()
   {
      printMethod(TEST_FUNC);
      Rational a(3, -7);
      Rational c(a);
      Rational b = 7;

      a *= b;
      TEST_ASSERT(a.num() == -3);
      TEST_ASSERT(a.den() == 1);
      TEST_ASSERT(a == b*c);
      a /= b;
      TEST_ASSERT(c.num() == -3);
      TEST_ASSERT(c.den() == 7);
      TEST_ASSERT(a == c);
   } 

   void testMultiplyDivide()
   {
      printMethod(TEST_FUNC);
      Rational a(3, -7);
      Rational b(2, 5);
      Rational c(a);

      // Multiply and divide rationals
      Rational d = a * b;
      TEST_ASSERT(d.num() == -6);
      TEST_ASSERT(d.den() == 35);
      //std::cout <<  d;
      TEST_ASSERT(d == b*a);
      TEST_ASSERT((d/b)*(b/d) == 1);
      a = d / b;
      TEST_ASSERT(a == c);

      // Multiply and divide rationals
      d = a * 7;
      TEST_ASSERT(d.num() == -3);
      TEST_ASSERT(d.den() == 1);
      TEST_ASSERT(d == 7*a);
      TEST_ASSERT((d/7)*(7/d) == 1);
      a = d / 7;
      TEST_ASSERT(a == c);
      TEST_ASSERT(Memory::total() == 0);
   } 

};

TEST_BEGIN(RationalTest)
TEST_ADD(RationalTest, testDefaultConstructor)
TEST_ADD(RationalTest, testNumDenConstructor1)
TEST_ADD(RationalTest, testNumDenConstructor2)
TEST_ADD(RationalTest, testNumDenConstructor3)
TEST_ADD(RationalTest, testIntConstructor)
TEST_ADD(RationalTest, testCopyConstructor)
TEST_ADD(RationalTest, testCopyAssignment)
TEST_ADD(RationalTest, testIntAssignment)
TEST_ADD(RationalTest, testCastDouble)
TEST_ADD(RationalTest, testEquality)
TEST_ADD(RationalTest, testUnaryNegation)
TEST_ADD(RationalTest, testAddSubtractAssignment)
TEST_ADD(RationalTest, testAddSubtractIntAssignment)
TEST_ADD(RationalTest, testAddSubtract)
TEST_ADD(RationalTest, testMultiplyDivideAssignment)
TEST_ADD(RationalTest, testMultiplyDivideIntAssignment)
TEST_ADD(RationalTest, testMultiplyDivide)
TEST_END(RationalTest)

#endif
