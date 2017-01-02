#ifndef UTIL_DARRAY_TEST_H
#define UTIL_DARRAY_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/containers/DArray.h>
#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/MemoryCounter.h>
#include <util/archives/BinaryFileOArchive.h>
#include <util/archives/BinaryFileIArchive.h>

using namespace Util;

class DArrayTest : public UnitTest 
{
private:

   const static int capacity = 3;

   //typedef std::complex<double> Data;
   typedef double Data;

   int memory_;


public:

   void setUp() 
   {  memory_ = Memory::total(); }

   void tearDown() {}
   void testConstructor();
   void testAllocate();
   void testSubscript();
   void testSubscriptCmplx();
   void testIterator();
   //void testCopyConstructor();
   void testCopyConstructorCmplx();
   void testAssignment();
   void testAssignmentCmplx();
   void testBaseClassReference();
   void testSerialize1MemoryCmplx();
   void testSerialize2MemoryCmplx();
   void testSerialize1FileCmplx();
   void testSerialize2FileCmplx();

};


void DArrayTest::testConstructor()
{
   printMethod(TEST_FUNC);
   {
      DArray<Data> v;
      TEST_ASSERT(v.capacity() == 0 );
      TEST_ASSERT(!v.isAllocated() );
   }
   TEST_ASSERT(Memory::total() == memory_);
} 

void DArrayTest::testAllocate()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == 0);
   {
      DArray<Data> v;
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == capacity );
      TEST_ASSERT(v.isAllocated());
      TEST_ASSERT((int)Memory::total() == capacity*sizeof(Data));
   }
   TEST_ASSERT(Memory::total() == memory_);
} 

void DArrayTest::testSubscript()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == 0);
   {
      DArray<Data> v;
      v.allocate(capacity);
      for (int i=0; i < capacity; i++ ) {
         v[i] = (i+1)*10.0 ;
      }
   
      TEST_ASSERT(v[0] == 10.0);
      TEST_ASSERT(v[2] == 30.0);
      TEST_ASSERT((int)Memory::total() == capacity*sizeof(Data));
   }
   TEST_ASSERT(Memory::total() == memory_);
} 

void DArrayTest::testSubscriptCmplx()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT(Memory::total() == 0);
   {
      DArray< std::complex<Data> > v;
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

void DArrayTest::testIterator()
{
   printMethod(TEST_FUNC);
   TEST_ASSERT((int)Memory::total() == 0);
   {
      DArray<Data> v;
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

void DArrayTest::testCopyConstructorCmplx()
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
   
      DArray< std::complex<Data> > u(v);
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
   TEST_ASSERT(Memory::total() == memory_);
} 

void DArrayTest::testAssignment()
{
   printMethod(TEST_FUNC);

   {
      DArray<Data> v;
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == 3 );
      TEST_ASSERT(v.isAllocated() );
   
      DArray<Data> u;
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
   TEST_ASSERT(Memory::total() == memory_);
} 

void DArrayTest::testAssignmentCmplx()
{
   printMethod(TEST_FUNC);

   {
      DArray< std::complex<Data> > v;
      v.allocate(capacity);
      TEST_ASSERT(v.capacity() == 3);
      TEST_ASSERT(v.isAllocated());
   
      DArray< std::complex<Data> > u;
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

void DArrayTest::testBaseClassReference()
{
   printMethod(TEST_FUNC);
   {
      DArray<Data> v;
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


void DArrayTest::testSerialize1MemoryCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > v;
      v.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }
      int size = memorySize(v);
     
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
   
      DArray< std::complex<Data> > u;
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
         u[i].real(0.0);
         u[i].imag(0.0);
      }
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
   TEST_ASSERT(Memory::total() == memory_);

}

void DArrayTest::testSerialize2MemoryCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > v;
      v.allocate(capacity);
      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }
      int size = memorySize(v);
     
      MemoryOArchive oArchive;
      oArchive.allocate(size);
   
      oArchive << v;
      TEST_ASSERT(oArchive.cursor() == oArchive.begin() + size);
   
      // Show that v is unchanged by packing
      TEST_ASSERT(v[0].imag()==10.1);
      TEST_ASSERT(v[1].real()==20.0);
      TEST_ASSERT(v[2].imag()==30.1);
      TEST_ASSERT(v.capacity() == capacity);
   
      DArray< std::complex<Data> > u;
   
      // Note: We do not allocate DArray<Data> u in this test.
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
   TEST_ASSERT(Memory::total() == memory_);
}

void DArrayTest::testSerialize1FileCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > v;
      v.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }
     
      int i1 = 13;
      int i2;

      BinaryFileOArchive oArchive;
      openOutputFile("binary", oArchive.file());
      oArchive << v;
      oArchive << i1;
      oArchive.file().close();
   
      // Show that v is unchanged by packing
      TEST_ASSERT(v[0].imag()==10.1);
      TEST_ASSERT(v[1].real()==20.0);
      TEST_ASSERT(v[2].imag()==30.1);
      TEST_ASSERT(v.capacity() == 3);
   
      DArray< std::complex<Data> > u;
      u.allocate(3);
   
      BinaryFileIArchive iArchive;
      openInputFile("binary", iArchive.file());
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
         u[i].real(0.0);
         u[i].imag(0.0);
      }
      i2 = 0;
   
      // Reload into u and i2
      openInputFile("binary", iArchive.file());
      iArchive >> u;
      iArchive >> i2;
   
      TEST_ASSERT(u[0].imag() == 10.1);
      TEST_ASSERT(u[1].real() == 20.0);
      TEST_ASSERT(u[2].imag() == 30.1);
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);
   }
   TEST_ASSERT(Memory::total() == memory_);
}

void DArrayTest::testSerialize2FileCmplx()
{
   printMethod(TEST_FUNC);
   {
      DArray< std::complex<Data> > v;
      v.allocate(3);
      for (int i=0; i < capacity; i++ ) {
         v[i].real((i+1)*10.0);
         v[i].imag((i+1)*10.0 + 0.1);
      }
     
      int i1 = 13;
      int i2;
  
      BinaryFileOArchive oArchive;
      openOutputFile("binary", oArchive.file());
      oArchive << v;
      oArchive << i1;
      oArchive.file().close();
   
      // Show that v is unchanged by packing
      TEST_ASSERT(v[0].imag() == 10.1);
      TEST_ASSERT(v[1].real() == 20.0);
      TEST_ASSERT(v[2].imag() == 30.1);
      TEST_ASSERT(v.capacity() == 3);
   
      DArray< std::complex<Data> > u;
   
      // u.allocate(3); -> 
      // Note: We do not allocate first. This is the difference 
      // from the previous test
   
      BinaryFileIArchive iArchive;
      openInputFile("binary", iArchive.file());
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
         u[i].real(0.0);
         u[i].imag(0.0);
      }
      i2 = 0;
   
      // Reload into u and i2
      openInputFile("binary", iArchive.file());
      iArchive >> u;
      iArchive >> i2;
   
      TEST_ASSERT(eq(u[0].imag(), 10.1));
      TEST_ASSERT(eq(u[1].real(), 20.0));
      TEST_ASSERT(eq(u[2].imag(), 30.1));
      TEST_ASSERT(i2 == 13);
      TEST_ASSERT(u.capacity() == 3);
   }
   TEST_ASSERT(Memory::total() == memory_);
}

TEST_BEGIN(DArrayTest)
TEST_ADD(DArrayTest, testConstructor)
TEST_ADD(DArrayTest, testAllocate)
TEST_ADD(DArrayTest, testSubscript)
TEST_ADD(DArrayTest, testSubscriptCmplx)
TEST_ADD(DArrayTest, testIterator)
//TEST_ADD(DArrayTest, testCopyConstructor)
TEST_ADD(DArrayTest, testCopyConstructorCmplx)
TEST_ADD(DArrayTest, testAssignment)
TEST_ADD(DArrayTest, testAssignmentCmplx)
TEST_ADD(DArrayTest, testBaseClassReference)
TEST_ADD(DArrayTest, testSerialize1MemoryCmplx)
TEST_ADD(DArrayTest, testSerialize2MemoryCmplx)
TEST_ADD(DArrayTest, testSerialize1FileCmplx)
TEST_ADD(DArrayTest, testSerialize2FileCmplx)
TEST_END(DArrayTest)

#endif
