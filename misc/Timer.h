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
      typedef clock_t TimePoint;
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
      * Reset accumulated time to zero.
      */
      void clear();

      /**
      * Is this Timer running?
      */
      bool isRunning() const;

      /**
      * Return the accumulated time, in seconds.
      */
      double time() const;

      /**
      * Return current time point.
      */
      static TimePoint now();

   private:

      #ifdef UTIL_CXX11
      using Duration = std::chrono::duration<double>;
      #else
      typedef double Duration;
      #endif

      /// Accumulated time.
      Duration time_;
 
      /// Beginning of interval when Timer is running
      TimePoint begin_;
 
      /// Is the timer running now? 
      bool  isRunning_; 

   };

   /*
   * Stop the timer.
   */ 
   inline void Timer::stop()
   {  stop(Timer::now()); }
   
   /*
   * Is this timer running?
   */ 
   inline bool Timer::isRunning() const
   {  return isRunning_; }

}
#endif
