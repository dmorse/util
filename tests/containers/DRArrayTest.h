#ifndef UTIL_DRARRAY_TEST_H
#define UTIL_DRARRAY_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/containers/DRArray.h>
using namespace Util;

class DRArrayTest : public UnitTest
{
private:

   const static int capacity = 3;

   typedef double Data;

   int memory_;

public:

   void setUp()
   {  memory_ = Memory::total(); }

   void tearDown() {}
   void testDefaultConstructor();
   void testAllocateConstructor();
   void testAllocate();
   void testSubscript();
   void testSubscriptCmplx();
   void testAssociate();
   void testIterator();
   void testCopyConstructor();
   void testCopyConstructorCmplx();
   void testAssignment();
   void testAssignmentCmplx();
   void testBaseClassReference();
};


void DRArrayTest::testDefaultConstructor()
{
   printMethod(TEST_FUNC);
   {
      DRArray<Data> v;
      TEST_ASSERT(v.capacity() == 0 );
      TEST_ASSERT(!v.isAllocated() );
      TEST_ASSERT(!v.isOwner());
      TEST_ASSERT(!v.isAssociated());
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testAllocateConstructor()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == 0);
   {
      DRArray<Data> v(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT(v.isOwner());
      TEST_ASSERT(!v.isAssociated());
      TEST_ASSERT((int)Memory::total() == memory_ + capacity*sizeof(Data));

      // Deallocate array
      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT((int)Memory::total() == memory_);

   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testAllocate()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == 0);
   {
      DRArray<Data> v;

      // Allocate array
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT(v.isOwner());
      TEST_ASSERT(!v.isAssociated());
      TEST_ASSERT((int)Memory::total() == memory_ + capacity*sizeof(Data));

      // Deallocate array
      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT((int)Memory::total() == memory_);

   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testSubscript()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == memory_);
   {
      DRArray<Data> v(capacity);
      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0 ;
      }

      TEST_ASSERT(v[0] == 10.0);
      TEST_ASSERT(v[1] == 20.0);
      TEST_ASSERT(v[2] == 30.0);
      TEST_ASSERT((int)Memory::total() == memory_ + capacity*sizeof(Data));
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testAssociate()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == memory_);
   DRArray<Data> u;
   {
      // Data owner
      DRArray<Data> v(capacity);
      TEST_ASSERT(v.capacity() == capacity);

      // Data user
      u.associate(v, 1, capacity - 1);
      TEST_ASSERT(u.capacity() == capacity - 1);
      TEST_ASSERT(u.isAllocated());
      TEST_ASSERT(u.isAssociated());
      TEST_ASSERT(!u.isOwner());

      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0 ;
      }

      TEST_ASSERT(eq(v[0], 10.0));
      TEST_ASSERT(eq(v[1], 20.0));
      TEST_ASSERT(eq(v[2], 30.0));
      TEST_ASSERT(eq(u[0], 20.0));
      TEST_ASSERT(eq(u[1], 30.0));
      u[1] = 25.0;
      TEST_ASSERT(eq(v[1], 20.0));
      TEST_ASSERT(eq(v[2], 25.0));
      TEST_ASSERT((int)Memory::total() == memory_ + capacity*sizeof(Data));

      // v.deallocate(); // Intentional error

      u.dissociate();
      TEST_ASSERT(u.capacity() == 0);
      TEST_ASSERT(!u.isAllocated());
      TEST_ASSERT(!u.isAssociated());
      TEST_ASSERT(!u.isOwner());

      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT(!v.isAssociated());
      TEST_ASSERT(!v.isOwner());

   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testSubscriptCmplx()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == memory_);
   {
      DRArray< std::complex<Data> > v;
      v.allocate(capacity);
      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }

      TEST_ASSERT(eq(v[0].real(), 10.0));
      TEST_ASSERT(eq(v[1].imag(), 20.1));
      TEST_ASSERT(eq(v[2].real(), 30.0));
      TEST_ASSERT((int)Memory::total() == capacity*sizeof(std::complex<Data>));
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testCopyConstructor()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == memory_);
   {
      // Data owner
      DRArray<Data> v(capacity);
      TEST_ASSERT(v.capacity() == capacity);
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT(v.isOwner());
      TEST_ASSERT(!v.isAssociated());
      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0 ;
      }
      TEST_ASSERT((int)Memory::total() == memory_ + capacity*sizeof(Data));

      DRArray<Data> u(v);
      TEST_ASSERT(u.capacity() == capacity);
      TEST_ASSERT(u.isAllocated());
      TEST_ASSERT(u.isOwner());
      TEST_ASSERT(!u.isAssociated());

      TEST_ASSERT(eq(v[0], 10.0));
      TEST_ASSERT(eq(v[1], 20.0));
      TEST_ASSERT(eq(v[2], 30.0));
      TEST_ASSERT(eq(u[0], 10.0));
      TEST_ASSERT(eq(u[1], 20.0));
      TEST_ASSERT(eq(u[2], 30.0));
      u[1] = 25.0;
      TEST_ASSERT(eq(u[1], 25.0));
      TEST_ASSERT(eq(v[1], 20.0));
      TEST_ASSERT((int)Memory::total() == memory_ + 2*capacity*sizeof(Data));

      u.deallocate();
      TEST_ASSERT((int)Memory::total() == memory_ + capacity*sizeof(Data));
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testCopyConstructorCmplx()
{
   printMethod(TEST_FUNC);
   {
      DRArray< std::complex<Data> > v;
      TEST_ASSERT(v.capacity() == 0 );
      TEST_ASSERT(!v.isAllocated() );

      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated() );
      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }

      DRArray< std::complex<Data> > u(v);
      TEST_ASSERT(u.capacity() == capacity);
      TEST_ASSERT(u.isAllocated() );
      TEST_ASSERT(u.isOwner());
      TEST_ASSERT(!u.isAssociated());
      TEST_ASSERT(real(v[0]) == 10.0 );
      TEST_ASSERT(imag(v[1]) == 20.1 );
      TEST_ASSERT(real(v[2]) == 30.0 );
      TEST_ASSERT(real(u[0]) == 10.0 );
      TEST_ASSERT(imag(u[1]) == 20.1 );
      TEST_ASSERT(real(u[2]) == 30 );
      TEST_ASSERT((int)Memory::total() == 2*capacity*sizeof(std::complex<Data>));
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testAssignment()
{
   printMethod(TEST_FUNC);

   {
      DRArray<Data> v;
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == 3 );
      TEST_ASSERT(v.isAllocated() );
      TEST_ASSERT(v.isOwner() );
      TEST_ASSERT(!v.isAssociated() );

      DRArray<Data> u;
      u.allocate(3);
      TEST_ASSERT(u.capacity() == 3 );
      TEST_ASSERT(u.isAllocated() );
      TEST_ASSERT(u.isOwner() );
      TEST_ASSERT(!u.isAssociated() );

      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10;
      }

      u = v;

      TEST_ASSERT(u.capacity() == 3 );
      TEST_ASSERT(u.isAllocated() );
      TEST_ASSERT(u.isOwner() );
      TEST_ASSERT(!u.isAssociated() );
      TEST_ASSERT(v[0] == 10.0);
      TEST_ASSERT(v[2] == 30.0);
      TEST_ASSERT(u[0] == 10.0);
      TEST_ASSERT(u[2] == 30.0);
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testAssignmentCmplx()
{
   printMethod(TEST_FUNC);

   {
      DRArray< std::complex<Data> > v;
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == 3);
      TEST_ASSERT(v.isAllocated());

      DRArray< std::complex<Data> > u;
      u.allocate(3);
      TEST_ASSERT(u.capacity() == 3 );
      TEST_ASSERT(u.isAllocated() );

      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }

      u  = v;

      TEST_ASSERT(u.capacity() == 3 );
      TEST_ASSERT(u.isAllocated() );
      TEST_ASSERT(real(v[0]) == 10.0);
      TEST_ASSERT(imag(v[1]) == 20.1);
      TEST_ASSERT(real(v[2]) == 30.0);
      TEST_ASSERT(real(u[0]) == 10.0);
      TEST_ASSERT(imag(u[1]) == 20.1);
      TEST_ASSERT(real(u[2]) == 30.0);
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testIterator()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT((int)Memory::total() == 0);
   {
      DRArray<Data> v;
      v.allocate(capacity);
      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0;
      }

      ArrayIterator<Data> it;
      v.begin(it);
      TEST_ASSERT(eq(*it, 10.0));
      TEST_ASSERT(!it.isEnd());
      TEST_ASSERT(it.notEnd());
      ++it;
      TEST_ASSERT(eq(*it, 20.0));
      TEST_ASSERT(!it.isEnd());
      TEST_ASSERT(it.notEnd());
      ++it;
      TEST_ASSERT(eq(*it, 30.0));
      ++it;
      TEST_ASSERT(it.isEnd());
      TEST_ASSERT(!it.notEnd());
      TEST_ASSERT((int)Memory::total() == capacity*sizeof(Data));
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DRArrayTest::testBaseClassReference()
{
   printMethod(TEST_FUNC);
   {
      DRArray<Data> v;
      v.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0;
      }

      Array<Data>& u = v;
      TEST_ASSERT(u[0] == 10.0);
      TEST_ASSERT(u[2] == 30.0);
   }
   TEST_ASSERT(Memory::total() == memory_);
}

TEST_BEGIN(DRArrayTest)
TEST_ADD(DRArrayTest, testDefaultConstructor)
TEST_ADD(DRArrayTest, testAllocateConstructor)
TEST_ADD(DRArrayTest, testAllocate)
TEST_ADD(DRArrayTest, testSubscript)
TEST_ADD(DRArrayTest, testSubscriptCmplx)
TEST_ADD(DRArrayTest, testAssociate)
TEST_ADD(DRArrayTest, testCopyConstructor)
TEST_ADD(DRArrayTest, testCopyConstructorCmplx)
TEST_ADD(DRArrayTest, testAssignment)
TEST_ADD(DRArrayTest, testAssignmentCmplx)
TEST_ADD(DRArrayTest, testIterator)
TEST_ADD(DRArrayTest, testBaseClassReference)
TEST_END(DRArrayTest)

#endif
