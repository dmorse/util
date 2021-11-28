#ifndef EXCEPTION_TEST_H
#define EXCEPTION_TEST_H

#include <util/misc/Exception.h>
#include <util/global.h>

#ifdef UTIL_MPI
#ifndef TEST_MPI
#define TEST_MPI
#endif
#endif

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

using namespace Util;

class ExceptionTest : public UnitTest 
{

public:

   void setUp()
   {};

   void tearDown()
   {};

   void testConstructor() 
   {
      printMethod(TEST_FUNC);
      printEndl();

      Exception*  exceptionPtr_;
      exceptionPtr_ = new Exception("testConstructor", "My message",
                                 __FILE__, __LINE__, 1);
      exceptionPtr_->write(std::cout);
      delete exceptionPtr_;
      std::cout << "Expected Exception message" << std::endl;
   }

   void testThrow1() 
   {
      printMethod(TEST_FUNC);
      printEndl();

      try {
         throw Exception("testThrow", "My message",__FILE__,__LINE__,0);
      }
      catch (Exception e) {
         e.write(std::cout);
         std::cout << "Caught expected Exception" << std::endl;
      }

   }

   void testThrow2() 
   {
      printMethod(TEST_FUNC);
      printEndl();

      bool success = false;
      try {
         UTIL_THROW("My message");
      }
      catch (Exception e) {
         success = true;
         e.write(std::cout);
         std::cout << "Caught expected Exception" << std::endl;
      }
      TEST_ASSERT(success);
   }

   void testAssert() 
   {
      printMethod(TEST_FUNC);
      printEndl();

      bool success = false;
      try {
         UTIL_ASSERT(1 == 2);
      } 
      catch (Exception e) {
         success = true;
         std::cout << "Caught expected Exception" << std::endl;
      }
      TEST_ASSERT(success);
   }

};

TEST_BEGIN(ExceptionTest)
TEST_ADD(ExceptionTest, testConstructor)
TEST_ADD(ExceptionTest, testThrow1)
TEST_ADD(ExceptionTest, testThrow2)
//TEST_ADD(ExceptionTest, testAssert)
TEST_END(ExceptionTest)

#endif
