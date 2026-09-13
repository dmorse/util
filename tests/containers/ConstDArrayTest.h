#ifndef UTIL_CONST_D_ARRAY_TEST_H
#define UTIL_CONST_D_ARRAY_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/containers/ConstDArray.h>
#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/MemoryCounter.h>
#include <util/archives/BinaryFileOArchive.h>
#include <util/archives/BinaryFileIArchive.h>

using namespace Util;

class ConstDArrayTest : public UnitTest
{
private:

   const static int capacity = 3;

   //typedef std::complex<double> Data;
   typedef double Data;

   int memory_;


public:

   void setUp()
   {  memory_ = (int) Memory::total(); }

   void tearDown() {}

   void testDefaultConstructor();
   void testAllocateConstructor();
   void testAllocate();
   void testReallocate();
   void testCopyConstructor();
   void testCopyConstructorCmplx();
   void testAssignment();
   void testAssignmentCmplx();
   void testIterator();
   void testBaseClassReference();
   void testSerialize1MemoryCmplx();
   void testSerialize2MemoryCmplx();
   void testSerialize1FileCmplx();
   void testSerialize2FileCmplx();

};


void ConstDArrayTest::testDefaultConstructor()
{
   printMethod(TEST_FUNC);
   {
      ConstDArray<Data> v;
      TEST_ASSERT(v.capacity() == 0 );
      TEST_ASSERT(!v.isAllocated() );
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testAllocateConstructor()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == 0);
   {
      ConstDArray<Data> v(capacity);

      // Allocate array
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT((int)Memory::total() == capacity*sizeof(Data));

      // Deallocate array
      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT((int)Memory::total() == memory_);

   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testAllocate()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == 0);
   {
      ConstDArray<Data> v;

      // Allocate array
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT((int)Memory::total() == capacity*sizeof(Data));

      // Deallocate array
      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT((int)Memory::total() == 0);

   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testReallocate()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT((int)Memory::total() == 0);
   {
      ConstDArray<Data> v;

      // Allocate array
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT((int)Memory::total() == capacity*sizeof(Data));

      // reallocate array
      v.reallocate(capacity+2);
      TEST_ASSERT(v.capacity() == capacity +2);
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT((int)Memory::total() == (capacity + 2)*sizeof(Data));

      // Deallocate array
      v.deallocate();
      TEST_ASSERT(v.capacity() == 0);
      TEST_ASSERT(!v.isAllocated());
      TEST_ASSERT((int)Memory::total() == 0);

   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testCopyConstructor()
{
   printMethod(TEST_FUNC);
   {
      DArray< Data > v;
      TEST_ASSERT(v.capacity() == 0 );
      TEST_ASSERT(!v.isAllocated() );

      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated() );
      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0;
      }

      ConstDArray< Data > u(v);
      TEST_ASSERT(u.capacity() == capacity);
      TEST_ASSERT(u.isAllocated() );
      TEST_ASSERT(v[0] == 10.0 );
      TEST_ASSERT(v[2] == 30.0 );
      TEST_ASSERT(u[0] == 10.0 );
      TEST_ASSERT(u[2] == 30.0 );
      TEST_ASSERT((int)Memory::total() == 2*capacity*sizeof(Data));
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testCopyConstructorCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > v;
      TEST_ASSERT(v.capacity() == 0 );
      TEST_ASSERT(!v.isAllocated() );

      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated() );
      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }

      ConstDArray< std::complex<Data> > u(v);
      TEST_ASSERT(u.capacity() == capacity);
      TEST_ASSERT(u.isAllocated() );
      TEST_ASSERT(real(v[0]) == 10.0 );
      TEST_ASSERT(imag(v[1]) == 20.1 );
      TEST_ASSERT(real(v[2]) == 30.0 );
      TEST_ASSERT(real(u[0]) == 10.0 );
      TEST_ASSERT(imag(u[1]) == 20.1 );
      TEST_ASSERT(real(u[2]) == 30 );
      TEST_ASSERT((int)Memory::total() == 2*capacity*sizeof(std::complex<Data>));
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testAssignment()
{
   printMethod(TEST_FUNC);

   {
      DArray<Data> v;
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == 3 );
      TEST_ASSERT(v.isAllocated() );

      ConstDArray<Data> u;
      u.allocate(3);
      TEST_ASSERT(u.capacity() == 3 );
      TEST_ASSERT(u.isAllocated() );

      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10;
      }

      u  = v;

      TEST_ASSERT(u.capacity() == 3 );
      TEST_ASSERT(u.isAllocated() );
      TEST_ASSERT(v[0] == 10.0);
      TEST_ASSERT(v[2] == 30.0);
      TEST_ASSERT(u[0] == 10.0);
      TEST_ASSERT(u[2] == 30.0);
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testAssignmentCmplx()
{
   printMethod(TEST_FUNC);

   {
      DArray< std::complex<Data> > v;
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == 3);
      TEST_ASSERT(v.isAllocated());

      ConstDArray< std::complex<Data> > u;
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
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testIterator()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT((int)Memory::total() == 0);
   {
      DArray<Data> u;
      u.allocate(capacity);
      for (int i=0; i < capacity; i++ ) {
         u[i] = (i+1)*10.0;
      }
      ConstDArray<Data> v(u);

      ConstArrayIterator<Data> it;
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
      TEST_ASSERT((int)Memory::total() == 2*capacity*sizeof(Data));
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testBaseClassReference()
{
   printMethod(TEST_FUNC);
   {
      DArray<Data> v;
      v.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0;
      }
      ConstDArray<Data> w(v);

      ConstArray<Data>& u = w;
      TEST_ASSERT(u[0] == 10.0);
      TEST_ASSERT(u[2] == 30.0);
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testSerialize1MemoryCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > w;
      w.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         w[i].real((i+1)*10.0);
         w[i].imag((i+1)*10.0 + 0.1);
      }
      int size = memorySize(w);
      ConstDArray< std::complex<Data> > v(w);

      int i1 = 13;
      int i2;

      MemoryOArchive oArchive;
      oArchive.allocate(size + 12);

      oArchive << v;
      TEST_ASSERT(oArchive.cursor() == oArchive.begin() + size);
      oArchive << i1;

      // Show that v is unchanged by packing
      TEST_ASSERT(imag(v[0])==10.1);
      TEST_ASSERT(real(v[1])==20.0);
      TEST_ASSERT(imag(v[2])==30.1);
      TEST_ASSERT(v.capacity() == 3);

      ConstDArray< std::complex<Data> > u;
      u.allocate(3);

      MemoryIArchive iArchive;
      iArchive = oArchive;
      TEST_ASSERT(iArchive.begin()  == oArchive.begin());
      TEST_ASSERT(iArchive.cursor() == iArchive.begin());

      // Load into u and i2
      iArchive >> u;
      TEST_ASSERT(iArchive.begin() == oArchive.begin());
      TEST_ASSERT(iArchive.end() == oArchive.cursor());
      TEST_ASSERT(iArchive.cursor() == iArchive.begin() + size);

      iArchive >> i2;
      TEST_ASSERT(iArchive.cursor() == iArchive.end());
      TEST_ASSERT(iArchive.begin() == oArchive.begin());
      TEST_ASSERT(iArchive.end() == oArchive.cursor());

      TEST_ASSERT(u[0].imag() == 10.1);
      TEST_ASSERT(u[1].real() == 20.0);
      TEST_ASSERT(u[2].imag() == 30.1);
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);

      // Release
      iArchive.release();
      TEST_ASSERT(!iArchive.isAllocated());
      TEST_ASSERT(iArchive.begin() == 0);
      TEST_ASSERT(iArchive.cursor() == 0);
      TEST_ASSERT(iArchive.end() == 0);
      TEST_ASSERT(oArchive.cursor() == oArchive.begin() + size + sizeof(int));

      // Clear values of u and i2
      for (int i=0; i < capacity; i++ ) {
         w[i].real(0.0);
         w[i].imag(0.0);
      }
      u = w;
      i2 = 0;

      // Reload into u and i2
      iArchive = oArchive;
      iArchive >> u;
      TEST_ASSERT(iArchive.begin() == oArchive.begin());
      TEST_ASSERT(iArchive.end() == oArchive.cursor());
      TEST_ASSERT(iArchive.cursor() == iArchive.begin() + size);

      iArchive >> i2;
      TEST_ASSERT(iArchive.cursor() == iArchive.end());
      TEST_ASSERT(iArchive.begin() == oArchive.begin());
      TEST_ASSERT(iArchive.end() == oArchive.cursor());

      TEST_ASSERT(imag(u[0]) == 10.1);
      TEST_ASSERT(real(u[1]) == 20.0);
      TEST_ASSERT(imag(u[2]) == 30.1);
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);
   }
   TEST_ASSERT((int)Memory::total() == memory_);

}

void ConstDArrayTest::testSerialize2MemoryCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > w;
      w.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         w[i].real((i+1)*10.0);
         w[i].imag((i+1)*10.0 + 0.1);
      }
      int size = memorySize(w);
      ConstDArray< std::complex<Data> > v(w);

      MemoryOArchive oArchive;
      oArchive.allocate(size);

      oArchive << v;
      TEST_ASSERT(oArchive.cursor() == oArchive.begin() + size);

      // Show that v is unchanged by packing
      TEST_ASSERT(v[0].imag()==10.1);
      TEST_ASSERT(v[1].real()==20.0);
      TEST_ASSERT(v[2].imag()==30.1);
      TEST_ASSERT(v.capacity() == capacity);

      ConstDArray< std::complex<Data> > u;

      // Note: We do not allocate ConstDArray<Data> u in this test.
      // This is the main difference from testSerialize1MemoryCmplx()

      MemoryIArchive iArchive;

      iArchive = oArchive;

      TEST_ASSERT(iArchive.begin()  == oArchive.begin());
      TEST_ASSERT(iArchive.cursor() == iArchive.begin());

      iArchive >> u;

      TEST_ASSERT(iArchive.cursor() == iArchive.begin() + size);
      TEST_ASSERT(imag(u[0]) == 10.1);
      TEST_ASSERT(real(u[1]) == 20.0);
      TEST_ASSERT(imag(u[2]) == 30.1);
      TEST_ASSERT(u.capacity() == 3);
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testSerialize1FileCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > w;
      w.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         w[i].real((i+1)*10.0);
         w[i].imag((i+1)*10.0 + 0.1);
      }
      ConstDArray< std::complex<Data> > v(w);
      //int size = memorySize(v);

      int i1 = 13;
      int i2;

      BinaryFileOArchive oArchive;
      openOutputFile("tmp/ConstDArray_binary", oArchive.file());
      oArchive << v;
      oArchive << i1;
      oArchive.file().close();

      // Show that v is unchanged by packing
      TEST_ASSERT(v[0].imag()==10.1);
      TEST_ASSERT(v[1].real()==20.0);
      TEST_ASSERT(v[2].imag()==30.1);
      TEST_ASSERT(v.capacity() == 3);

      ConstDArray< std::complex<Data> > u;
      u.allocate(3);

      BinaryFileIArchive iArchive;
      openInputFile("tmp/ConstDArray_binary", iArchive.file());
      iArchive >> u;
      iArchive >> i2;
      iArchive.file().close();

      TEST_ASSERT(u[0].imag() == 10.1);
      TEST_ASSERT(u[1].real() == 20.0);
      TEST_ASSERT(u[2].imag() == 30.1);
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);

      // Clear values of u and i2
      for (int i=0; i < capacity; i++ ) {
         w[i].real(0.0);
         w[i].imag(0.0);
      }
      u = w;
      i2 = 0;

      // Reload into u and i2
      openInputFile("tmp/ConstDArray_binary", iArchive.file());
      iArchive >> u;
      iArchive >> i2;

      TEST_ASSERT(u[0].imag() == 10.1);
      TEST_ASSERT(u[1].real() == 20.0);
      TEST_ASSERT(u[2].imag() == 30.1);
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

void ConstDArrayTest::testSerialize2FileCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > w;
      w.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         w[i].real((i+1)*10.0);
         w[i].imag((i+1)*10.0 + 0.1);
      }
      ConstDArray< std::complex<Data> > v(w);

      int i1 = 13;
      int i2;

      BinaryFileOArchive oArchive;
      openOutputFile("tmp/binary", oArchive.file());
      oArchive << v;
      oArchive << i1;
      oArchive.file().close();

      // Show that v is unchanged by packing
      TEST_ASSERT(v[0].imag() == 10.1);
      TEST_ASSERT(v[1].real() == 20.0);
      TEST_ASSERT(v[2].imag() == 30.1);
      TEST_ASSERT(v.capacity() == 3);

      ConstDArray< std::complex<Data> > u;

      // u.allocate(3); ->
      // Note: We do not allocate first. This is the difference
      // from the previous test

      BinaryFileIArchive iArchive;
      openInputFile("tmp/binary", iArchive.file());
      iArchive >> u;
      iArchive >> i2;
      iArchive.file().close();

      TEST_ASSERT(eq(u[0].imag(), 10.1));
      TEST_ASSERT(eq(u[1].real(), 20.0));
      TEST_ASSERT(eq(u[2].imag(), 30.1));
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);

      // Clear values of u and i2
      for (int i=0; i < capacity; i++ ) {
         w[i].real(0.0);
         w[i].imag(0.0);
      }
      u = w;
      i2 = 0;

      // Reload into u and i2
      openInputFile("tmp/binary", iArchive.file());
      iArchive >> u;
      iArchive >> i2;

      TEST_ASSERT(eq(u[0].imag(), 10.1));
      TEST_ASSERT(eq(u[1].real(), 20.0));
      TEST_ASSERT(eq(u[2].imag(), 30.1));
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);
   }
   TEST_ASSERT((int)Memory::total() == memory_);
}

TEST_BEGIN(ConstDArrayTest)
TEST_ADD(ConstDArrayTest, testDefaultConstructor)
TEST_ADD(ConstDArrayTest, testAllocateConstructor)
TEST_ADD(ConstDArrayTest, testAllocate)
TEST_ADD(ConstDArrayTest, testReallocate)
TEST_ADD(ConstDArrayTest, testCopyConstructor)
TEST_ADD(ConstDArrayTest, testCopyConstructorCmplx)
TEST_ADD(ConstDArrayTest, testAssignment)
TEST_ADD(ConstDArrayTest, testAssignmentCmplx)
TEST_ADD(ConstDArrayTest, testIterator)
TEST_ADD(ConstDArrayTest, testBaseClassReference)
TEST_ADD(ConstDArrayTest, testSerialize1MemoryCmplx)
TEST_ADD(ConstDArrayTest, testSerialize2MemoryCmplx)
TEST_ADD(ConstDArrayTest, testSerialize1FileCmplx)
TEST_ADD(ConstDArrayTest, testSerialize2FileCmplx)
TEST_END(ConstDArrayTest)

#endif
