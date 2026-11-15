#ifndef DISTRIBUTION_TEST_H
#define DISTRIBUTION_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/accumulators/Distribution.h>
#include <util/accumulators/IntDistribution.h>

#include <cmath>
#include <sstream>
#include <string>

using namespace Util;

class DistributionTest : public UnitTest
{

public:

   void testBinIndex();
   void testAssign();

   template <class T>
   std::string outputString(T& distribution)
   {
      std::ostringstream out;
      distribution.output(out);
      return out.str();
   }

};

/*
* A value just below max must be counted in the last bin.
*/
void DistributionTest::testBinIndex()
{
   printMethod(TEST_FUNC);

   Distribution distribution;
   distribution.setParam(0.0, 1.0, 3);
   TEST_ASSERT(distribution.binIndex(0.5) == 1);
   TEST_ASSERT(distribution.binIndex(std::nextafter(1.0, 0.0)) == 2);
}

/*
* Assignment to a Distribution or IntDistribution that has a histogram.
*/
void DistributionTest::testAssign()
{
   printMethod(TEST_FUNC);

   Distribution source, sameSize, otherSize;
   source.setParam(0.0, 1.0, 4);
   source.sample(0.2);
   source.sample(0.7);
   sameSize.setParam(-1.0, 1.0, 4);
   otherSize.setParam(0.0, 2.0, 8);
   sameSize = source;
   otherSize = source;
   TEST_ASSERT(outputString(sameSize) == outputString(source));
   TEST_ASSERT(outputString(otherSize) == outputString(source));

   IntDistribution intSource, intSameSize, intOtherSize;
   intSource.setParam(0, 3);
   intSource.sample(1);
   intSource.sample(2);
   intSameSize.setParam(-2, 1);
   intOtherSize.setParam(0, 9);
   intSameSize = intSource;
   intOtherSize = intSource;
   TEST_ASSERT(outputString(intSameSize) == outputString(intSource));
   TEST_ASSERT(outputString(intOtherSize) == outputString(intSource));
}

TEST_BEGIN(DistributionTest)
TEST_ADD(DistributionTest, testBinIndex)
TEST_ADD(DistributionTest, testAssign)
TEST_END(DistributionTest)

#endif
