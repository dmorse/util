#ifndef AUTOCORR_ARRAY_TEST_H
#define AUTOCORR_ARRAY_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/accumulators/AutoCorrArray.h>
#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/MemoryCounter.h>
#include <util/archives/BinaryFileIArchive.h>
#include <util/archives/BinaryFileOArchive.h>

#include <iostream>
#include <fstream>
#include <sstream>

using namespace Util;

class AutoCorrArrayTest : public UnitTest
{

   AutoCorrArray<double, double> accumulator_;

public:

   AutoCorrArrayTest();
   ~AutoCorrArrayTest();

   void setUp();
   void tearDown();

   void readData();
   void testReadParam();
   void testSample();
   void testSerialize();
   void testSerializeFile() ;
   void testSaveLoad();
   void testSetNEnsemble();

};

AutoCorrArrayTest::AutoCorrArrayTest()
{}

AutoCorrArrayTest::~AutoCorrArrayTest()
{}

void AutoCorrArrayTest::setUp() 
{ 
   std::ifstream paramFile;
   openInputFile("in/AutoCorrArray", paramFile); 
   accumulator_.readParam(paramFile);
   paramFile.close();
   accumulator_.setNEnsemble(4);
}

void AutoCorrArrayTest::tearDown() 
{}

void AutoCorrArrayTest::readData() 
{
   DArray<double> data;
   int i, j, m, n, p;

   std::ifstream dataFile;
   openInputFile("in/data", dataFile); 
   dataFile >> m;
   n = accumulator_.nEnsemble();
   data.allocate(n);
   p = m / n;
   for (i = 0; i < p; ++i) {
      for (j = 0; j < n; ++j) {
        dataFile >> data[j];
      }
      accumulator_.sample(data);
   }
   dataFile.close();
}

void AutoCorrArrayTest::testReadParam() 
{
   printMethod(TEST_FUNC);

   printEndl();
   accumulator_.writeParam(std::cout);
}

void AutoCorrArrayTest::testSample() 
{
   printMethod(TEST_FUNC);

   readData();

   printEndl();
   accumulator_.output(std::cout);
}

void AutoCorrArrayTest::testSerialize() 
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

   AutoCorrArray<double, double> clone;
   v & clone;

   clone.output(std::cout);
}

void AutoCorrArrayTest::testSerializeFile() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   BinaryFileOArchive u;
   openOutputFile("tmp/AutoCorrArrayTestSerializeFile", u.file());
   u << accumulator_;
   u.file().close();

   AutoCorrArray<double, double> clone;
   BinaryFileIArchive v;
   openInputFile("tmp/AutoCorrArrayTestSerializeFile", v.file());
   v >> clone;
   v.file().close();
   
   clone.output(std::cout);
}

void AutoCorrArrayTest::testSaveLoad() 
{
   printMethod(TEST_FUNC);
   printEndl();

   readData();

   BinaryFileOArchive u;
   openOutputFile("tmp/AutoCorrArrayTestSaveLoad", u.file());
   accumulator_.save(u);
   u.file().close();

   AutoCorrArray<double, double> clone;
   BinaryFileIArchive v;
   openInputFile("tmp/AutoCorrArrayTestSaveLoad", v.file());
   clone.load(v);
   v.file().close();
 
   clone.writeParam(std::cout);
   clone.output(std::cout);
}

/*
* A change of nEnsemble must clear the accumulator.
*/
void AutoCorrArrayTest::testSetNEnsemble()
{
   printMethod(TEST_FUNC);

   DArray<double> data;
   data.allocate(4);
   int i, j;

   // Sample 3 values of 4 sequences, then 2 values of 2 sequences
   for (j = 0; j < 4; ++j) {
      data[j] = 10.0;
   }
   for (i = 0; i < 3; ++i) {
      accumulator_.sample(data);
   }
   accumulator_.setNEnsemble(2);
   for (j = 0; j < 4; ++j) {
      data[j] = 1.0;
   }
   for (i = 0; i < 2; ++i) {
      accumulator_.sample(data);
   }
   TEST_ASSERT(accumulator_.nSample() == 2);
   TEST_ASSERT(accumulator_.average() == 1.0);

   // Return to 4 sequences: results as for a new accumulator
   accumulator_.setNEnsemble(4);
   AutoCorrArray<double, double> fresh;
   fresh.setParam(4, 25);
   for (i = 0; i < 5; ++i) {
      for (j = 0; j < 4; ++j) {
         data[j] = double(i + j);
      }
      accumulator_.sample(data);
      fresh.sample(data);
   }
   std::ostringstream out, freshOut;
   accumulator_.output(out);
   fresh.output(freshOut);
   TEST_ASSERT(out.str() == freshOut.str());
}

TEST_BEGIN(AutoCorrArrayTest)
TEST_ADD(AutoCorrArrayTest, testReadParam)
TEST_ADD(AutoCorrArrayTest, testSample)
TEST_ADD(AutoCorrArrayTest, testSerialize)
TEST_ADD(AutoCorrArrayTest, testSerializeFile)
TEST_ADD(AutoCorrArrayTest, testSaveLoad)
TEST_ADD(AutoCorrArrayTest, testSetNEnsemble)
TEST_END(AutoCorrArrayTest)

#endif
