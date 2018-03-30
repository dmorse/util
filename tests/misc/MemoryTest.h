#ifndef MEMORY_TEST_H
#define MEMORY_TEST_H

#include <util/misc/Memory.h>
#include <util/global.h>

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

using namespace Util;

class MemoryTest : public UnitTest 
{

   int mem0_;

public:

   void setUp()
   {  mem0_ = Memory::total(); };

   void tearDown()
   {};

   void testAllocate() 
   {
      printMethod(TEST_FUNC);

      double* ptr = 0;
      int n = 100;
      Memory::allocate(ptr, n);
      for (int i = 0; i < n; ++i) {
         ptr[i] = 0.1 + (double)(i);
      }
      TEST_ASSERT(Memory::total() == mem0_ + n*sizeof(double));
      for (int i = 0; i < n; ++i) {
         TEST_ASSERT(eq(ptr[i], double(i) + 0.1));
      }
      Memory::deallocate(ptr, n);
      TEST_ASSERT(Memory::total() == mem0_);
   }

   void testReallocate() 
   {
      printMethod(TEST_FUNC);

      double* ptr = 0;
      int n = 100;
      Memory::allocate(ptr, n);
      for (int i = 0; i < n; ++i) {
         ptr[i] = 0.1 + (double)(i);
      }
      TEST_ASSERT(Memory::total() == mem0_ + n*sizeof(double));
      double* old = ptr;
      int m = n + 20;
      Memory::reallocate(ptr, n, m);
      for (int i = 0; i < n; ++i) {
         TEST_ASSERT(eq(ptr[i], double(i) + 0.1));
      }
      TEST_ASSERT(old != ptr); 
      TEST_ASSERT(Memory::total() == mem0_ + m*sizeof(double));
      Memory::deallocate(ptr, m);
      TEST_ASSERT(Memory::total() == mem0_);
   }

};

TEST_BEGIN(MemoryTest)
TEST_ADD(MemoryTest, testAllocate)
TEST_ADD(MemoryTest, testReallocate)
TEST_END(MemoryTest)

#endif
