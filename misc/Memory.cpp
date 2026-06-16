/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Memory.h"

namespace Util
{

   /// Number of calls to allocate.
   long int Memory::nAllocate_ = 0;

   /// Number of calls to de-allocate.
   long int Memory::nDeallocate_ = 0;

   /// Total amount of memory allocated, in bytes.
   long int Memory::total_ = 0;

   /// Maximum of total over course of simulation.
   long int Memory::max_ = 0;

   /*
   * Call this to ensure compilation of this file. 
   */
   void Memory::initStatic()
   {  max_ = 0; }  

   /*
   * Return number of calls to allocate.
   */
   long int Memory::nAllocate()
   {  return nAllocate_; }

   /*
   * Return number of calls to deallocate.
   */
   long int Memory::nDeallocate()
   {  return nDeallocate_; }

   /*
   * Return total amount of memory allocated thus far.
   */
   long int Memory::total()
   {  return total_; }

   /*
   * Return maximum amount of allocated memory thus far.
   */
   long int Memory::max()
   {  return max_; }

   #ifdef UTIL_MPI
   /*
   * Return maximum amount of memory allocated on any one processor.
   */
   long int Memory::max(MPI::Intracomm& communicator)
   { 
      long int maxGlobal;
      long int maxLocal = max_;
      communicator.Allreduce(&maxLocal, &maxGlobal, 1, 
		             MPI::LONG_INT, MPI::MAX);
      return maxGlobal;
   }
   #endif

   /*
   * Clear total and max counters.
   */
   void Memory::clearCounters()
   {
      total_ = 0;
      max_ = 0;
   }

} 
