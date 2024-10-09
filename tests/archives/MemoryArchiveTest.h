#ifndef MEMORY_ARCHIVE_TEST_H
#define MEMORY_ARCHIVE_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/archives/MemoryOArchive.h>
#include <util/archives/MemoryIArchive.h>
#include <util/archives/MemoryCounter.h>
#include "SerializeTestClass.h"

#include <complex>

using namespace Util;

class MemoryArchiveTest : public UnitTest 
{

private:

   const static size_t capacity = 128;

public:

   void setUp() {}
   void tearDown() {}
   void testOArchiveConstructor();
   void testOArchiveAllocate();
   void testIArchiveConstructor();
   void testIArchiveAllocate();
   void testAssign();
   void testPack();
   void testPackArray();
   void testSerializeObject();

};


void MemoryArchiveTest::testOArchiveConstructor()
{
   printMethod(TEST_FUNC);
   MemoryOArchive  v;
   TEST_ASSERT(v.capacity() == 0 );
   TEST_ASSERT(!v.isAllocated() );
} 

void MemoryArchiveTest::testOArchiveAllocate()
{
   printMethod(TEST_FUNC);
   MemoryOArchive  v;
   v.allocate(capacity);
   TEST_ASSERT(v.capacity() == capacity);
   TEST_ASSERT(v.cursor() == v.begin() );
   TEST_ASSERT(v.isAllocated() );
} 

void MemoryArchiveTest::testIArchiveConstructor()
{
   printMethod(TEST_FUNC);
   MemoryIArchive  v;
   TEST_ASSERT(v.capacity() == 0 );
   TEST_ASSERT(!v.isAllocated() );
} 

void MemoryArchiveTest::testIArchiveAllocate()
{
   printMethod(TEST_FUNC);
   MemoryIArchive  v;
   v.allocate(capacity);
   TEST_ASSERT(v.capacity() == capacity );
   TEST_ASSERT(v.cursor() == v.begin() );
   TEST_ASSERT(v.end() == v.begin() );
   TEST_ASSERT(v.isAllocated() );
} 

void MemoryArchiveTest::testAssign()
{
   printMethod(TEST_FUNC);
   MemoryOArchive  v;
   v.allocate(capacity);
   TEST_ASSERT(v.capacity() == capacity );
   TEST_ASSERT(v.cursor() == v.begin() );
   TEST_ASSERT(v.isAllocated() );

   MemoryIArchive u;
   u = v;

   TEST_ASSERT(u.capacity() == capacity );
   TEST_ASSERT(u.cursor() == v.begin() );
   TEST_ASSERT(u.end() == v.begin() );
   TEST_ASSERT(u.isAllocated() );
} 

void MemoryArchiveTest::testPack()
{
   printMethod(TEST_FUNC);
   MemoryOArchive  v;
   MemoryCounter   w;
   v.allocate(capacity);
   TEST_ASSERT(v.capacity() == capacity);
   TEST_ASSERT(v.isAllocated() );
   TEST_ASSERT(v.cursor() == v.begin());

   // Typedef for complex as double[2]
   typedef double cmplx[2];

   // Declare variables
   int i1, i2;
   double d1, d2;
   std::complex<double> c1, c2;
   std::string s1, s2;
   Vector a1, a2;
   cmplx z1, z2;
   size_t offset;   

   // Initialize variables
   i1 = 3;
   d1 = 45.0;
   c1 = std::complex<double>(3.0, 4.0);
   s1 = "My string has spaces";
   a1[0] =  1.3;
   a1[1] = -2.3;
   a1[2] =  3.3;
   z1[0] = 0.6;
   z1[1] = 0.4;
  
   // Write variables to MemoryOArchive v and MemoryCounter w
   v << i1;
   w << i1;
   offset = sizeof(int);
   TEST_ASSERT(v.cursor() == v.begin() + offset);
   TEST_ASSERT(w.size() == offset);

   v & d1;
   w & d1;
   offset += sizeof(double);
   TEST_ASSERT(v.cursor() == v.begin() + offset);
   TEST_ASSERT(w.size() == offset);

   v << c1;
   w << c1;
   offset += sizeof(std::complex<double>);
   TEST_ASSERT(v.cursor() == v.begin() + offset);
   TEST_ASSERT(w.size() == offset);

   v << s1;
   w << s1;
   offset += memorySize(s1);
   TEST_ASSERT(v.cursor() == v.begin() + offset);
   TEST_ASSERT(w.size() == offset);

   v << a1;
   w << a1;
   offset += memorySize(a1);
   TEST_ASSERT(v.cursor() == v.begin() + offset);
   TEST_ASSERT(w.size() == offset);

   v << z1;
   w << z1;
   offset += memorySize(z1);
   TEST_ASSERT(memorySize(z1) == 2*sizeof(double));
   TEST_ASSERT(v.cursor() == v.begin() + offset);
   TEST_ASSERT(w.size() == offset);

   // Read data from IArchive u
   MemoryIArchive u;
   u = v;
   TEST_ASSERT(u.cursor() == u.begin());
   TEST_ASSERT(u.end() == v.cursor());

   u >> i2;
   offset = sizeof(int);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(i1 == i2);

   u & d2;
   offset += sizeof(double);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(d1 == d2);

   u & c2;
   offset += sizeof(std::complex<double>);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(c1 == c2);

   u >> s2;
   offset += memorySize(s2);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(s1 == s2);
   //std::cout << std::endl;
   //std::cout << s2 << std::endl;

   u >> a2;
   offset += memorySize(a2);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(a1 == a2);

   u >> z2;
   offset += memorySize(z2);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(eq(z1[0], z2[0]));
   TEST_ASSERT(eq(z1[1], z2[1]));

   // Reset and begin rereading
   u.reset();
   TEST_ASSERT(u.cursor() == u.begin());
   TEST_ASSERT(u.end() == v.cursor());

   u >> i2;
   offset = sizeof(int);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(i1 == i2);

   u.release();
   TEST_ASSERT(!u.isAllocated());

   v.clear();
   TEST_ASSERT(v.cursor() == v.begin());
   v << i1;

}
 
void MemoryArchiveTest::testPackArray()
{
   printMethod(TEST_FUNC);

   MemoryOArchive v;
   v.allocate(capacity);
   TEST_ASSERT(v.cursor() == v.begin());
   TEST_ASSERT(v.capacity() == capacity);

   // Typedef for complex number as fixed-size array
   typedef double cmplx[2];

   // Declare variables
   int offset;   
   int i1, i2;
   double d1, d2;
   std::complex<double> c1, c2;
   double a1[4];
   double a2[4];
   double m1[3][3]; // intentionally oversized
   double m2[3][3]; // intentionally oversized
   cmplx z1; 
   cmplx z2; 

   // Initialize values
   i1 = 3;
   d1 = 45.0;
   c1 = std::complex<double>(3.0, 4.0);
   a1[0] = 9.0;
   a1[1] = 8.0;
   a1[2] = 7.0;
   a1[3] = 6.0;
   m1[0][0] = 13.0;
   m1[0][1] = 14.0;
   m1[1][0] = 15.0;
   m1[1][1] = 16.0;
   z1[0] = 0.6;
   z1[1] = 0.4;
  
   // Pack data into OArchive v 
   v << i1;
   offset = sizeof(int);
   TEST_ASSERT(v.cursor() == v.begin() + offset);

   v << d1;
   offset += sizeof(double);
   TEST_ASSERT(v.cursor() == v.begin() + offset);

   v.pack(a1, 4);
   offset += 4*sizeof(double);
   TEST_ASSERT(v.cursor() == v.begin() + offset);

   v << c1;
   offset += sizeof(std::complex<double>);
   TEST_ASSERT(v.cursor() == v.begin() + offset);

   v.pack(m1[0], 2, 2, 3);
   offset += 4*sizeof(double);
   TEST_ASSERT(v.cursor() == v.begin() + offset);

   v << z1;
   offset += 2*sizeof(double);
   TEST_ASSERT(v.cursor() == v.begin() + offset);

   // Read data from IArchive u
   MemoryIArchive u;
   u = v;

   TEST_ASSERT(u.begin() == v.begin());
   TEST_ASSERT(u.cursor() == v.begin());
   TEST_ASSERT(u.end() == v.cursor());
   TEST_ASSERT(u.end() == u.begin() + offset);

   u >> i2;
   offset = sizeof(int);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(i1 == i2);

   u >> d2;
   offset += sizeof(double);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(eq(d1, d2));

   u.unpack(a2, 4);
   offset += 4*sizeof(double);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   int i, j;
   for (j = 0; j < 4; ++j) {
      TEST_ASSERT(eq(a1[j],a2[j]));
   }

   u & c2;
   offset += sizeof(std::complex<double>);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(eq(c1.real(), c2.real()));
   TEST_ASSERT(eq(c1.imag(), c2.imag()));

   u.unpack(m2[0], 2, 2, 3);
   offset += 4*sizeof(double);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   for (i = 0; i < 2; ++i) {
      for (j = 0; j < 2; ++j) {
         TEST_ASSERT(eq(m1[i][j], m2[i][j]));
      }
   }
  
   u & z2;
   offset += 2*sizeof(double);
   TEST_ASSERT(u.cursor() == u.begin() + offset);
   TEST_ASSERT(eq(z1[0], z2[0]));
   TEST_ASSERT(eq(z1[1], z2[1]));
   TEST_ASSERT(eq(z2[0], 0.6));
   TEST_ASSERT(eq(z2[1], 0.4));
   //std::cout << std::endl;
   //std::cout << "z2[0] = " << z2[0] << std::endl;
   //std::cout << "z2[1] = " << z2[1] << std::endl;

}

void MemoryArchiveTest::testSerializeObject()
{
   printMethod(TEST_FUNC);

   MemoryOArchive v;
   MemoryIArchive u;
   SerializeTestClass a, b;

   a.i =13;
   a.d =26.0;

   int size = memorySize(a);
   v.allocate(size);

   v << a;
   TEST_ASSERT(v.cursor() == v.begin() + size);

   u = v;
   u >> b;

   TEST_ASSERT(b.i == 13);
   TEST_ASSERT(b.d == 26.0);

}

TEST_BEGIN(MemoryArchiveTest)
TEST_ADD(MemoryArchiveTest, testOArchiveConstructor)
TEST_ADD(MemoryArchiveTest, testOArchiveAllocate)
TEST_ADD(MemoryArchiveTest, testIArchiveConstructor)
TEST_ADD(MemoryArchiveTest, testIArchiveAllocate)
TEST_ADD(MemoryArchiveTest, testAssign)
TEST_ADD(MemoryArchiveTest, testPack)
TEST_ADD(MemoryArchiveTest, testPackArray)
TEST_ADD(MemoryArchiveTest, testSerializeObject)
TEST_END(MemoryArchiveTest)

#endif
