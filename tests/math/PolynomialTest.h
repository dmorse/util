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

   void testConstantConstructor()
   {
      printMethod(TEST_FUNC);
      Rational c(4, 5);
      Polynomial<Rational> r(c);
      TEST_ASSERT(r.size() == 1);
      TEST_ASSERT(r[0] == c);
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

   void testAssignment1()
   {
      printMethod(TEST_FUNC);

      // Construct r
      DArray<Rational> coeffs;
      coeffs.allocate(3);
      coeffs[0] = Rational(2,3);
      coeffs[1] = Rational(3,-7);
      coeffs[2] = Rational(-2,1);
      Polynomial<Rational> r(coeffs);

      // Assign s <- r
      Polynomial<Rational> s;
      s = r;

      TEST_ASSERT(s.size() == r.size());
      TEST_ASSERT(s[0] == r[0]);
      TEST_ASSERT(s[1] == r[1]);
      TEST_ASSERT(s[2] == r[2]);
   }

   void testAssignment2()
   {
      printMethod(TEST_FUNC);

      // Construct r
      DArray<Rational> coeffs;
      coeffs.allocate(3);
      coeffs[0] = Rational(2,3);
      coeffs[1] = Rational(3,-7);
      coeffs[2] = Rational(-2,1);
      Polynomial<Rational> r(coeffs);
      TEST_ASSERT(r.size() == 3);

      // Assign s <- r
      Polynomial<double> s;
      s = r;

      TEST_ASSERT(s.size() == r.size());
      TEST_ASSERT(eq(s[0], 2.0/3.0));
      TEST_ASSERT(eq(s[1], -3.0/7.0));
      TEST_ASSERT(eq(s[2], -2.0));
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

   void testAdditionSubtraction()
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

      // Test operations involving null polynomial
      Polynomial<Rational> d;
      TEST_ASSERT(d.size() == 0);
      d += d;
      TEST_ASSERT(d.size() == 0);
      d -= d;
      TEST_ASSERT(d.size() == 0);
      a += d;
      TEST_ASSERT(a == c);
      a -= d;
      TEST_ASSERT(a == c);
      d += a;
      TEST_ASSERT(d == a);
      d.clear();
      d -= a;
      d += a;
      TEST_ASSERT(d.size() == a.size());

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

   void testIntegrate()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(3);
      ac[0] = Rational(2);
      ac[1] = Rational(3);
      ac[2] = Rational(4);
      Polynomial<Rational> a(ac);
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a.capacity() == 3);

      Polynomial<Rational> b = a.integrate();
      TEST_ASSERT(b.size() == 4);
      TEST_ASSERT(b.capacity() == 4);
      TEST_ASSERT(b[0] == Rational(0));
      TEST_ASSERT(b[1] == Rational(2));
      TEST_ASSERT(b[2] == Rational(3,2));
      TEST_ASSERT(b[3] == Rational(4,3));

      Polynomial<Rational> c = b.differentiate();
      TEST_ASSERT(c == a);
   }

   void testReflect()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(4);
      ac[0] = Rational(2);
      ac[1] = Rational(3);
      ac[2] = Rational(4);
      ac[3] = Rational(5);
      Polynomial<Rational> a(ac);
      TEST_ASSERT(a.size() == 4);
      TEST_ASSERT(a.capacity() == 4);

      Polynomial<Rational> b = a.reflect();
      TEST_ASSERT(b.size() == 4);
      TEST_ASSERT(b.capacity() == 4);
      TEST_ASSERT(b[0] == Rational(2));
      TEST_ASSERT(b[1] == Rational(-3));
      TEST_ASSERT(b[2] == Rational(4));
      TEST_ASSERT(b[3] == Rational(-5));
   }

   void testShift()
   {
      printMethod(TEST_FUNC);

      DArray<Rational> ac;
      ac.allocate(3);
      ac[0] = Rational(2);
      ac[1] = Rational(3);
      ac[2] = Rational(1);
      Polynomial<Rational> a(ac);
      TEST_ASSERT(a.size() == 3);
      TEST_ASSERT(a.capacity() == 3);

      Rational c(2);
      Polynomial<Rational> b = a.shift(c);
      TEST_ASSERT(b.size() == 3);
      TEST_ASSERT(b.capacity() == 3);
      TEST_ASSERT(b[2] == a[2]);
      TEST_ASSERT(b[1] == a[1] + 2*a[2]*c );
      TEST_ASSERT(b[0] == a[0] + a[1]*c + a[2]*c*c);
   }

   void testMonomial()
   {
      printMethod(TEST_FUNC);

      Polynomial<Rational> r = Polynomial<Rational>::monomial(2);

      TEST_ASSERT(r.size() == 3);
      TEST_ASSERT(r.capacity() == 3);
      TEST_ASSERT(r[0] == Rational(0));
      TEST_ASSERT(r[1] == Rational(0));
      TEST_ASSERT(r[2] == Rational(1));
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
TEST_ADD(PolynomialTest, testConstantConstructor)
TEST_ADD(PolynomialTest, testArrayConstructor)
TEST_ADD(PolynomialTest, testAssignment1)
TEST_ADD(PolynomialTest, testAssignment2)
TEST_ADD(PolynomialTest, testEquality)
TEST_ADD(PolynomialTest, testAdditionSubtraction)
TEST_ADD(PolynomialTest, testScalarMultiplication)
TEST_ADD(PolynomialTest, testScalarDivision)
TEST_ADD(PolynomialTest, testPolynomialMultiplication)
TEST_ADD(PolynomialTest, testIntegrate)
TEST_ADD(PolynomialTest, testReflect)
TEST_ADD(PolynomialTest, testShift)
TEST_ADD(PolynomialTest, testMonomial)
TEST_ADD(PolynomialTest, testNegation)
TEST_END(PolynomialTest)

#endif
