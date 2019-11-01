#ifndef UTIL_TIMER_H
#define UTIL_TIMER_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>

#ifdef UTIL_CXX11
#include <chrono>
#else
#include <ctime>
#endif

namespace Util
{

   /**
   * Wall clock timer.
   *
   * A Timer keeps track of the time elapsed during one or more
   * interval. Each interval begins when start() is called and
   * ends when stop() is called. If start() and stop() are invoked 
   * repeatedly, the timer accumulates the time elapses in multiple 
   * intervals.  The accumulated time is returned by the time()
   * method, and can be reset to zero by the clear() method.
   *
   * \ingroup Misc_Module
   */
   class Timer
   {
   
   public:
	
      /// Constructor.
      Timer();

      /// Start the clock.
      void start();

      /// Stop the clock, increment accumulated time.
      void stop();
      
      /// Set accumulated time to zero.
      void clear();

      /// Get the accumulated time, in seconds
      double time();

      /// Is the timer running?
      bool isRunning();

      #ifdef UTIL_CXX11
      using Clock = std::chrono::steady_clock;
      using Duration = std::chrono::duration<double>;
      using TimePoint = Clock::time_point;
      #else
      using Duration = double;
      using TimePoint = clock_t;
      #endif

   private:

      /// Accumulated time.
      Duration time_;
 
      /// Beginning of interval when Timer is running
      TimePoint begin_;
 
      /// Is the timer running now? 
      bool  isRunning_; 

   };

   /**
   * Constructor
   */
   inline Timer::Timer()
    : isRunning_(false)
   {}
  
   /*
   * Start the timer.
   */ 
   inline void Timer::start()
   {
      if (isRunning_) {
         UTIL_THROW("Attempt to restart an active Timer");
      }
      isRunning_ = true;
      #ifdef UTIL_CXX11
      begin_ = Clock::now();
      #else
      begin_ = clock(); 
      #endif
   }
   
   /*
   * Stop the timer.
   */ 
   inline void Timer::stop()
   {
      TimePoint end;
      #ifdef UTIL_CXX11
      end = Clock::now();
      #else
      end = clock();
      #endif
      if (isRunning_) {
         isRunning_ = false;
      } else {
         UTIL_THROW("Attempt to stop an inactive Timer");
      }
      #ifdef UTIL_CXX11
      time_ += end - begin_;
      #else
      time_ += double(end - begin_)/double(CLOCKS_PER_SEC); 
      #endif
   }
   
   /*
   * Clear the timer.
   */ 
   inline void Timer::clear()
   {
      #ifdef UTIL_CXX11
      time_  = Duration::zero();
      #else
      time_  = 0.0;
      #endif
      isRunning_ = false;
   }

   /*
   * Get the current time.
   */ 
   inline double Timer::time()
   {
      #ifdef UTIL_CXX11
      return time_.count();
      #else
      return time_;
      #endif
   }

   /*
   * Is this timer running?
   */ 
   inline bool Timer::isRunning()
   {  return isRunning_; }

}
#endif
