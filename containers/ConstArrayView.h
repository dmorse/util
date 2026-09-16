#ifndef UTIL_CONST_ARRAY_VIEW_H
#define UTIL_CONST_ARRAY_VIEW_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/ConstArray.h>   // base class
#include <util/misc/CountedReference.h>   // member

// Forward declarations
namespace Util {
   template <typename Data> class ArraySource;
}

namespace Util {

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
   * pointer to const Data, thus providing read-only access to that slice.
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
   class ConstArrayView : public ConstArray<Data>
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

      // Prohibit copy construction
      ConstArrayView(ConstArrayView<Data> const & other) = delete;

      /**
      * Destructor.
      *
      * Releases any association with a DataSource<Data> array, and 
      * decrements the reference counter of this data source.
      */
      ~ConstArrayView();

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
      * After exit, isAllocated() will return false. Dissociation also
      * decrements the reference counter of the associated source array.
      *
      * \throw Exception if this is not associated with a source array.
      */
      void dissociate();

   protected:

      using ConstArray<Data>::data_;
      using ConstArray<Data>::capacity_;

   private:

      /// Reference to a container that owns memory referenced by this.
      CountedReference ref_;

   };

} // namespace Util

#include "ArraySource.h"
#include <util/global.h>

namespace Util {

   // Member functions

   /*
   * Default constructor.
   */
   template <typename Data>
   ConstArrayView<Data>::ConstArrayView()
    : ConstArray<Data>(),
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
      Data * ptr = const_cast<Data*>( source.cArray() );
      data_ = ptr + beginId;
      capacity_ = size;

      // Note: const_cast to non-const pointer is permissible because 
      // the ConstArray<Data> class public interface is designed to 
      // prevent modification of individual array elements.

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
   * Dissociate this view from the associated source array.
   */
   template <typename Data>
   void ConstArrayView<Data>::dissociate()
   {
      UTIL_CHECK(data_);
      UTIL_CHECK(ref_.isAssociated());

      data_ = nullptr;
      capacity_ = 0;
      ref_.dissociate(); // decrements reference counter of source array
   }

} // namespace Util
#endif
