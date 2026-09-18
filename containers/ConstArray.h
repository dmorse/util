#ifndef UTIL_CONST_ARRAY_H
#define UTIL_CONST_ARRAY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/ConstArrayIterator.h>
#include <util/global.h>

namespace Util
{

   /**
   * Read-only array container class template.
   *
   * An ConstArray<Data> is a sequence that supports random read-only 
   * access to elements via a operator [] that returns a const reference, 
   * or via a ConstArrayIterator. Similar to an Array, without any of
   * the functions that provide write access to element values.
   *
   * The ConstArray class template is designed to be used as only as a 
   * base class, and does not provide functions for memory management. 
   * The ConstArray template has a protected constructor and destructor
   * to prevent direct direct construction or destruction, but to allow
   * construction and destruction as a subojbect of a derived class.
   *
   * When compiled in debug mode (i.e., when NDEBUG is not defined) the
   * subscript operator [] checks the validity of the element index.
   *
   * \ingroup Array_Module
   */
   template <typename Data>
   class ConstArray
   {

   public:

      // Protected copy constructor and destructor (see below).

      // Prohibit copy construction
      ConstArray<Data>& 
      operator = (ConstArray<Data> const & other) = delete;

      // Prohibit assignment
      ConstArray(ConstArray const & other) = delete;

      /**
      * Set a const iterator to begin this ConstArray.
      *
      * On return, iterator points to the first element of the array, and
      * the iterator end pointer is set to one past the last element.
      *
      * \param iterator ConstArrayIterator, initialized on output
      */
      void begin(ConstArrayIterator<Data>& iterator) const;

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
      * Return logical size of this array.
      *
      * Currently, capacity() == size(), always.
      *
      * \return number of elements in this array
      */
      int size() const;

      /**
      * Return allocated size of this array.
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
      *
      * Subclasses have responsibility for memory management.
      */
      ConstArray();

      /**
      * Destructor (protected to prevent direct destruction).
      */
      ~ConstArray();

   };

   /*
   * Default constructor.
   */
   template <typename Data> inline
   ConstArray<Data>::ConstArray()
    : data_(nullptr),
      capacity_(0)
   {}

   /*
   * Destructor (do-hothing, and protected).
   *
   * Subclasses are responsible for memory management.
   */
   template <typename Data>
   ConstArray<Data>::~ConstArray()
   {}

   /*
   * Return true iff the data pointer is non-null, false otherwise.
   */
   template <typename Data> inline
   bool ConstArray<Data>::isAllocated() const
   {  return (bool)data_; }

   /*
   * Return logical size of this array.
   */
   template <typename Data> inline 
   int ConstArray<Data>::size() const
   {  return capacity_; }

   /*
   * Return allocated capacity.
   */
   template <typename Data> inline 
   int ConstArray<Data>::capacity() const
   {  return capacity_; }

   /*
   * Set a ConstArrayIterator to begin this ConstArray.
   */
   template <typename Data> inline 
   void ConstArray<Data>::begin(ConstArrayIterator<Data> &iterator) const
   {
      assert(data_);
      assert(capacity_ > 0);
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + capacity_);
   }

   /*
   * Get an element by const reference (C-array subscripting)
   */
   template <typename Data> inline 
   Data const & ConstArray<Data>::operator [] (int i) const
   {
      assert(data_);
      assert(i >= 0 );
      assert(i < capacity_);
      return *(data_ + i);
   }

   /*
   * Get a pointer to const to the underlying C array.
   */
   template <typename Data> inline 
   Data const * ConstArray<Data>::cArray() const
   {  return data_; }

}
#endif
