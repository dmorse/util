#ifndef UTIL_ARRAY_H
#define UTIL_ARRAY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/ArrayIterator.h>
#include <util/containers/ConstArrayIterator.h>
#include <util/global.h>

namespace Util
{

   /**
   * Array container class template.
   *
   * An Array is a sequence that supports random access via an overloaded
   * operator [], and that wraps a dynamically allocated C array. 
   *
   * The Array class template is designed to be used as only as a base 
   * class, and does not provide functions for memory management. 
   * Instantiations of the DArray, RArray, and DRArray class templates
   * are derived from corresponding instantiations of the Array template.
   * The Array template has a protected constructor and a protected
   * destructor. As a result, an Array can only be created as part of 
   * an instance of a derived class, and cannot be destroyed via a base 
   * class pointer or reference.
   *
   * When compiled in debug mode (i.e., when NDEBUG is not defined) the
   * subscript operator [] checks the validity of the element index.
   *
   * \ingroup Array_Module
   */
   template <typename Data>
   class Array
   {

   public:

      Array<Data>& operator = (Array<Data> const & other) = delete;
      Array(Array const & other) = delete;

      /**
      * Return allocated size.
      *
      * \return number of elements allocated in array
      */
      int capacity() const;

      /**
      * Set an iterator to begin this Array.
      *
      * On return, iterator points to the first element of the array, and
      * the iterator end pointer is set to one past the last element.
      *
      * \param iterator ArrayIterator, initialized on output
      */
      void begin(ArrayIterator<Data>& iterator);

      /**
      * Set a const iterator to begin this Array.
      *
      * On return, iterator points to the first element of the array, and
      * the iterator end pointer is set to one past the last element.
      *
      * \param iterator ConstArrayIterator, initialized on output
      */
      void begin(ConstArrayIterator<Data>& iterator) const;

      /**
      * Get an element by non-const reference.
      *
      * Mimic C-array subscripting.
      *
      * \param  i array index
      * \return non-const reference to element i
      */
      Data& operator [] (int i);

      /**
      * Get an element by const reference.
      *
      * Mimics C-array subscripting.
      *
      * \param i array index
      * \return const reference to element i
      */
      Data const & operator [] (int i) const;

      /**
      * Return a pointer to the underlying C array.
      */
      Data* cArray();

      /**
      * Return pointer to const to the underlying C array.
      */
      Data const * cArray() const;

   protected:

      /// Pointer to an array of Data elements.
      Data* data_;

      /// Allocated size of the data_ array.
      int capacity_;

      /**
      * Constructor (protected to provent direct instantiation).
      */
      Array();

      /**
      * Destructor (protected to prevent direct destruction).
      */
      ~Array() = default;

   };

   /*
   * Default constructor.
   */
   template <typename Data>
   Array<Data>::Array()
    : data_(nullptr),
      capacity_(0)
   {}

   /*
   * Return allocated size.
   */
   template <typename Data>
   inline int Array<Data>::capacity() const
   {  return capacity_; }

   /*
   * Set an ArrayIterator to begin this Array.
   */
   template <typename Data>
   inline void Array<Data>::begin(ArrayIterator<Data> &iterator)
   {
      assert(data_ != 0);
      assert(capacity_ > 0);
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + capacity_);
   }

   /*
   * Set a ConstArrayIterator to begin this Array.
   */
   template <typename Data>
   inline void Array<Data>::begin(ConstArrayIterator<Data> &iterator) const
   {
      assert(data_ != 0);
      assert(capacity_ > 0);
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + capacity_);
   }

   /*
   * Get an element by reference (C-array subscripting)
   */
   template <typename Data>
   inline Data& Array<Data>::operator [] (int i)
   {
      assert(data_ != 0);
      assert(i >= 0);
      assert(i < capacity_);
      return *(data_ + i);
   }

   /*
   * Get an element by const reference (C-array subscripting)
   */
   template <typename Data>
   inline Data const & Array<Data>::operator [] (int i) const
   {
      assert(data_ != 0);
      assert(i >= 0 );
      assert(i < capacity_);
      return *(data_ + i);
   }

   /*
   * Get a pointer to the underlying C array.
   */
   template <typename Data>
   inline Data* Array<Data>::cArray()
   {  return data_; }

   /*
   * Get a pointer to const to the underlying C array.
   */
   template <typename Data>
   inline Data const * Array<Data>::cArray() const
   {  return data_; }

}
#endif
