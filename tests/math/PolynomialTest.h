#ifndef UTIL_POLYNOMIAL_TEST_H
#define UTIL_POLYNOMIAL_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/math/Rational.h>
#include <util/math/Polynomial.h>
#include <util/containers/DArray.h>

#include <fstream>

using namespace Util;

class PolynomialTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {}
  
   void testDefaultConstructor()
   {
      printMethod(TEST_FUNC);
      Polynomial<Rational> r(12);
      TEST_ASSERT(r.size() == 0);
      TEST_ASSERT(r.capacity() == 12);
   } 

   void testArrayConstructor()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> coeffs;
      coeffs.allocate(3);
      coeffs[0] = Rational(2,3);
      coeffs[1] = Rational(3,-7);
      coeffs[2] = Rational(-2,1);

      Polynomial<Rational> r(coeffs);
      TEST_ASSERT(r.size() == 3);
      TEST_ASSERT(r.capacity() == 3);
      TEST_ASSERT(r[0].num() == 2);
      TEST_ASSERT(r[0].den() == 3);
      TEST_ASSERT(r[1].num() == -3);
      TEST_ASSERT(r[1].den() == 7);
      TEST_ASSERT(r[2].num() == -2);
      TEST_ASSERT(r[2].den() == 1);
   } 

   void testEquality()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(3);
      ac[0] = Rational(2,3);
      ac[1] = Rational(3,-7);
      ac[2] = Rational(-2,1);
      Polynomial<Rational> a(ac);

      DArray<Rational> bc;
      bc.allocate(2);
      bc[0] = Rational(2,1);
      bc[1] = Rational(1,1);
      Polynomial<Rational> b(bc);

      DArray<Rational> cc;
      cc.allocate(2);
      cc[0] = Rational(4,2);
      cc[1] = Rational(-2,-2);
      Polynomial<Rational> c(cc);

      TEST_ASSERT(a != b);
      TEST_ASSERT(a == a);
      TEST_ASSERT(b == b);
      TEST_ASSERT(b == c);
   }

   void testAddition()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(3);
      ac[0] = Rational(2,3);
      ac[1] = Rational(3,-7);
      ac[2] = Rational(-2,1);
      Polynomial<Rational> a(ac);
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a.capacity() == 3);

      DArray<Rational> bc;
      bc.allocate(2);
      bc[0] = Rational(2,1);
      bc[1] = Rational(1,1);
      Polynomial<Rational> b(bc);
      TEST_ASSERT(b.size() == 2);
      TEST_ASSERT(b.capacity() == 2);

      Polynomial<Rational> c(a);
      a += b;
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a[0] == c[0] + b[0]);
      TEST_ASSERT(a[1] == c[1] + b[1]);
      TEST_ASSERT(a[2] == c[2]);
      a -= b;
      TEST_ASSERT(a == c);
      a += b;
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a[0] == c[0] + b[0]);
      TEST_ASSERT(a[1] == c[1] + b[1]);
      TEST_ASSERT(a[2] == c[2]);

      b += c;
      TEST_ASSERT(b.size() == 3);
      TEST_ASSERT(a[0] == b[0]);
      TEST_ASSERT(a[1] == b[1]);
      TEST_ASSERT(a[2] == b[2]);
      TEST_ASSERT(a == b);

   }

   void testScalarMultiplication()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(3);
      ac[0] = Rational(2,3);
      ac[1] = Rational(3,-7);
      ac[2] = Rational(-2,1);
      Polynomial<Rational> a(ac);
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a.capacity() == 3);

      Rational b = Rational(3, 2);
      a *= b;
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a.capacity() == 3);
      TEST_ASSERT(a[0] == Rational(1));
      TEST_ASSERT(a[1] == Rational(-9, 14));
      TEST_ASSERT(a[2] == Rational(-3, 1));
   }

   void testScalarDivision()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(3);
      ac[0] = Rational(2,3);
      ac[1] = Rational(3,-7);
      ac[2] = Rational(-2,1);
      Polynomial<Rational> a(ac);
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a.capacity() == 3);

      Rational b = Rational(3, 2);
      a /= b;
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a.capacity() == 3);
      TEST_ASSERT(a[0] == Rational(4, 9));
      TEST_ASSERT(a[1] == Rational(-6, 21));
      TEST_ASSERT(a[2] == Rational(-4, 3));

   }

   void testPolynomialMultiplication()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(2);
      ac[0] = Rational(2);
      ac[1] = Rational(3);
      Polynomial<Rational> a(ac);
      TEST_ASSERT(a.size() == 2);
      TEST_ASSERT(a.capacity() == 2);

      DArray<Rational> bc;
      bc.allocate(2);
      bc[0] = Rational(2);
      bc[1] = Rational(1);
      Polynomial<Rational> b(bc);
      TEST_ASSERT(b.size() == 2);
      TEST_ASSERT(b.capacity() == 2);

      Polynomial<Rational> c(a);

      a *= b;
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a[0] == 4);
      TEST_ASSERT(a[1] == 8);
      TEST_ASSERT(a[2] == 3);

      b *= c;
      TEST_ASSERT(b.size() == 3);
      TEST_ASSERT(b[0] == 4);
      TEST_ASSERT(b[1] == 8);
      TEST_ASSERT(b[2] == 3);
      TEST_ASSERT(a == b);

   }

   void testNegation()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> coeffs;
      coeffs.allocate(3);
      coeffs[0] = Rational(2,3);
      coeffs[1] = Rational(3,-7);
      coeffs[2] = Rational(-2,1);

      Polynomial<Rational> r(coeffs);
      Polynomial<Rational> s = -r;
       
      TEST_ASSERT(s.size() == 3);
      TEST_ASSERT(s.capacity() == 3);
      TEST_ASSERT(s[0].num() == -2);
      TEST_ASSERT(s[0].den() == 3);
      TEST_ASSERT(s[1].num() == 3);
      TEST_ASSERT(s[1].den() == 7);
      TEST_ASSERT(s[2].num() == 2);
      TEST_ASSERT(s[2].den() == 1);
   }
 
};

TEST_BEGIN(PolynomialTest)
TEST_ADD(PolynomialTest, testDefaultConstructor)
TEST_ADD(PolynomialTest, testArrayConstructor)
TEST_ADD(PolynomialTest, testEquality)
TEST_ADD(PolynomialTest, testAddition)
TEST_ADD(PolynomialTest, testScalarMultiplication)
TEST_ADD(PolynomialTest, testScalarDivision)
TEST_ADD(PolynomialTest, testPolynomialMultiplication)
TEST_ADD(PolynomialTest, testNegation)
TEST_END(PolynomialTest)

#endif
