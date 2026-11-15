#ifndef TEXT_FILE_ARCHIVE_TEST_H
#define TEXT_FILE_ARCHIVE_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/archives/TextFileOArchive.h>
#include <util/archives/TextFileIArchive.h>
#include "SerializeTestClass.h"

#include <complex>
#include <fstream>

using namespace Util;

class TextFileArchiveTest : public UnitTest 
{

public:

   TextFileArchiveTest() {}

   void setUp() {}
   void tearDown() {}

   void testOArchiveConstructor1();
   void testOArchiveConstructor2();
   void testPack();
   void testPackChar();
   void testPackCharArray();

};

void TextFileArchiveTest::testOArchiveConstructor1()
{
   printMethod(TEST_FUNC);
   TextFileOArchive  v;
   openOutputFile("tmp/TextTestOArchiveConstructor1", v.file());
} 

void TextFileArchiveTest::testOArchiveConstructor2()
{
   printMethod(TEST_FUNC);
   std::string filename = filePrefix();
   filename += "tmp/TextTestOArchiveConstructor2";
   TextFileOArchive  v(filename);
   v.file().close();
} 

void TextFileArchiveTest::testPack()
{
   printMethod(TEST_FUNC);
   TextFileOArchive  v;
   openOutputFile("tmp/TextTestPack", v.file());

   typedef double cmplx[2];

   // Declare variables
   int i1, i2;
   int u1, u2;
   double d1, d2;
   std::complex<double> c1, c2;
   std::string s1, s2;
   Vector a1, a2;
   SerializeTestClass o1, o2;
   double b1[4];
   double b2[4];
   double m1[3][3]; // intentionally oversized
   double m2[3][3]; // intentionally oversized
   cmplx z1; // double[2] type
   cmplx z2; // double[2] type

   // Initialize variables
   i1 = 3;
   u1 = 7;
   d1 = 45.0;
   c1 = std::complex<double>(3.0, 4.0);
   s1 = "My string has spaces";
   a1[0] =  1.3;
   a1[1] = -2.3;
   a1[2] =  3.3;
   o1.i  =  13;
   o1.d  =  26.0;
   b1[0] = 9.0;
   b1[1] = 8.0;
   b1[2] = 7.0;
   b1[3] = 6.0;
   m1[0][0] = 13.0;
   m1[0][1] = 14.0;
   m1[1][0] = 15.0;
   m1[1][1] = 16.0;
   z1[0] = 0.6;
   z1[1] = 0.4;
  
   // Write variables to OArchive v
   v << i1;
   v & u1;
   v & d1;
   v << c1;
   v << s1;
   v << a1;
   v << o1;
   v << z1;
   v.pack(b1, 4);
   v.pack(m1[0], 2, 2, 3);
   v.file().close();

   TextFileIArchive u;
   openInputFile("tmp/TextTestPack", u.file());

   u >> i2;
   TEST_ASSERT(i1 == i2);

   u & u2;
   TEST_ASSERT(u1 == u2);

   u & d2;
   TEST_ASSERT(d1 == d2);

   u & c2;
   TEST_ASSERT(c1 == c2);

   u >> s2;
   TEST_ASSERT(s1 == s2);

   u >> a2;
   TEST_ASSERT(a1 == a2);

   u >> o2;
   TEST_ASSERT(o2.i == 13);
   TEST_ASSERT(o2.d == 26.0);

   // Fixed size array
   u & z2;
   TEST_ASSERT(eq(z1[0], z2[0]));
   TEST_ASSERT(eq(z1[1], z2[1]));
   TEST_ASSERT(eq(z2[0], 0.6));
   TEST_ASSERT(eq(z2[1], 0.4));

   // std::cout << std::endl;
   // std::cout << "z2[0] = " << z2[0] << std::endl;
   // std::cout << "z2[1] = " << z2[1] << std::endl;

   u.unpack(b2, 4);
   for (int j = 0; j < 4; ++j) {
      TEST_ASSERT(b1[j] == b2[j]);
   }

   u.unpack(m2[0], 2, 2, 3);
   int i, j;
   for (i = 0; i < 2; ++i) {
      for (j = 0; j < 2; ++j) {
         TEST_ASSERT(eq(m1[i][j], m2[i][j]));
      }
   }

}

/*
* Characters, including whitespace characters, after other values.
*/
void TextFileArchiveTest::testPackChar()
{
   printMethod(TEST_FUNC);
   TextFileOArchive  v;
   openOutputFile("tmp/TextTestPackChar", v.file());

   int i1 = 13;
   double d1 = 2.5;
   std::string s1 = " two  words ";
   char c1[4] = {'Q', ' ', '\n', '\t'};

   v << i1;
   for (int k = 0; k < 4; ++k) {
      v << c1[k];
   }
   v << d1;
   v << c1[0];
   v << s1;
   v << c1[1];
   v << i1;
   v.file().close();

   TextFileIArchive u;
   openInputFile("tmp/TextTestPackChar", u.file());
   int i2;
   double d2;
   std::string s2;
   char c2;

   u >> i2;
   TEST_ASSERT(i2 == i1);
   for (int k = 0; k < 4; ++k) {
      u >> c2;
      TEST_ASSERT(c2 == c1[k]);
   }
   u >> d2;
   TEST_ASSERT(d2 == d1);
   u >> c2;
   TEST_ASSERT(c2 == c1[0]);
   u >> s2;
   TEST_ASSERT(s2 == s1);
   u >> c2;
   TEST_ASSERT(c2 == c1[1]);
   u >> i2;
   TEST_ASSERT(i2 == i1);
   TEST_ASSERT(!u.file().fail());
}

/*
* Arrays of characters, including whitespace characters.
*/
void TextFileArchiveTest::testPackCharArray()
{
   printMethod(TEST_FUNC);
   TextFileOArchive  v;
   openOutputFile("tmp/TextTestPackCharArray", v.file());

   int i1 = 13;
   char b1[4] = {'A', ' ', '\n', 'Z'};
   char m1[2][3] = {{'a', 'b', 'x'}, {'\t', 'd', 'x'}};
   v.pack(b1, 4);
   v.pack(m1[0], 2, 2, 3);
   v << i1;
   v.file().close();

   TextFileIArchive u;
   openInputFile("tmp/TextTestPackCharArray", u.file());
   int i2 = 0;
   char b2[5] = {'#', '#', '#', '#', '#'};
   char m2[2][3] = {{'#', '#', '#'}, {'#', '#', '#'}};
   u.unpack(b2, 4);
   u.unpack(m2[0], 2, 2, 3);
   u >> i2;
   TEST_ASSERT(!u.file().fail());

   for (int j = 0; j < 4; ++j) {
      TEST_ASSERT(b2[j] == b1[j]);
   }
   TEST_ASSERT(b2[4] == '#');
   for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
         TEST_ASSERT(m2[i][j] == m1[i][j]);
      }
      TEST_ASSERT(m2[i][2] == '#');
   }
   TEST_ASSERT(i2 == i1);

   // Arrays without separators, as written by hand
   std::ofstream out;
   openOutputFile("tmp/TextTestPackCharArray2", out);
   out << "ABC\nab\ncd\n7\n";
   out.close();
   TextFileIArchive w;
   openInputFile("tmp/TextTestPackCharArray2", w.file());
   int i3 = 0;
   char b3[4] = {'#', '#', '#', '#'};
   char m3[2][3] = {{'#', '#', '#'}, {'#', '#', '#'}};
   w.unpack(b3, 3);
   w.unpack(m3[0], 2, 2, 3);
   w >> i3;
   TEST_ASSERT(!w.file().fail());
   TEST_ASSERT(b3[0] == 'A' && b3[1] == 'B' && b3[2] == 'C');
   TEST_ASSERT(b3[3] == '#');
   TEST_ASSERT(m3[0][0] == 'a' && m3[0][1] == 'b');
   TEST_ASSERT(m3[1][0] == 'c' && m3[1][1] == 'd');
   TEST_ASSERT(m3[0][2] == '#' && m3[1][2] == '#');
   TEST_ASSERT(i3 == 7);
}

TEST_BEGIN(TextFileArchiveTest)
TEST_ADD(TextFileArchiveTest, testOArchiveConstructor1)
TEST_ADD(TextFileArchiveTest, testOArchiveConstructor2)
TEST_ADD(TextFileArchiveTest, testPack)
TEST_ADD(TextFileArchiveTest, testPackChar)
TEST_ADD(TextFileArchiveTest, testPackCharArray)
TEST_END(TextFileArchiveTest)

#endif
