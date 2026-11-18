#ifndef AUTOCORR_TEST_H
#define AUTOCORR_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/accumulators/AutoCorr.h>
#include <util/accumulators/AutoCorrelation.tpp>
#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/MemoryCounter.h>
#include <util/archives/BinaryFileIArchive.h>
#include <util/archives/BinaryFileOArchive.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace Util;

class AutoCorrTest : public UnitTest
{

   AutoCorr<double, double> accumulator_;

public:

   AutoCorrTest();
   ~AutoCorrTest();

   void setUp(); 
   //void tearDown();
   void readData();
   void testReadParam(); 
   void testSample();
   void testSerialize();
   void testSerializeFile();
   void testSaveLoad(); 
   void testCorrTime();
   void testAutoCorrelationClear();
   void testAutoCorrelationLoad();

};

AutoCorrTest::AutoCorrTest(){}
AutoCorrTest::~AutoCorrTest(){}

void AutoCorrTest::setUp() 
{
   std::ifstream paramFile; 
   openInputFile("in/AutoCorr", paramFile); 
   accumulator_.readParam(paramFile);
   paramFile.close();
}

//void AutoCorrTest::tearDown(){}

void AutoCorrTest::readData() 
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

void AutoCorrTest::testReadParam() 
{
   printMethod(TEST_FUNC);

   printEndl();
   accumulator_.writeParam(std::cout);
}

void AutoCorrTest::testSample() 
{
   printMethod(TEST_FUNC);

   readData();

   printEndl();
   accumulator_.output(std::cout);
}

void AutoCorrTest::testSerialize() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   int size = memorySize(accumulator_);

   MemoryOArchive u;
   u.allocate(size);

   std::cout << size << std::endl;

   u << accumulator_;
   TEST_ASSERT(u.cursor() == u.begin() + size);

   MemoryIArchive v;
   v = u;

   AutoCorr<double, double> clone;
   v & clone;

   clone.output(std::cout);
}

void AutoCorrTest::testSerializeFile() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   BinaryFileOArchive u;
   openOutputFile("tmp/AutoCorrTestSerializeFile", u.file());
   u << accumulator_;
   u.file().close();

   AutoCorr<double, double> clone;
   BinaryFileIArchive v;
   openInputFile("tmp/AutoCorrTestSerializeFile", v.file());
   v >> clone;
   v.file().close();
   
   clone.output(std::cout);
}

void AutoCorrTest::testSaveLoad() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   BinaryFileOArchive u;
   openOutputFile("tmp/AutoCorrTestSaveLoad", u.file());
   accumulator_.save(u);
   u.file().close();

   AutoCorr<double, double> clone;
   BinaryFileIArchive v;
   openInputFile("tmp/AutoCorrTestSaveLoad", v.file());
   clone.load(v);
   v.file().close();
 
   clone.writeParam(std::cout);
   clone.output(std::cout);
}

/*
* corrTime() must subtract the average, as autoCorrelation(t) does.
*/
void AutoCorrTest::testCorrTime()
{
   printMethod(TEST_FUNC);

   // Sample the values of in/data, shifted to an average near 10
   int i, n;
   double x;
   std::ifstream dataFile;
   openInputFile("in/data", dataFile);
   dataFile >> n;
   for (i = 0; i < n; ++i) {
      dataFile >> x;
      accumulator_.sample(x + 10.0);
   }
   dataFile.close();

   // Sum of C(t)/C(0) for 0 < t < capacity/2 (the buffer is full)
   double sum = 0.0;
   for (i = 1; i < accumulator_.bufferCapacity()/2; ++i) {
      sum += accumulator_.autoCorrelation(i);
   }
   sum /= accumulator_.autoCorrelation(0);

   TEST_ASSERT(std::abs(accumulator_.corrTime() - sum) < 1.0E-8);
}

/*
* After clear(), an AutoCorrelation must give the results of a new one.
*/
void AutoCorrTest::testAutoCorrelationClear()
{
   printMethod(TEST_FUNC);

   AutoCorrelation<double, double> used, fresh;
   used.setParam(8, 10, 2);
   fresh.setParam(8, 10, 2);

   // Sample enough values to create several descendant stages
   int i;
   for (i = 0; i < 1000; ++i) {
      used.sample(std::sin(0.3*double(i)));
   }
   used.clear();

   double x;
   for (i = 0; i < 64; ++i) {
      x = std::cos(0.7*double(i));
      used.sample(x);
      fresh.sample(x);
   }
   TEST_ASSERT(used.nSample() == fresh.nSample());
   TEST_ASSERT(used.maxDelay() == fresh.maxDelay());
   std::ostringstream usedOut, freshOut;
   used.output(usedOut);
   fresh.output(freshOut);
   TEST_ASSERT(usedOut.str() == freshOut.str());
}

/*
* Loading an AutoCorrelation from an archive must replace its stages.
*/
void AutoCorrTest::testAutoCorrelationLoad()
{
   printMethod(TEST_FUNC);

   // Save an AutoCorrelation with one value, and thus no child stage
   AutoCorrelation<double, double> source;
   source.setParam(8, 3, 2);
   source.sample(1.0);
   MemoryOArchive u;
   u.allocate(memorySize(source));
   u << source;

   // Load it into an AutoCorrelation with 4 stages
   AutoCorrelation<double, double> used;
   used.setParam(8, 3, 2);
   int i;
   for (i = 0; i < 1000; ++i) {
      used.sample(std::sin(0.3*double(i)));
   }
   MemoryIArchive v;
   v = u;
   v >> used;
   TEST_ASSERT(used.nSample() == 1);
   TEST_ASSERT(used.maxDelay() == source.maxDelay());

   // Sample more values
   double x;
   for (i = 0; i < 64; ++i) {
      x = std::cos(0.7*double(i));
      source.sample(x);
      used.sample(x);
   }
   TEST_ASSERT(used.maxDelay() == source.maxDelay());
   std::ostringstream usedOut, sourceOut;
   used.output(usedOut);
   source.output(sourceOut);
   TEST_ASSERT(usedOut.str() == sourceOut.str());
}

TEST_BEGIN(AutoCorrTest)
TEST_ADD(AutoCorrTest, testReadParam)
TEST_ADD(AutoCorrTest, testSample)
TEST_ADD(AutoCorrTest, testSerialize)
TEST_ADD(AutoCorrTest, testSerializeFile)
TEST_ADD(AutoCorrTest, testSaveLoad)
TEST_ADD(AutoCorrTest, testCorrTime)
TEST_ADD(AutoCorrTest, testAutoCorrelationClear)
TEST_ADD(AutoCorrTest, testAutoCorrelationLoad)
TEST_END(AutoCorrTest)

#endif
