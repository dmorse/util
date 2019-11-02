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
	
      #ifdef UTIL_CXX11
      using Clock = std::chrono::steady_clock;
      using TimePoint = Clock::time_point;
      #else
      using TimePoint = clock_t;
      #endif

      /**
      * Default constructor.
      */
      Timer();

      /**
      * Start timing from an externally supplied time
      *
      * Set start time and set isRunning = true.
      *
      * \param begin starting TimePoint.
      */
      void start(TimePoint begin);

      /**
      * Start timing from now (internally computed).
      *
      * Set start time and set isRunning = true.
      */
      void start();

      /**
      * Stop the clock at an externally supplied time.
      * 
      * Increment accumulated time, set isRunning = false.
      */
      void stop(TimePoint end);
     
      /** 
      * Stop the clock now (internally supplied).
      *
      * Increment accumulated time, set isRunning = false.
      */
      void stop();
     
      /**
      * Is this Timer running?
      */
      bool isRunning();

      /** 
      * Reset accumulated time to zero.
      */
      void clear();

      /**
      * Return the accumulated time, in seconds.
      */
      double time();

      /**
      * Return current time point.
      */
      static TimePoint now();

   private:

      #ifdef UTIL_CXX11
      using Duration = std::chrono::duration<double>;
      #else
      using Duration = double;
      #endif

      /// Accumulated time.
      Duration time_;
 
      /// Beginning of interval when Timer is running
      TimePoint begin_;
 
      /// Is the timer running now? 
      bool  isRunning_; 

   };

   /**
   * Return current time point (static function)
   */
   inline Timer::TimePoint Timer::now()
   #ifdef UTIL_CXX11
   {  return Clock::now(); }
   #else
   {  return clock(); }
   #endif

   /*
   * Start the timer with externally supplied time point.
   */ 
   inline 
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
   inline 
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
   inline void Timer::stop(TimePoint end)
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
   * Stop the timer.
   */ 
   inline void Timer::stop()
   {  stop(Timer::now()); }
   
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
   * Is this timer running?
   */ 
   inline bool Timer::isRunning()
   {  return isRunning_; }

}
#endif
