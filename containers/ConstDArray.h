#ifndef UTIL_CONST_D_ARRAY_H
#define UTIL_CONST_D_ARRAY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/ConstArray.h>
#include <util/misc/Memory.h>
#include <util/global.h>

namespace Util
{

   /**
   * Dynamically allocatable contiguous read-only array template.
   *
   * A ConstDArray owns a dynamically allocated C array. Read-only 
   * random access to elements is provided by the ConstArray base class. 
   * A ConstDArray can be allocated, deallocated or reallocated (i.e., 
   * resized and moved) by member functions.
   *
   * The subscript operator [] inherited from the ConstArray<Data> base
   * class provides read-only access to individual elements, with array 
   * index bound checking enabled when compiled in debug mode.
   *
   * \ingroup Array_Module
   */
   template <typename Data>
   class ConstDArray : public ConstArray<Data>
   {

   public:

      /**
      * Default constructor.
      */
      ConstDArray();

      /**
      * Allocating constructor.
      *
      * \param capacity  number of elements to allocate
      */
      ConstDArray(int capacity);

      /**
      * Copy constructor.
      *
      * Allocates new memory and copies all elements by value.
      *
      * \param other  the ConstDArray to be copied
      */
      ConstDArray(ConstDArray<Data> const & other);

      /**
      * Copy constructor, copy from Array<Data>.
      *
      * Allocates new memory and copies all elements by value.
      *
      * \param other  the DArray to be copied
      */
      ConstDArray(Array<Data> const & other);

      /**
      * Destructor.
      *
      * Deletes underlying C array, if allocated previously.
      */
      virtual ~ConstDArray();

      /**
      * Assignment from a ConstDArray<Data> container.
      *
      * Copies all elements. The other DArrray must be allocated. If this
      * ConstDArray is not allocated on entry, it is allocated before 
      * elements are copied.  If this and the other ConstDArray are both 
      * allocated on entry, the capacities must be equal on entry.
      *
      * \throw Exception if other ConstDArray is not allocated
      * \throw Exception if LHS and RHS have unequal nonzero capacities
      *
      * \param other  the other (RHS) ConstDArray
      */
      ConstDArray<Data>& operator = (ConstDArray<Data> const & other);

      /**
      * Assignment from a ConstArray<Data> container.
      *
      * Performs a deep copy, by copying values of all elements of an
      * ConstArray<Data> container. If this LHS array is already allocated
      * on entry, it must have the same capacity as the other RHS array.
      * If this LHS array is not allocated on entry, required memory is
      * allocated before elements are copied.
      *
      * \throw Exception if other array is not allocated
      * \throw Exception if this and other have unequal capacities
      *
      * \param other  array container on RHS of assigment (input)
      */
      ConstDArray<Data>& operator = (ConstArray<Data> const & other);

      /**
      * Assignment from an Array<Data> container.
      *
      * Performs a deep copy, by copying values of all elements of an
      * Array<Data> container. If this LHS array is already allocated
      * on entry, it must have the same capacity as the other RHS array.
      * If this LHS array is not allocated on entry, required memory is
      * allocated before elements are copied.
      *
      * \throw Exception if other array is not allocated
      * \throw Exception if this and other have unequal capacities
      *
      * \param other  array container on RHS of assigment (input)
      */
      ConstDArray<Data>& operator = (Array<Data> const & other);

      /**
      * Allocate the underlying C array.
      *
      * \throw Exception if the ConstDArray is already allocated
      *
      * \param capacity  number of elements to allocate
      */
      void allocate(int capacity);

      /**
      * Deallocate the underlying C array.
      *
      * \throw Exception if the ConstDArray is not allocated
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
      * Serialize a ConstDArray to/from an Archive.
      *
      * \param ar       archive
      * \param version  archive version id
      */
      template <class Archive>
      void serialize(Archive& ar, const unsigned int version);

      // Inherited functions
      using ConstArray<Data>::size;
      using ConstArray<Data>::capacity;
      using ConstArray<Data>::isAllocated;
      using ConstArray<Data>::operator [];
      using ConstArray<Data>::cArray;

   protected:

      using ConstArray<Data>::data_;
      using ConstArray<Data>::capacity_;

   };

   // Non-inline member function definitions

   /*
   * Default constructor.
   */
   template <typename Data>
   ConstDArray<Data>::ConstDArray()
    : ConstArray<Data>()
   {}

   /*
   * Allocating constructor.
   */
   template <typename Data>
   ConstDArray<Data>::ConstDArray(int capacity)
    : ConstArray<Data>()
   {  allocate(capacity); }

   /*
   * Copy constructor.
   *
   * Allocates memory and copies all elements by value.
   *
   *\param other the ConstDArray to be copied.
   */
   template <typename Data>
   ConstDArray<Data>::ConstDArray(ConstDArray<Data> const & other)
    : ConstArray<Data>()
   {
      if (!other.isAllocated()) {
         UTIL_THROW("Other ConstDArray must be allocated.");
      }
      Memory::allocate(data_, other.capacity());
      capacity_ = other.capacity();
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }
   }

   /*
   * Copy constructor, from Array<Data>.
   *
   * Allocates memory and copies all elements by value.
   *
   *\param other the DArray to be copied.
   */
   template <typename Data>
   ConstDArray<Data>::ConstDArray(Array<Data> const & other)
    : ConstArray<Data>()
   {
      if (!other.isAllocated()) {
         UTIL_THROW("Other Array must be allocated.");
      }
      Memory::allocate(data_, other.capacity());
      capacity_ = other.capacity();
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }
   }

   /*
   * Destructor.
   */
   template <typename Data>
   ConstDArray<Data>::~ConstDArray()
   {
      if (isAllocated()) {
         try {
            Memory::deallocate<Data>(data_, capacity_);
         } catch (...) {
            std::cout << "Exception in ConstDArray destructor";
         }
         data_ = nullptr;
         capacity_ = 0;
      }
   }

   /*
   * Assignment, element-by-element.
   *
   * This operator will allocate memory if not allocated previously.
   */
   template <typename Data>
   ConstDArray<Data>& 
   ConstDArray<Data>::operator = (ConstDArray<Data> const & other)
   {
      // Check for self assignment
      if (this == &other) return *this;

      // Precondition - require that other (RHS) array is allocated
      UTIL_CHECK(other.isAllocated());
      UTIL_CHECK(other.capacity() > 0);

      // Allocate this (LHS) array if necessary
      if (!isAllocated()) {
         allocate(other.capacity());
      }

      // Require equal capacities
      UTIL_CHECK (capacity_ == other.capacity_);

      // Copy all elements
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }

      return *this;
   }

   /*
   * Assignment from an ConstArray<Data> (deep copy).
   */
   template <typename Data>
   ConstDArray<Data>& 
   ConstDArray<Data>::operator = (ConstArray<Data> const & other)
   {
      // Check for self assignment
      if (dynamic_cast< ConstArray<Data>* >(this) == &other) return *this;

      // Preconditions - require that other (RHS) array is allocated
      UTIL_CHECK(other.isAllocated());
      UTIL_CHECK(other.capacity() > 0);

      // If this LHS array is not allocated, then allocate
      if (!isAllocated()) {
         allocate(other.capacity());
      }

      // Require equal capacities
      UTIL_CHECK (capacity_ == other.capacity());

      // Copy elements
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }

      return *this;
   }

   /*
   * Assignment from an Array<Data> (deep copy).
   */
   template <typename Data>
   ConstDArray<Data>& 
   ConstDArray<Data>::operator = (Array<Data> const & other)
   {
      // Check for self assignment
      //if (dynamic_cast< ConstArray<Data>* >(this) == &other) return *this;

      // Preconditions - require that other (RHS) array is allocated
      UTIL_CHECK(other.isAllocated());
      UTIL_CHECK(other.capacity() > 0);

      // If this LHS array is not allocated, then allocate
      if (!isAllocated()) {
         allocate(other.capacity());
      }

      // Require equal capacities
      UTIL_CHECK (capacity_ == other.capacity());

      // Copy elements
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }

      return *this;
   }

   /*
   * Allocate the underlying C array.
   */
   template <typename Data>
   void ConstDArray<Data>::allocate(int capacity)
   {
      UTIL_CHECK(capacity > 0);
      UTIL_CHECK(!isAllocated());
      Memory::allocate<Data>(data_, capacity);
      capacity_ = capacity;
   }

   /*
   * Deallocate the underlying C array.
   */
   template <typename Data>
   void ConstDArray<Data>::deallocate()
   {
      UTIL_CHECK(isAllocated());
      Memory::deallocate<Data>(data_, capacity_);
      capacity_ = 0;
   }

   /*
   * Reallocate and copy the underlying C array.
   */
   template <typename Data>
   void ConstDArray<Data>::reallocate(int capacity)
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
   * Serialize a ConstDArray to/from an Archive.
   */
   template <typename Data>
   template <class Archive>
   void ConstDArray<Data>::serialize(Archive& ar, 
		                     const unsigned int version)
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
               UTIL_THROW("Inconsistent ConstDArray capacities");
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
