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
      std::cout << std::endl;
      Binomial::setup(4);
   } 

};

TEST_BEGIN(BinomialTest)
TEST_ADD(BinomialTest, testSetup)
TEST_END(BinomialTest)

#endif
