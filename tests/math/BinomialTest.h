#ifndef UTIL_BINOMIAL_TEST_H
#define UTIL_BINOMIAL_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/math/Binomial.h>

#include <fstream>

using namespace Util;

class BinomialTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {}

  
   void testSetup()
   {
      printMethod(TEST_FUNC);
      Binomial::setup(4);
   } 

   void testReSetup()
   {
      printMethod(TEST_FUNC);
      Binomial::setup(4);
      Binomial::setup(6);
   }
 
   void testCoeff0()
   {
      printMethod(TEST_FUNC);
      TEST_ASSERT(Binomial::coeff(0, 0) == 1);
   }

   void testCoeff1()
   {
      printMethod(TEST_FUNC);
      TEST_ASSERT(Binomial::coeff(0, 0) == 1);
      TEST_ASSERT(Binomial::coeff(1, 0) == 1);
      TEST_ASSERT(Binomial::coeff(1, 1) == 1);
      TEST_ASSERT(Binomial::coeff(2, 0) == 1);
      TEST_ASSERT(Binomial::coeff(2, 1) == 2);
      TEST_ASSERT(Binomial::coeff(2, 2) == 1);
   }

   void testCoeff2()
   {
      printMethod(TEST_FUNC);
      Binomial::setup(2);
      Binomial::setup(4);
      TEST_ASSERT(Binomial::coeff(0, 0) == 1);
      TEST_ASSERT(Binomial::coeff(1, 0) == 1);
      TEST_ASSERT(Binomial::coeff(1, 1) == 1);
      TEST_ASSERT(Binomial::coeff(2, 0) == 1);
      TEST_ASSERT(Binomial::coeff(2, 1) == 2);
      TEST_ASSERT(Binomial::coeff(2, 2) == 1);
      TEST_ASSERT(Binomial::coeff(3, 0) == 1);
      TEST_ASSERT(Binomial::coeff(3, 1) == 3);
      TEST_ASSERT(Binomial::coeff(3, 2) == 3);
      TEST_ASSERT(Binomial::coeff(3, 3) == 1);
      TEST_ASSERT(Binomial::coeff(4, 0) == 1);
      TEST_ASSERT(Binomial::coeff(4, 1) == 4);
      TEST_ASSERT(Binomial::coeff(4, 2) == 6);
      TEST_ASSERT(Binomial::coeff(4, 3) == 4);
      TEST_ASSERT(Binomial::coeff(4, 4) == 1);
   }
 
};

TEST_BEGIN(BinomialTest)
TEST_ADD(BinomialTest, testSetup)
TEST_ADD(BinomialTest, testReSetup)
TEST_ADD(BinomialTest, testCoeff0)
TEST_ADD(BinomialTest, testCoeff1)
TEST_ADD(BinomialTest, testCoeff2)
TEST_END(BinomialTest)

#endif
