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
   * An ConstArray is a sequence that supports random read-only access
   * to elements via a operator [] that returns a const reference, or
   * via a ConstArrayIterator.
   *
   * The ConstArray class template is designed to be used as only as a 
   * base class, and does not provide functions for memory management. 
   * The ConstArray template has a protected constructor, a protected
   * destructor, and deleted copy constructor and assignment operator. 
   * As a result, an ConstArray can only be created as part of an
   * instance of a derived class, and cannot be destroyed via a base 
   * class pointer or reference.
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

      ConstArray<Data>& 
      operator = (ConstArray<Data> const & other) = delete;

      ConstArray(ConstArray const & other) = delete;

      /**
      * Return allocated size.
      *
      * \return number of elements allocated in array
      */
      int capacity() const;

      /**
      * Does this array have associated data?
      *
      * Return false if the pointer to data is null, true otherwise.
      */
      bool isAllocated() const;

      #if 0
      /**
      * Set an iterator to begin this ConstArray.
      *
      * On return, iterator points to the first element of the array, and
      * the iterator end pointer is set to one past the last element.
      *
      * \param iterator ArrayIterator, initialized on output
      */
      void begin(ArrayIterator<Data>& iterator);
      #endif

      /**
      * Set a const iterator to begin this ConstArray.
      *
      * On return, iterator points to the first element of the array, and
      * the iterator end pointer is set to one past the last element.
      *
      * \param iterator ConstArrayIterator, initialized on output
      */
      void begin(ConstArrayIterator<Data>& iterator) const;

      #if 0
      /**
      * Get an element by non-const reference.
      *
      * Mimic C-array subscripting.
      *
      * \param  i array index
      * \return non-const reference to element i
      */
      Data& operator [] (int i);
      #endif

      /**
      * Get an element by const reference.
      *
      * Mimics C-array subscripting.
      *
      * \param i array index
      * \return const reference to element i
      */
      Data const & operator [] (int i) const;

      #if 0
      /**
      * Return a pointer to the underlying C array.
      */
      Data* cArray();
      #endif

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
      * Constructor (protected to prevent direct instantiation).
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
   * Destructor (do-hothing)
   */
   template <typename Data>
   ConstArray<Data>::~ConstArray()
   {}

   /*
   * Return allocated capacity.
   */
   template <typename Data> inline 
   int ConstArray<Data>::capacity() const
   {  return capacity_; }

   /*
   * Return true iff the data pointer is non-null, false otherwise.
   */
   template <typename Data> inline
   bool ConstArray<Data>::isAllocated() const
   {  return (bool)data_; }

   #if 0
   /*
   * Set an ArrayIterator to begin this ConstArray.
   */
   template <typename Data> inline 
   void ConstArray<Data>::begin(ArrayIterator<Data> &iterator)
   {
      assert(data_);
      assert(capacity_ > 0);
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + capacity_);
   }
   #endif

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

   #if 0
   /*
   * Get an element by reference (C-array subscripting)
   */
   template <typename Data> inline 
   Data& ConstArray<Data>::operator [] (int i)
   {
      assert(data_);
      assert(i >= 0);
      assert(i < capacity_);
      return *(data_ + i);
   }
   #endif

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

   #if 0
   /*
   * Get a pointer to the underlying C array.
   */
   template <typename Data> inline 
   Data* ConstArray<Data>::cArray()
   {  return data_; }
   #endif

   /*
   * Get a pointer to const to the underlying C array.
   */
   template <typename Data> inline 
   Data const * ConstArray<Data>::cArray() const
   {  return data_; }

}
#endif
