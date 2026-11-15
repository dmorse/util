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
   void testSetNEnsemble();

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

/*
* A change of nEnsemble must clear the accumulator.
*/
void MeanSqDispArrayTest::testSetNEnsemble()
{
   printMethod(TEST_FUNC);

   MeanSqDispArray<double> accumulator;
   accumulator.setParam(4, 8);
   DArray<double> values;
   values.allocate(4);
   int i, j;

   // Sample 3 values of 4 sequences, then 2 values of 2 sequences
   for (i = 0; i < 3; ++i) {
      for (j = 0; j < 4; ++j) {
         values[j] = 10.0*double(i);
      }
      accumulator.sample(values);
   }
   accumulator.setNEnsemble(2);
   for (i = 0; i < 2; ++i) {
      for (j = 0; j < 4; ++j) {
         values[j] = double(i);
      }
      accumulator.sample(values);
   }
   TEST_ASSERT(accumulator.nSample() == 2);

   // Return to 4 sequences: results as for a new accumulator
   accumulator.setNEnsemble(4);
   MeanSqDispArray<double> fresh;
   fresh.setParam(4, 8);
   for (i = 0; i < 5; ++i) {
      for (j = 0; j < 4; ++j) {
         values[j] = double(i*j);
      }
      accumulator.sample(values);
      fresh.sample(values);
   }
   std::ostringstream out, freshOut;
   accumulator.output(out);
   fresh.output(freshOut);
   TEST_ASSERT(out.str() == freshOut.str());
}

TEST_BEGIN(MeanSqDispArrayTest)
TEST_ADD(MeanSqDispArrayTest, testSampleInt)
TEST_ADD(MeanSqDispArrayTest, testSetNEnsemble)
TEST_END(MeanSqDispArrayTest)

#endif
