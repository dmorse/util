#ifndef LABEL_TEST_H
#define LABEL_TEST_H

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <util/param/Label.h>
#include <util/global.h>

#include <iostream>
#include <fstream>

using namespace Util;

class LabelTest : public UnitTest 
{

public:

   void setUp()
   { 
      Label::clear();
   }

   void tearDown()
   {}

   void testLabelConstructor1() 
   {
      printMethod(TEST_FUNC);
      Label label("MyLabel");
      TEST_ASSERT(Label::isClear());
      TEST_ASSERT(!Label::isMatched());

   }

   void testLabelConstructor2() 
   {
      printMethod(TEST_FUNC);
      Label label("MyLabel", false);
      TEST_ASSERT(Label::isClear());
      TEST_ASSERT(!Label::isMatched());
   }

   void testExtractor1() 
   {
      printMethod(TEST_FUNC);
      Label label("MyLabel");
      std::ifstream in;
      openInputFile("in/Label", in);
      in >> label;
      TEST_ASSERT(Label::isClear());
      TEST_ASSERT(Label::isMatched());
      in >> Label("YourLabel");
      TEST_ASSERT(Label::isClear());
      TEST_ASSERT(Label::isMatched());
      in.close();
   }

   void testExtractor2() 
   {
      printMethod(TEST_FUNC);
      Label label0("WrongLabel", false);
      Label label1("AnotherLabel", false);
      Label label2("MyLabel", false);
      Label label3("YourLabel", true);
      Label label4("LastLabel", false);
      std::ifstream in;
      openInputFile("in/Label", in);
      TEST_ASSERT(Label::isClear());
      TEST_ASSERT(!Label::isMatched());
      in >> label0;
      TEST_ASSERT(!Label::isClear());
      TEST_ASSERT(!Label::isMatched());
      in >> label1;
      TEST_ASSERT(!Label::isClear());
      TEST_ASSERT(!Label::isMatched());
      in >> label2;
      TEST_ASSERT(Label::isClear());
      TEST_ASSERT(Label::isMatched());
      in >> label3;
      TEST_ASSERT(Label::isClear());
      TEST_ASSERT(Label::isMatched());
      TEST_ASSERT(!label4.match(in));
      in.close();
   }

   #ifndef UTIL_MPI
   void testExtractor3() 
   {
      printMethod(TEST_FUNC);
      Label label0("WrongLabel", false);
      Label label1("AnotherLabel", false);
      Label label2("MyLabel", false);
      Label label3("YourLabel", true);
      std::ifstream in;
      openInputFile("in/Label", in);
      in >> label0;
      in >> label1;
      printEndl();
      try {
         in >> label3;
      } catch (Util::Exception& e) {
         std::cout << "Caught expected Exception" << std::endl;
         Label::clear();
      }
      in.close();
   }
   #endif

   void testInserter() 
   {
      printMethod(TEST_FUNC);
      printEndl();
      Label label("MyLabel");
      std::cout << label;
      std::cout << "\n"; 
   }

};


TEST_BEGIN(LabelTest)
TEST_ADD(LabelTest, testLabelConstructor1)
TEST_ADD(LabelTest, testLabelConstructor2)
TEST_ADD(LabelTest, testExtractor1)
TEST_ADD(LabelTest, testExtractor2)
#ifndef UTIL_MPI
TEST_ADD(LabelTest, testExtractor3)
#endif
TEST_ADD(LabelTest, testInserter)
TEST_END(LabelTest)

#endif
