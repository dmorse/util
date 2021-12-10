/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Timer.h"

namespace Util
{

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

}
