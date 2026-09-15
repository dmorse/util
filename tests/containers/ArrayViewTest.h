#ifndef UTIL_ARRAY_VIEW_TEST_H
#define UTIL_ARRAY_VIEW_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/containers/DRArray.h>
#include <util/containers/ConstArrayView.h>
#include <util/containers/ArrayView.h>
using namespace Util;

class ArrayViewTest : public UnitTest
{
private:

   const static int capacity = 3;

   typedef double Data;

   long int memory_;

public:

   void setUp()
   {  memory_ = Memory::total(); }

   void tearDown() {}

   void testConstArrayView();
   void testArrayView();
};

void ArrayViewTest::testConstArrayView()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == memory_);
   {
      // Array source/owner (DRArray)
      DRArray<Data> v(capacity);
      TEST_ASSERT(v.capacity() == capacity);

      // Array view (const)
      ConstArrayView<Data> u;
      TEST_ASSERT(!u.isAssociated());
      TEST_ASSERT(u.size() == 0);
      u.associate(v, 1, capacity - 1);
      TEST_ASSERT(u.isAssociated());
      TEST_ASSERT(u.size() == capacity - 1);

      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0 ;
      }

      TEST_ASSERT(eq(u[0], 20.0));
      TEST_ASSERT(eq(u[1], 30.0));
      long int tot = Memory::total();
      TEST_ASSERT(tot == (long int)(memory_ + capacity*sizeof(Data)));

      //v.deallocate(); // Intentional error

      u.dissociate();
      TEST_ASSERT(u.size() == 0);
      TEST_ASSERT(!u.isAssociated());
      TEST_ASSERT(u.size() == 0);

      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT(!v.isAssociated());
      TEST_ASSERT(!v.isOwner());

   }
   TEST_ASSERT(Memory::total() == memory_);
}

void ArrayViewTest::testArrayView()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == memory_);
   {
      // Data owner 1 (DRArray)
      DRArray<Data> v(capacity);
      TEST_ASSERT(v.capacity() == capacity);

      // Array view (non-const)
      ArrayView<Data> u;
      TEST_ASSERT(!u.isAssociated());
      TEST_ASSERT(u.size() == 0);
      u.associate(v, 1, capacity - 1);
      TEST_ASSERT(u.size() == capacity - 1);
      TEST_ASSERT(u.isAssociated());

      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0 ;
      }

      TEST_ASSERT(eq(u[0], 20.0));
      TEST_ASSERT(eq(u[1], 30.0));
      long int tot = Memory::total();
      TEST_ASSERT(tot == (long int)(memory_ + capacity*sizeof(Data)));

      u[1] = 25.0;
      TEST_ASSERT(eq(u[1], 25.0));
      TEST_ASSERT(eq(v[2], 25.0));

      //v.deallocate(); // Intentional error

      u.dissociate();
      TEST_ASSERT(!u.isAssociated());
      TEST_ASSERT(u.size() == 0);

      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT(!v.isAssociated());
      TEST_ASSERT(!v.isOwner());

   }
   TEST_ASSERT(Memory::total() == memory_);
}

TEST_BEGIN(ArrayViewTest)
TEST_ADD(ArrayViewTest, testConstArrayView)
TEST_ADD(ArrayViewTest, testArrayView)
TEST_END(ArrayViewTest)

#endif
