#ifndef MEMORY_TEST_H
#define MEMORY_TEST_H

#include <util/misc/Memory.h>
#include <util/global.h>

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

using namespace Util;

class MemoryTest : public UnitTest 
{

public:

   void setUp()
   {};

   void tearDown()
   {};

   void testAllocate() 
   {
      printMethod(TEST_FUNC);

      double* ptr = 0;
      int n = 100;
      TEST_ASSERT(Memory::total() == 0);
      Memory::allocate(ptr, n);
      for (int i = 0; i < n; ++i) {
         ptr[i] = 0.1 + (double)(i);
      }
      TEST_ASSERT(Memory::total() == n*sizeof(double));
      for (int i = 0; i < n; ++i) {
         TEST_ASSERT(eq(ptr[i], double(i) + 0.1));
      }
      Memory::deallocate(ptr, n);
      TEST_ASSERT(Memory::total() == 0);
   }

   void testReallocate() 
   {
      printMethod(TEST_FUNC);

      double* ptr = 0;
      int n = 100;
      TEST_ASSERT(Memory::total() == 0);
      Memory::allocate(ptr, n);
      for (int i = 0; i < n; ++i) {
         ptr[i] = 0.1 + (double)(i);
      }
      TEST_ASSERT(Memory::total() == n*sizeof(double));
      double* old = ptr;
      Memory::reallocate(ptr, n, n + 20);
      for (int i = 0; i < n; ++i) {
         TEST_ASSERT(eq(ptr[i], double(i) + 0.1));
      }
      TEST_ASSERT(old != ptr); 
      TEST_ASSERT(Memory::total() == (n+20)*sizeof(double));
      Memory::deallocate(ptr, n+20);
      TEST_ASSERT(Memory::total() == 0);
   }

};

TEST_BEGIN(MemoryTest)
TEST_ADD(MemoryTest, testAllocate)
TEST_ADD(MemoryTest, testReallocate)
TEST_END(MemoryTest)

#endif
