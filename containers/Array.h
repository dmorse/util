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
   * An Array is a sequence container that wraps a dynamically allocated 
   * C array, and supports random read-write access via an overloaded 
   * subscript [] operator [].
   *
   * The Array class template is designed to be used as only as a base 
   * class that provides an interface to an array, but does not provide 
   * functions for memory management.  The Array template has a protected 
   * constructor and destructor to prevent direct instantiation and
   * destruction via a base class pointer, but allow creation and 
   * destruction as a subobject of a derived class. Responsibility for
   * management of the associated memory block is delegated to subclasses. 
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

      // Default constructor and destructor are protected.

      // Prohibit copy construction
      Array(Array const & other) = delete;

      // Prohibit assignment
      Array<Data>& operator = (Array<Data> const & other) = delete;

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

      /**
      * Does this array have associated data?
      *
      * Return false if the pointer to data is null, true otherwise.
      */
      bool isAllocated() const;

      /**
      * Return logical size of array.
      *
      * Currently, size() == capacity(), always.
      *
      * \return number of elements in array
      */
      int size() const;

      /**
      * Return allocated size.
      *
      * \return number of elements allocated in array
      */
      int capacity() const;

   protected:

      /// Pointer to an array of Data elements.
      Data* data_;

      /// Allocated size of the data_ array.
      int capacity_;

      /**
      * Constructor (protected to prevent direct instantiation).
      */
      Array();

      /**
      * Destructor (protected to prevent direct destruction).
      */
      ~Array();

   };

   // Member function definitions

   /*
   * Default constructor (protected).
   *
   * Subclasses are responsible for memory management.
   */
   template <typename Data> inline
   Array<Data>::Array()
    : data_(nullptr),
      capacity_(0)
   {}

   /*
   * Destructor (do-nothing, protected).
   *
   * Subclasses are responsible for memory management.
   */
   template <typename Data> inline
   Array<Data>::~Array()
   {}

   /*
   * Set an ArrayIterator to begin this Array.
   */
   template <typename Data> inline 
   void Array<Data>::begin(ArrayIterator<Data> &iterator)
   {
      assert(data_);
      assert(capacity_ > 0);
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + capacity_);
   }

   /*
   * Set a ConstArrayIterator to begin this Array.
   */
   template <typename Data> inline 
   void Array<Data>::begin(ConstArrayIterator<Data> &iterator) const
   {
      assert(data_);
      assert(capacity_ > 0);
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + capacity_);
   }

   /*
   * Get an element by reference (C-array subscripting)
   */
   template <typename Data> inline 
   Data& Array<Data>::operator [] (int i)
   {
      assert(data_);
      assert(i >= 0);
      assert(i < capacity_);
      return *(data_ + i);
   }

   /*
   * Get an element by const reference (C-array subscripting)
   */
   template <typename Data> inline 
   Data const & Array<Data>::operator [] (int i) const
   {
      assert(data_);
      assert(i >= 0 );
      assert(i < capacity_);
      return *(data_ + i);
   }

   /*
   * Get a pointer to the underlying C array.
   */
   template <typename Data> inline 
   Data* Array<Data>::cArray()
   {  return data_; }

   /*
   * Get a pointer to const to the underlying C array.
   */
   template <typename Data> inline 
   Data const * Array<Data>::cArray() const
   {  return data_; }

   /*
   * Return true iff the data pointer is non-null, false otherwise.
   */
   template <typename Data> inline
   bool Array<Data>::isAllocated() const
   {  return (bool)data_; }

   /*
   * Return logical size of this array.
   */
   template <typename Data> inline 
   int Array<Data>::size() const
   {  return capacity_; }

   /*
   * Return allocated capacity.
   */
   template <typename Data> inline 
   int Array<Data>::capacity() const
   {  return capacity_; }

}
#endif
