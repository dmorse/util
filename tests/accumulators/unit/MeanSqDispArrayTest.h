#ifndef MEAN_SQ_DISP_ARRAY_TEST_H
#define MEAN_SQ_DISP_ARRAY_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/accumulators/MeanSqDispArray.h>
#include <util/containers/DArray.h>

#include <sstream>

using namespace Util;

class MeanSqDispArrayTest : public UnitTest
{

public:

   void testSampleInt();

};

/*
* Integer displacements with squares beyond the range of an int.
*/
void MeanSqDispArrayTest::testSampleInt()
{
   printMethod(TEST_FUNC);

   MeanSqDispArray<int> accumulator;
   accumulator.setParam(1, 4);
   DArray<int> values;
   values.allocate(1);
   values[0] = 0;
   accumulator.sample(values);
   values[0] = 50000;
   accumulator.sample(values);

   // Output: lag and mean-squared displacement for lags 0 and 1
   std::ostringstream out;
   accumulator.output(out);
   std::istringstream in(out.str());
   int lag;
   double msd;
   in >> lag >> msd >> lag >> msd;
   TEST_ASSERT(lag == 1);
   TEST_ASSERT(msd == 2.5E+9);
}

TEST_BEGIN(MeanSqDispArrayTest)
TEST_ADD(MeanSqDispArrayTest, testSampleInt)
TEST_END(MeanSqDispArrayTest)

#endif
