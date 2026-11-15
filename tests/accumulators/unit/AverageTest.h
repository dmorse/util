#ifndef AVERAGE_TEST_H
#define AVERAGE_TEST_H

#include <test/UnitTest.h>
#include <test/ParamFileTest.h>
#include <test/UnitTestRunner.h>

#include <util/accumulators/Average.h>
#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/MemoryCounter.h>
#include <util/archives/BinaryFileIArchive.h>
#include <util/archives/BinaryFileOArchive.h>

#include <cmath>
#include <sstream>

using namespace Util;

class AverageTest : public UnitTest
{

   Average accumulator_;

public:

   AverageTest();
   ~AverageTest();

   void setUp();
   void readData();
   void testReadParam();
   void testSample();
   void testSerialize();
   void testSerializeFile();
   void testSaveLoad();
   void testClearReuse();
   void testLoadUsed();

};

AverageTest::AverageTest(){}
AverageTest::~AverageTest(){}

void AverageTest::setUp() {
   std::ifstream paramFile;
   openInputFile("in/Average", paramFile); 
   accumulator_.readParam(paramFile);
   paramFile.close();
}
   
void AverageTest::readData() 
{
   int i, n;
   double x;
   std::ifstream dataFile;
   openInputFile("in/data", dataFile);
   dataFile >> n;
   for (i = 0; i < n; ++i) {
      dataFile >> x;
      accumulator_.sample(x);
   }
   dataFile.close();
}

void AverageTest::testReadParam() 
{
   printMethod(TEST_FUNC);

   printEndl();      
   accumulator_.writeParam(std::cout);
}

void AverageTest::testSample() 
{
   printMethod(TEST_FUNC);

   readData();

   printEndl();      
   accumulator_.output(std::cout);
}

void AverageTest::testSerialize() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   MemoryOArchive u;
   int size = memorySize(accumulator_);
   u.allocate(size);

   std::cout << size << std::endl;

   u << accumulator_;
   TEST_ASSERT(u.cursor() == u.begin() + size);

   MemoryIArchive v;
   v = u;

   Average clone;
   v >> clone;
   TEST_ASSERT(v.cursor() == u.begin() + size);

   clone.output(std::cout);
}

void AverageTest::testSerializeFile() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   BinaryFileOArchive u;
   openOutputFile("tmp/AverageTestSerializeFile", u.file());
   u << accumulator_;
   u.file().close();

   Average clone;
   BinaryFileIArchive v;
   openInputFile("tmp/AverageTestSerializeFile", v.file());
   v >> clone;
   v.file().close();
   
   clone.output(std::cout);
}

void AverageTest::testSaveLoad() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   BinaryFileOArchive u;
   openOutputFile("tmp/AverageTestSaveLoad", u.file());
   accumulator_.save(u);
   u.file().close();

   Average clone;
   BinaryFileIArchive v;
   openInputFile("tmp/AverageTestSaveLoad", v.file());
   clone.load(v);
   v.file().close();
 
   clone.writeParam(std::cout);
   clone.output(std::cout);
}

/*
* Clear an Average that has descendant stages and sample again, as an
* averaging analyzer does in a second simulation. The results must be
* those of a new Average that samples the same values.
*/
void AverageTest::testClearReuse()
{
   printMethod(TEST_FUNC);

   Average reused;
   Average fresh;
   reused.setNSamplePerBlock(4);
   fresh.setNSamplePerBlock(4);
   int i;
   for (i = 0; i < 100; ++i) {
      reused.sample(1.0 + std::sin(0.37*i));
   }
   reused.clear();
   TEST_ASSERT(reused.nSample() == 0);

   double x;
   for (i = 0; i < 70; ++i) {
      x = 2.0 + std::cos(0.53*i);
      reused.sample(x);
      fresh.sample(x);
   }
   TEST_ASSERT(reused.nSample() == 70);
   TEST_ASSERT(reused.average() == fresh.average());
   TEST_ASSERT(reused.variance() == fresh.variance());
   TEST_ASSERT(reused.blockingError() == fresh.blockingError());
   std::ostringstream reusedOut, freshOut;
   reused.output(reusedOut);
   fresh.output(freshOut);
   TEST_ASSERT(reusedOut.str() == freshOut.str());

   // Clear twice, then destroy
   reused.clear();
   reused.clear();
   TEST_ASSERT(reused.nSample() == 0);
}

/*
* Loading an Average from an archive must replace all of its stages.
*/
void AverageTest::testLoadUsed()
{
   printMethod(TEST_FUNC);

   readData();

   // Saved states: the test data (1000 values), and 8 values, too few
   // for any stage to have the 16 values used by blockingError()
   Average few;
   for (int i = 0; i < 8; ++i) {
      few.sample(std::sin(0.37*i));
   }
   BinaryFileOArchive u;
   openOutputFile("tmp/AverageTestLoadUsed", u.file());
   accumulator_.save(u);
   few.save(u);
   u.file().close();

   // Average objects with more values, and more stages
   Average used1, used2, used3;
   for (int i = 0; i < 5000; ++i) {
      used1.sample(double(i % 7));
      used2.sample(double(i % 7));
      used3.sample(double(i % 7));
   }

   // Load the saved states with load() and with operator >>
   BinaryFileIArchive v1;
   openInputFile("tmp/AverageTestLoadUsed", v1.file());
   used1.load(v1);
   used3.load(v1);
   v1.file().close();
   BinaryFileIArchive v2;
   openInputFile("tmp/AverageTestLoadUsed", v2.file());
   v2 >> used2;
   v2.file().close();

   // The output lists every stage
   std::ostringstream out, out1, out2;
   accumulator_.output(out);
   used1.output(out1);
   used2.output(out2);
   TEST_ASSERT(out1.str() == out.str());
   TEST_ASSERT(out2.str() == out.str());
   TEST_ASSERT(used3.nSample() == 8);
   TEST_ASSERT(used3.blockingError() == few.blockingError());
}

TEST_BEGIN(AverageTest)
TEST_ADD(AverageTest, testReadParam)
TEST_ADD(AverageTest, testSample)
TEST_ADD(AverageTest, testSerialize)
TEST_ADD(AverageTest, testSerializeFile)
TEST_ADD(AverageTest, testSaveLoad)
TEST_ADD(AverageTest, testClearReuse)
TEST_ADD(AverageTest, testLoadUsed)
TEST_END(AverageTest)

#endif
