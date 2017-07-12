#ifndef UTIL_GCD_TEST_H
#define UTIL_GCD_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/math/gcd.h>

#include <fstream>

using namespace Util;

class GcdTest : public UnitTest 
{

public:

   void setUp()
   {}

   void tearDown()
   {}

  
   void test1()
   {
      printMethod(TEST_FUNC);
      int a = 24;
      int b = 18;
      int c = gcd(a, b);
      TEST_ASSERT(a%c == 0);
      TEST_ASSERT(b%c == 0);
      TEST_ASSERT(c == 6);
      TEST_ASSERT(c == gcd(b, a));
   } 

   void test2()
   {
      printMethod(TEST_FUNC);
      int a =  49;
      int b = -21;
      int c = gcd(49,-21);
      TEST_ASSERT(a%c == 0);
      TEST_ASSERT(b%c == 0);
      TEST_ASSERT(c == 7);
      TEST_ASSERT(c == gcd(b, a));
   }

   void test3()
   {
      printMethod(TEST_FUNC);
      int a = -49;
      int b = 0;
      int c = gcd(a, b);
      TEST_ASSERT(a%c == 0);
      TEST_ASSERT(b%c == 0);
      TEST_ASSERT(c == 49);
      TEST_ASSERT(c == gcd(b, a));
   }

};

TEST_BEGIN(GcdTest)
TEST_ADD(GcdTest, test1)
TEST_ADD(GcdTest, test2)
TEST_ADD(GcdTest, test3)
TEST_END(GcdTest)

#endif
