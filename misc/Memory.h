#ifndef UTIL_MEMORY_H
#define UTIL_MEMORY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>
#include <stddef.h>
#include <iostream>
#include <new>

namespace Util
{

   /**
   * Provides method to allocate array.
   *
   * The Memory::allocate() method invokes the new operator within a
   * try-catch block, and keeps track of the total memory allocated via
   * this class.
   *
   * \ingroup Misc_Module
   */
   class Memory
   {
   public:

      /**
      * Allocate a C++ array.
      *
      * This function calls C++ new operator to allocate an array
      * containing size elemnents of type Data. It assigns parameter ptr to
      * the address of the first element, adds size * sizeof(Data) to the
      * to the current total, and updates the max counter if the resulting
      * total exceeds the previous maximum.
      *
      * \param ptr reference to pointer (output)
      * \param size number of elements
      */
      template <typename Data>
      static void allocate(Data*& ptr, size_t size);

      /**
      * Add size of a newly allocated array in bytes to total.
      *
      * This function accounts for the size of an array that was allocated
      * externally. It adds size * sizeof(Data) to the current counter and
      * updates max if the resulting total exceeds the previous maximum.
      *
      * \param size number of elements
      */
      template <typename Data>
      static void add(size_t size);

      /**
      * Deallocate a C++ array.
      *
      * Uses the C++ delete [] operator to deallocate a Data array of size
      * elements of type Data that was allocated by the Memory::allocate 
      * member function. On input, ptr must be the pointer to an array of 
      * elements of type Data, and size must be the number of elements. On 
      * output, the array is deleted, ptr is set to nullptr, and the total
      * counter is decremented by size * sizeof(Data).
      *
      * \param ptr  reference to pointer (ptr is set to nullptr on output)
      * \param size  number of elements in existing array
      */
      template <typename Data>
      static void deallocate(Data*& ptr, size_t size);

      /**
      * Subtract size of a newly deleted array in bytes from total.
      *
      * This function accounts for the size of an array that was deleted
      * externally. It subtracts size * sizeof(Data) from the current 
      * counter, or throws an Exception if the resulting total would be
      * negative.
      *
      * \param size number of elements
      */
      template <typename Data>
      static void sub(size_t size);

      /**
      * Reallocate a C++ array.
      *
      * This function calls allocate to allocate a new array of size
      * newSize. If oldSize > 0, it copies all existing elements, and
      * then deallocates the old array. On return, ptr is the address 
      * of the new array.
      *
      * Precondition: On input, newSize > 0 and newSize > oldSize.
      *
      * \param ptr reference to pointer (input/output)
      * \param oldSize number of elements in existing array
      * \param newSize number of elements in new array
      */
      template <typename Data>
      static void reallocate(Data*& ptr, size_t oldSize, size_t newSize);

      /**
      * Return number of times reallocate() or add() have been called.
      *
      * Each call to reallocate() also increments nAllocate(), because
      * allocate() is called internally.
      */
      static long int nAllocate();

      /**
      * Return number of times deallocate() or sub() have been called.
      *
      * Each call to reallocate() also increments nDeallocate(), because
      * deallocate() is called internally.
      */
      static long int nDeallocate();

      /**
      * Return total amount of memory currently allocated.
      */
      static long int total();

      /**
      * Return the maximum amount of allocated heap memory thus far.
      *
      * This function returns the temporal maximum of total().
      */
      static long int max();

      #ifdef UTIL_MPI
      /**
      * Return max for any processor in communicator.
      */
      static long int max(MPI::Intracomm& communicator);
      #endif

      /**
      * Reset total and max counters to zero.
      */
      static void clearCounters();

      /**
      * Call this just to guarantee initialization of static memory.
      */
      static void initStatic();

   private:

      /// Total amount of memory currently allocated, in bytes.
      static long int total_;

      /// Maximum amount of memory allocated, in bytes.
      static long int max_;

      /// Number of calls to allocate.
      static long int nAllocate_;

      /// Number of calls to deallocate.
      static long int nDeallocate_;

   };

   // Member function template definitions

   /*
   * Allocate an array.
   */
   template <typename Data>
   void Memory::allocate(Data*& ptr, size_t size)
   {
      if (ptr) {
         UTIL_THROW("Attempt to allocate to non-null pointer");
      }
      try {
         ptr = new Data[size];
         UTIL_CHECK(ptr);
      } catch (std::bad_alloc&) {
         std::cout << "Allocation error in Util::Memory" << std::endl;
         throw;
      }
      add<Data>(size);
   }

   /*
   * Add size of a newly allocated C-Array to the current total.
   */
   template <typename Data>
   void Memory::add(size_t size)
   {
      total_ += size * sizeof(Data);
      ++nAllocate_;
      if (total_ > max_) max_ = total_;
   }

   /*
   * De-allocate an array that was allocated with Memory::allocate.
   */
   template <typename Data>
   void Memory::deallocate(Data*& ptr, size_t size)
   {
      // Preconditions
      UTIL_CHECK(ptr);
      UTIL_CHECK(size > 0);

      delete [] ptr;
      ptr = nullptr;
      sub<Data>(size);
   }

   /*
   * Subtract size of a newly deleted array from current total.
   */
   template <typename Data>
   void Memory::sub(size_t size)
   {
      UTIL_CHECK(size > 0);
      long int change = size * sizeof(Data);
      UTIL_CHECK(total_ >= change);
      total_ -= change;
      ++nDeallocate_;
   }

   /*
   * Re-allocate an array (allocate new array, copy, and deallocate old).
   */
   template <typename Data>
   void Memory::reallocate(Data*& ptr, size_t oldSize, size_t newSize)
   {
      UTIL_CHECK(newSize > 0);
      UTIL_CHECK(newSize > oldSize);

      Data* newPtr = nullptr;
      allocate(newPtr, newSize);
      if (oldSize > 0) {
         UTIL_CHECK(ptr);
         for (size_t i = 0; i < oldSize; ++i) {
            newPtr[i] = ptr[i];
         }
         deallocate(ptr, oldSize);
      }
      ptr = newPtr;
   }

}
#endif
