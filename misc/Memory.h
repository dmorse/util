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
   * The Memory::allocate() method invokes the new operator within
   * a try catch block, and keeps track of the total memory 
   * allocated.
   *
   * \ingroup Misc_Module
   */
   class Memory
   { 
   public:

      /**
      * Allocate a C++ array.
      *
      * Uses new to allocates a Data array of size elements, assigns ptr 
      * the address of the first element. 
      * 
      * \param ptr reference to pointer (output)
      * \param size number of elements
      */
      template <typename Data>
      static void allocate(Data*& ptr, size_t size);

      /**
      * Deallocate a C++ array.
      *
      * Uses free to deallocate a Data array of size elements.
      * 
      * \param ptr reference to pointer (intput, ptr = 0 on output)
      * \param size number of elements in existing array
      */
      template <typename Data>
      static void deallocate(Data*& ptr, size_t size);

      /**
      * Reallocate a C++ array.
      *
      * This function calls allocate to allocate a new array, copies 
      * all existing elements and deallocates old and calls deallocate 
      * to free the old array. On outputs, ptr is the address of the
      * new array.
      *
      * Precondition: On input, newSize > oldSize.
      *
      * \param ptr reference to pointer (input/output)
      * \param oldSize number of elements in existing array
      * \param newSize number of elements in new array
      */
      template <typename Data>
      static void reallocate(Data*& ptr, size_t oldSize, size_t newSize);

      /**
      * Return number of times allocate() was called.
      *
      * Each call to reallocate() also increments nAllocate(), because 
      * allocate() is called internally. 
      */
      static int nAllocate();

      /**
      * Return number of times deallocate() was called.
      *
      * Each call to reallocate() also increments nDeallocate(), because 
      * deallocate() is called internally. 
      */
      static int nDeallocate();

      /**
      * Return total amount of memory currently allocated.
      */
      static int total();

      /**
      * Return the maximum amount of allocated heap memory thus far.
      *
      * This function returns the temporal maximum of total().
      */
      static int max();

      #ifdef UTIL_MPI
      /**
      * Return max for any processor in communicator.
      */
      static int max(MPI::Intracomm& communicator);
      #endif

      /**
      * Call this just to guarantee initialization of static memory.
      */
      static void initStatic();
   
   private: 

      /// Total amount of memory allocated, in bytes. 
      static int total_;
   
      /// Maximum amount of memory allocated, in bytes. 
      static int max_;
   
      /// Number of calls to allocate.
      static int nAllocate_;
   
      /// Number of calls to deallocate.
      static int nDeallocate_;
   
   };
   
   /*
   * Allocate a C array.
   */
   template <typename Data>
   void Memory::allocate(Data*& ptr, size_t size)
   {
     if (ptr) {
         UTIL_THROW("Attempt to allocate to non-null pointer");
      }
      try {
         ptr = new Data[size];
         total_ += (size*sizeof(Data));
         ++nAllocate_;
         if (total_ > max_) max_ = total_;
      } catch (std::bad_alloc&) {
         std::cout << "Allocation error" << std::endl;
         throw;
      }
   }

   /*
   * De-allocate a C array.
   */
   template <typename Data>
   void Memory::deallocate(Data*& ptr, size_t size)
   {
      // Preconditions
      UTIL_CHECK(ptr);
      UTIL_CHECK(size > 0);

      delete [] ptr;
      ptr = 0;
      total_ -= size*sizeof(Data);
      ++nDeallocate_;
   }

   /*
   * Re-allocate a C array (allocate and copy).
   */
   template <typename Data>
   void Memory::reallocate(Data*& ptr, size_t oldSize, size_t newSize)
   {
      UTIL_CHECK(newSize > 0);
      UTIL_CHECK(oldSize >= 0);
      UTIL_CHECK(newSize > oldSize);

      Data* newPtr = 0;
      allocate(newPtr, newSize);
      if (oldSize > 0) {
         UTIL_CHECK(ptr);
         for (size_t i = 0; i < oldSize; ++i) {
            newPtr[i] = ptr[i];
         }
         Data* oldPtr = ptr;
         deallocate(oldPtr, oldSize);
      }
      ptr = newPtr;
   }

} 
#endif
