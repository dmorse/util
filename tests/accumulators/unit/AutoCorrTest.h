#ifndef AUTOCORR_TEST_H
#define AUTOCORR_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/accumulators/AutoCorr.h>
#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/MemoryCounter.h>
#include <util/archives/BinaryFileIArchive.h>
#include <util/archives/BinaryFileOArchive.h>

#include <iostream>
#include <fstream>
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

TEST_BEGIN(AutoCorrTest)
TEST_ADD(AutoCorrTest, testReadParam)
TEST_ADD(AutoCorrTest, testSample)
TEST_ADD(AutoCorrTest, testSerialize)
TEST_ADD(AutoCorrTest, testSerializeFile)
TEST_ADD(AutoCorrTest, testSaveLoad)
TEST_ADD(AutoCorrTest, testCorrTime)
TEST_END(AutoCorrTest)

#endif
