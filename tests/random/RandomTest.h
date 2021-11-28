#ifndef RANDOM_TEST_H
#define RANDOM_TEST_H

#include <util/random/Random.h>
#include <util/archives/BinaryFileOArchive.h>
#include <util/archives/BinaryFileIArchive.h>

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <fstream>

using namespace Util;

class RandomTest : public UnitTest {

private:

   Random *random;

public:

   void setUp()
   {
      random  = new Random;
      setVerbose(0);
   };


   void tearDown()
   {
      delete random;
   };


   void testReadParam() 
   {

      printMethod(TEST_FUNC);

      std::ifstream in;
      openInputFile("in/Random", in);
      if (ParamComponent::echo()) printEndl();
      random->readParam(in);

      // Verbose output
      if (verbose() > 0) {
         printEndl();
         printf("seed: %ld\n", random->seed());
      }

   }


   void testGetFloat() 
   {
      printMethod(TEST_FUNC);

      const int max  = 1000;
      const int nbin = 10;
      int  histogram[nbin];
      int  i, j;
      double x;

      std::ifstream in;
      openInputFile("in/Random", in);
      if (ParamComponent::echo()) printEndl();
      random->readParam(in);

      for (i=0; i < nbin; i++) {
         histogram[i] = 0;
      }

      for (i=0; i < max; i++) {
         x = random->uniform(0.0,1.0);
         j = int(x*nbin);
         histogram[j]++;
      }

      if (verbose() > 1) {
         printEndl();
         for (i=0; i < nbin; i++) {
            printf("%i  %i\n", i, histogram[i]);
         }
      }

   }

   void testGetInteger() 
   {
      const int nSample  = 10000;
      const int nbin     = 10;
      int  histogram[nbin+1];
      int  i;
      long x;

      printMethod(TEST_FUNC);

      for (i=0; i <= nbin; i++) {
         histogram[i] = 0;
      }

      std::ifstream in;
      openInputFile("in/Random", in);
      if (ParamComponent::echo()) printEndl();
      random->readParam(in);

      for (i=0; i < nSample; i++) {
         x = random->uniformInt(0, nbin);
         histogram[x]++;
         //printf("   %ld\n", x);
      }

      if (verbose() > 1) {
         printEndl();
         for (i=0; i <= nbin; i++) {
            printf("%i %i\n", i, histogram[i]);
         }
      }

   }


   void testGaussian() 
   {
      int i, max;
      double x;

      printMethod(TEST_FUNC);
      if (verbose() > 1) printEndl();

      std::ifstream in;
      openInputFile("in/Random", in);
      if (ParamComponent::echo()) printEndl();
      random->readParam(in);

      max = 100;
      for (i=0; i < max; i++) {
         x = random->gaussian();
         if (verbose() > 1) {
            std::cout << x << std::endl;
         }
      }
   }


   void testUnitVector() {
      int    i, max;
      double vsq;
      Vector v;

      printMethod(TEST_FUNC);

      std::ifstream in;
      openInputFile("in/Random", in);
      if (ParamComponent::echo()) printEndl();
      random->readParam(in);

      max = 100;
      for (i=0; i < max; i++) {
         random->unitVector(v);
         vsq = v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
         if (verbose() > 1) {
            std::cout << v << "  " << vsq << std::endl;
         }
      }

   }

   void testBinarySerialize() {
      printMethod(TEST_FUNC);

      // Read parameters from file
      std::ifstream in;
      openInputFile("in/Random", in);
      if (ParamComponent::echo()) printEndl();
      random->readParam(in);

      // Pull 20 random numbers to change state
      for (int i=0; i < 20; i++) {
         random->uniformInt(0, 255);
      }

      // Write Random object to file
      BinaryFileOArchive oar;
      openOutputFile("out/binary", oar.file());
      oar << *random;
      oar.file().close();

      // Extract 3 integers after writing to file
      int a = random->uniformInt(0,255);
      int b = random->uniformInt(0,255);
      int c = random->uniformInt(0,255);

      if (verbose() > 1) {
         printEndl();
         std::cout << a << std::endl;
         std::cout << b << std::endl;
         std::cout << c << std::endl;
      }

      // Read new Random object from input file archive
      BinaryFileIArchive iar;
      openInputFile("out/binary", iar.file());
      Random* ranPtr = new Random;
      iar >> *ranPtr;
      iar.file().close();

      // Extract 3 integers after reading from file, and compare
      TEST_ASSERT(ranPtr->uniformInt(0,255) == a);
      TEST_ASSERT(ranPtr->uniformInt(0,255) == b);
      TEST_ASSERT(ranPtr->uniformInt(0,255) == c);

      delete ranPtr;
  
   }

};

TEST_BEGIN(RandomTest)
TEST_ADD(RandomTest, testReadParam)
TEST_ADD(RandomTest, testGetFloat)
TEST_ADD(RandomTest, testGetInteger)
TEST_ADD(RandomTest, testGaussian)
TEST_ADD(RandomTest, testUnitVector)
TEST_ADD(RandomTest, testBinarySerialize)
TEST_END(RandomTest)


#endif
