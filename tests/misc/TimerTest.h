#ifndef TIMER_TEST_H
#define TIMER_TEST_H

#include <util/misc/Timer.h>
#include <util/global.h>

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

using namespace Util;

class TimerTest : public UnitTest 
{

public:

   void setUp()
   {};

   void tearDown()
   {};

   void testConstructor() 
   {
      printMethod(TEST_FUNC);
      Timer timer;
   }



   void testLoop1() 
   {
      printMethod(TEST_FUNC);
      
      long int max = 100000000;
      long int k = -1000;
      long int j = k;
      long int i;

      // Accumulate time for one loop
      Timer timer;
      timer.start();
      for (i = 0; i < max; ++i) {
         j += 3;
      }
      timer.stop();

      std::cout << std::endl;
      std::cout << "Total loop time = " 
                << timer.time() << " sec" << std::endl;
      std::cout << "Iteration time  = " 
                << timer.time()/double(max) << " sec" 
                << std::endl;

      // Accumulate time for a second loop
      timer.start();
      for (i = 0; i < max; ++i) {
         j += 3;
      }
      timer.stop();
      std::cout << "Final loop time = " 
                << timer.time() << " sec" << std::endl;

      // Trivial test to avoid warnings that j is unused
      TEST_ASSERT(j == k + 6*max);
   }

   void testLoop2() 
   {
      printMethod(TEST_FUNC);
      Timer timer;
      Timer::TimePoint now;
      
      long int max = 100000000;
      long int k = -1000;
      long int j = k;
      long int i;

      // Accumulate time for one loop
      now = Timer::now();
      timer.start(now);
      for (i = 0; i < max; ++i) {
         j += 3;
      }
      now = Timer::now();
      timer.stop(now);
      std::cout << std::endl;
      std::cout << "Total loop time = " 
                << timer.time() << " sec" << std::endl;
      std::cout << "Iteration time  = " 
                << timer.time()/double(max) << " sec" 
                << std::endl;

      // Accumulate time for a second loop
      now = Timer::now();
      timer.start(now);
      for (i = 0; i < max; ++i) {
         j += 3;
      }
      now = Timer::now();
      timer.stop(now);
      std::cout << "Final loop time = " 
                << timer.time() << " sec" << std::endl;

      // Trivial test to avoid warnings that j is unused
      TEST_ASSERT(j == k + 6*max);
   }

};

TEST_BEGIN(TimerTest)
TEST_ADD(TimerTest, testConstructor)
TEST_ADD(TimerTest, testLoop1)
TEST_ADD(TimerTest, testLoop2)
TEST_END(TimerTest)
#endif
