/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Timer.h"

namespace Util
{

   // Static function

   /*
   * Return current time point (static function)
   */
   Timer::TimePoint Timer::now()
   #ifdef UTIL_CXX11
   {  return Clock::now(); }
   #else
   {  return clock(); }
   #endif

   // Non-static member functions

   /*
   * Constructor
   */
   Timer::Timer()
    : isRunning_(false)
   {  clear(); }
  
   /*
   * Get the current time.
   */ 
   double Timer::time()
   {
      #ifdef UTIL_CXX11
      return time_.count();
      #else
      return time_;
      #endif
   }

   /*
   * Start the timer with externally supplied time point.
   */ 
   void Timer::start(TimePoint begin)
   {
      if (isRunning_) {
         UTIL_THROW("Attempt to restart an active Timer");
      }
      isRunning_ = true;
      begin_ = begin;
   }
   
   /*
   * Start the timer.
   */ 
   void Timer::start()
   {
      if (isRunning_) {
         UTIL_THROW("Attempt to restart an active Timer");
      }
      isRunning_ = true;
      begin_ = Timer::now();
   }
   
   /*
   * Stop the timer at externally supplied time point.
   */ 
   void Timer::stop(TimePoint end)
   {
      if (!isRunning_) {
         UTIL_THROW("Attempt to stop an inactive Timer");
      }
      isRunning_ = false;
      #ifdef UTIL_CXX11
      time_ += end - begin_;
      #else
      time_ += double(end - begin_)/double(CLOCKS_PER_SEC); 
      #endif
   }
   
   /*
   * Clear the timer.
   */ 
   void Timer::clear()
   {
      #ifdef UTIL_CXX11
      time_  = Duration::zero();
      #else
      time_  = 0.0;
      #endif
      isRunning_ = false;
   }

}
