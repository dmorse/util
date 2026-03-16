#ifndef UTIL_D_ARRAY_H
#define UTIL_D_ARRAY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/Array.h>
#include <util/misc/Memory.h>
#include <util/global.h>

namespace Util
{

   /**
   * Dynamically allocatable contiguous array template.
   *
   * A DArray wraps a dynamically allocated C Array, and stores the 
   * capacity of the array. A DArray can be allocated, deallocated or
   * reallocated (i.e., resized and moved) by member functions.j
   *
   * The Array<Data> base class provides bounds checking when compiled
   * in debug mode. 
   *
   * \ingroup Array_Module
   */
   template <typename Data>
   class DArray : public Array<Data>
   {

   public:

      /**
      * Default constructor.
      */
      DArray();

      /**
      * Allocating constructor.
      *
      * \param capacity  number of elements to allocate
      */
      DArray(int capacity);

      /**
      * Copy constructor.
      *
      * Allocates new memory and copies all elements by value.
      *
      * \param other  the DArray to be copied
      */
      DArray(DArray<Data> const & other);

      /**
      * Destructor.
      *
      * Deletes underlying C array, if allocated previously.
      */
      virtual ~DArray();

      /**
      * Assignment operator.
      *
      * Copies all elements. The other DArrray must be allocated. If this
      * DArray is not allocated, the function allocates it before copying
      * all elements.  If this and the other DArray are both allocated, 
      * the capacities must be exactly equal on entry.
      *
      * \throw Exception if other DArray is not allocated
      * \throw Exception if DArrays are allocated with unequal capacities
      *
      * \param other  the other (RHS) DArray
      */
      DArray<Data>& operator = (DArray<Data> const & other);

      /**
      * Allocate the underlying C array.
      *
      * \throw Exception if the DArray is already allocated
      *
      * \param capacity  number of elements to allocate
      */
      void allocate(int capacity);

      /**
      * Dellocate the underlying C array.
      *
      * \throw Exception if the DArray is not allocated
      */
      void deallocate();

      /**
      * Reallocate the underlying C array and copy to new location.
      *
      * The array is reallocated and copied to a new location if the new 
      * capacity, given by the capacity parameter, is greater than the 
      * existing array capacity. Nothing is done if the new and old 
      * capacities are equal. An Exception is thrown if the new capacity
      * is less than the old capacity. 
      *
      * \param capacity  number of elements for which to allocate space
      */
      void reallocate(int capacity);

      /**
      * Return true if this DArray has been allocated, false otherwise.
      */
      bool isAllocated() const;

      /**
      * Serialize a DArray to/from an Archive.
      *
      * \param ar       archive
      * \param version  archive version id
      */
      template <class Archive>
      void serialize(Archive& ar, const unsigned int version);

   protected:

      using Array<Data>::data_;
      using Array<Data>::capacity_;

   };

   // Member function definitions

   /*
   * Default constructor.
   */
   template <typename Data>
   DArray<Data>::DArray()
    : Array<Data>()
   {}

   /*
   * Allocating constructor.
   */
   template <typename Data>
   DArray<Data>::DArray(int capacity)
    : Array<Data>()
   {  allocate(capacity); }

   /*
   * Copy constructor.
   *
   * Allocates memory and copies all elements by value.
   *
   *\param other the DArray to be copied.
   */
   template <typename Data>
   DArray<Data>::DArray(DArray<Data> const & other)
    : Array<Data>()
   {
      if (!other.isAllocated()) {
         UTIL_THROW("Other DArray must be allocated.");
      }
      Memory::allocate(data_, other.capacity_);
      capacity_ = other.capacity_;
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other.data_[i];
      }
   }

   /*
   * Destructor.
   */
   template <typename Data>
   DArray<Data>::~DArray()
   {
      if (isAllocated()) {
         Memory::deallocate<Data>(data_, capacity_);
         capacity_ = 0;
      }
   }

   /*
   * Assignment, element-by-element.
   *
   * This operator will allocate memory if not allocated previously.
   */
   template <typename Data>
   DArray<Data>& DArray<Data>::operator = (DArray<Data> const & other)
   {
      // Check for self assignment
      if (this == &other) return *this;

      // Precondition - require that other (RHS) array is allocated
      if (!other.isAllocated()) {
         UTIL_THROW("Other DArray must be allocated.");
      }

      // Allocate this (LHS) array if necessary
      if (!isAllocated()) {
         allocate(other.capacity());
      }

      // Require equal capacities 
      if (capacity_ != other.capacity_) {
         UTIL_THROW("Cannot assign DArrays of unequal capacity");
      }

      // Copy all elements
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }

      return *this;
   }

   /*
   * Allocate the underlying C array.
   */
   template <typename Data>
   void DArray<Data>::allocate(int capacity)
   {
      if (capacity <= 0) {
         UTIL_THROW("Attempt to allocate with capacity <= 0");
      }
      if (isAllocated()) {
         UTIL_THROW("Attempt to re-allocate a DArray");
      }
      Memory::allocate<Data>(data_, capacity);
      capacity_ = capacity;
   }

   /*
   * Deallocate the underlying C array.
   */
   template <typename Data>
   void DArray<Data>::deallocate()
   {
      if (!isAllocated()) {
         UTIL_THROW("Array is not allocated");
      }
      Memory::deallocate<Data>(data_, capacity_);
      capacity_ = 0;
   }

   /*
   * Reallocate and copy the underlying C array.
   */
   template <typename Data>
   void DArray<Data>::reallocate(int capacity)
   {
      UTIL_CHECK(capacity >= 0);
      if (capacity == capacity_) return;
      UTIL_CHECK(capacity > capacity_);
      if (isAllocated()) {
         Memory::reallocate<Data>(data_, capacity_, capacity);
      } else {
         Memory::allocate<Data>(data_, capacity);
      }
      capacity_ = capacity;
   }

   /*
   * Return true if the DArray has been allocated, false otherwise.
   */
   template <typename Data>
   inline bool DArray<Data>::isAllocated() const
   {  return (bool)data_; }

   /*
   * Serialize a DArray to/from an Archive.
   */
   template <typename Data>
   template <class Archive>
   void DArray<Data>::serialize(Archive& ar, const unsigned int version)
   {
      int capacity;
      if (Archive::is_saving()) {
         capacity = capacity_;
      }
      ar & capacity;
      if (Archive::is_loading()) {
         if (!isAllocated()) {
            if (capacity > 0) {
               allocate(capacity);
            }
         } else {
            if (capacity != capacity_) {
               UTIL_THROW("Inconsistent DArray capacities");
            }
         }
      }
      if (isAllocated()) {
         for (int i = 0; i < capacity_; ++i) {
            ar & data_[i];
         }
      }
   }

}
#endif
