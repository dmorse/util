#ifndef DISTRIBUTION_TEST_H
#define DISTRIBUTION_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/accumulators/Distribution.h>

#include <cmath>

using namespace Util;

class DistributionTest : public UnitTest
{

public:

   void testBinIndex();

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

TEST_BEGIN(DistributionTest)
TEST_ADD(DistributionTest, testBinIndex)
TEST_END(DistributionTest)

#endif
