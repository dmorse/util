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
 
};

TEST_BEGIN(BSplineBasisTest)
TEST_ADD(BSplineBasisTest, testConstructor)
TEST_END(BSplineBasisTest)

#endif
