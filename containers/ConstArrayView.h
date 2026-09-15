#ifndef UTIL_CONST_ARRAY_VIEW_H
#define UTIL_CONST_ARRAY_VIEW_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/misc/CountedReference.h>   // member
#include <util/global.h>

namespace Util {

   // Forward Declaration
   template <typename Data> class ArraySource;

   /**
   * A read-only view of a slice of another array.
   *
   * A ConstArrayView is a sequence that supports read-only random access
   * via an overloaded operator [], and that wraps an underlying C array
   * that it does not own.
   *
   * A ConstArrayView<Data> object may access a slice of an associated
   * instance of ArraySource<Data>, hereafter referred to as the source
   * array. The address of the beginning of the slice is stored as a
   * Data const * pointer, thus providing read-only access to that slice.
   * This pair of data structures implements a reference counting scheme 
   * that signals an error at run time in  response to any action that 
   * would create a dangling reference, i.e., in response to deletion of 
   * a source array that is still referred to by one or more views.
   *
   * When compiled in debug mode (i.e., when NDEBUG is not defined), the
   * subscript operator [] checks the validity of the element index.
   *
   * \ingroup Array_Module
   * \ingroup Util_Containers_Module
   */
   template <typename Data>
   class ConstArrayView
   {

   public:

      /**
      * Data type of each array element.
      */
      using ValueType = Data;

      /**
      * Constructor.
      */
      ConstArrayView();

      /**
      * Destructor.
      *
      * Releases any association with a DataSource<Data> array, and 
      * decrements the reference counter of this data source.
      */
      ~ConstArrayView();

      // Prohibit copy construction
      ConstArrayView(ConstArrayView<Data> const & other) = delete;

      // Prohibit assignment
      ConstArrayView<Data>& 
      operator = (ConstArrayView<Data> const & other) = delete;

      /**
      * Associate this object with a slice of a source array.
      *
      * This associates this object a slice of a source array that is an 
      * instance of ArraySource<Data>.
      *
      * \throw Exception if this array is already associated.
      * \throw Exception if other array is not allocated on entry.
      *
      * \param other  parent array that owns the data
      * \param beginId  index in of source array at which slice begins
      * \param size  number of elements in the slice
      */
      void associate(ArraySource<Data> const & source, 
                     int beginId, int size);

      /**
      * Associate this object with all of a source array.
      *
      * This function associates this ConstArrayView with all of a source
      * array. This is equivalent to associate(other, 0, other.size()).
      *
      * \throw Exception if this array is allocated
      * \throw Exception if source array is not a data owner
      *
      * \param source  array that owns the data
      */
      void associate(ArraySource<Data> const & source);

      /**
      * Dissociate this object from an associated source array.
      *
      * After exit, isAssociated() will all return false. Dissociation
      * also decrements the reference counter of the associated source.
      *
      * \throw Exception if this is not associated with a source array.
      */
      void dissociate();

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
      * Get an element by const reference.
      *
      * Mimics C-array subscripting.
      *
      * \param i array index
      * \return const reference to element i
      */
      Data const & operator [] (int i) const;

      /**
      * What is the size of the associated array slice?
      */
      int size() const;

      /**
      * Is this view associated with a source array?
      */
      bool isAssociated() const;

      /**
      * Get a pointer to the underlying const C-array.
      */
      Data const * cArray() const;

   private:

      // Read-only pointer to an associated array slice.
      Data const * data_;

      // Size of the array slice (number of elements).
      int size_;

      /// Reference to a container that owns memory referenced by this.
      CountedReference ref_;

   };

   // Inline member function definitions

   /*
   * Get an element by const reference (C-array subscripting)
   */
   template <typename Data> inline 
   Data const & ConstArrayView<Data>::operator [] (int i) const
   {
      assert(data_);
      assert(i >= 0 );
      assert(i < size_);
      return *(data_ + i);
   }

   /*
   * What is the size of the associated slice?
   */
   template <typename Data> inline
   int ConstArrayView<Data>::size() const
   {  return size_; }

   /*
   * Is this view associated with a source array ?
   */
   template <typename Data> inline
   bool ConstArrayView<Data>::isAssociated() const
   {  return ((bool) data_ && ref_.isAssociated()); }

   /*
   * Get the pointer to the underlying C array.
   */
   template <typename Data> inline
   Data const * ConstArrayView<Data>::cArray() const
   {  return data_; }

   // Non-inline member functions

   /*
   * Default constructor.
   */
   template <typename Data>
   ConstArrayView<Data>::ConstArrayView()
    : data_(nullptr),
      size_(0),
      ref_()
   {}

   /*
   * Destructor.
   */
   template <typename Data>
   ConstArrayView<Data>::~ConstArrayView()
   {
      if (ref_.isAssociated()) {
         ref_.dissociate(); // decrements counter of source array
      } 
   }

   /*
   * Associate this object with a slice of an ArraySource.
   */
   template <typename Data>
   void ConstArrayView<Data>::associate(ArraySource<Data> const & source,
                                        int beginId, int size)
   {
      UTIL_CHECK(source.isAllocated());
      UTIL_CHECK(beginId >= 0);
      UTIL_CHECK(size > 0);
      UTIL_CHECK(beginId + size <= source.size());
      UTIL_CHECK(!ref_.isAssociated());

      // Copy data pointer and size
      data_ = source.cArray() + beginId;
      size_ = size;

      // Associate ReferencecCounter base class of the source array with 
      // the CountedReference ref_ member variable of this data user.
      ref_.associate(source);

      // On exit, the ReferenceCounter of the data source is incremented
      // and the ref_ CountedReference member variable of this object
      // holds a pointer to that ReferenceCounter.
   }

   /*
   * Associate this object with all of an ArraySource<Data>.
   */
   template <typename Data>
   void ConstArrayView<Data>::associate(ArraySource<Data> const & source)
   {  associate(source, 0, source.size()); }

   /*
   * Dissociate this view from the associated source.
   */
   template <typename Data>
   void ConstArrayView<Data>::dissociate()
   {
      UTIL_CHECK(data_);
      UTIL_CHECK(ref_.isAssociated());

      data_ = nullptr;
      size_ = 0;
      ref_.dissociate(); // decrements reference counter of source array
   }

   /*
   * Set a ConstArrayIterator to begin this Array.
   */
   template <typename Data> 
   void ConstArrayView<Data>::begin(ConstArrayIterator<Data> &iterator) 
   const
   {
      assert(data_);
      assert(size_ > 0);
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + size_);
   }

} // namespace Util
#endif
