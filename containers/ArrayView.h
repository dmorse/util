#ifndef UTIL_ARRAY_VIEW_H
#define UTIL_ARRAY_VIEW_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/Array.h>        // base class
#include <util/misc/CountedReference.h>   // member
#include <util/global.h>

// Forward declaration
namespace Util {
   template <typename Data> class ArraySource;
}

namespace Util {

   /**
   * A read-write view of an array owned by a different container.
   *
   * An ArrayView is a sequence container that supports random read-write
   * access to an underlying C array that it does not own, via an
   * overloaded subscript ([]) operator.
   *
   * An ArrayView<Data> object may access a slice of an associated
   * instance of ArraySource<Data>, hereafter referred to as the source
   * array.  This pair of data structures implements a reference counting 
   * scheme that signals an error at run time in response to any action 
   * that would create a dangling reference, i.e., in response to deletion 
   * of a source array that is still referred to by one or more views.
   *
   * When compiled in debug mode (i.e., when NDEBUG is not defined), the
   * subscript operator [] checks the validity of the element index.
   *
   * \ingroup Array_Module
   * \ingroup Util_Containers_Module
   */
   template <typename Data>
   class ArrayView : public Array<Data>
   {

   public:

      /**
      * Data type of each array element.
      */
      using ValueType = Data;

      /**
      * Constructor.
      */
      ArrayView();

      // Prohibit copy construction
      ArrayView(ArrayView<Data> const & other) = delete;

      /**
      * Destructor.
      *
      * Releases any association with a DataSource<Data> array, and 
      * decrements the reference counter of this data source.
      */
      ~ArrayView();

      // Prohibit assignment
      ArrayView<Data>& 
      operator = (ArrayView<Data> const & other) = delete;

      /**
      * Associate this object with a slice of a source array.
      *
      * Associates this object with a slice of a source array that is an 
      * instance of ArraySource<Data>.
      *
      * \throw Exception if this array is already associated.
      * \throw Exception if other array is not allocated on entry.
      *
      * \param other  parent array that owns the data
      * \param beginId  index in of source array at which slice begins
      * \param size  number of elements in the slice
      */
      void associate(ArraySource<Data> & source, 
                     int beginId, int size);

      /**
      * Associate this object with all of a source array.
      *
      * This function associates this ArrayView with all of a source
      * array. This is equivalent to associate(other, 0, other.size()).
      *
      * \throw Exception if this array is allocated
      * \throw Exception if source array is not a data owner
      *
      * \param source  array that owns the data
      */
      void associate(ArraySource<Data>& source);

      /**
      * Dissociate this object from an associated source array.
      *
      * After exit, isAssociated() will all return false. Dissociation
      * also decrements the reference counter of the associated source.
      *
      * \throw Exception if this is not associated with a source array.
      */
      void dissociate();

   protected:

      using Array<Data>::data_;
      using Array<Data>::capacity_;

   private:

      /// Reference to a container that owns memory referenced by this.
      CountedReference ref_;

   };

} // namespace Util

#include "ArraySource.h"

namespace Util {

   // Non-inline member functions

   /*
   * Default constructor.
   */
   template <typename Data>
   ArrayView<Data>::ArrayView()
    : Array<Data>(),
      ref_()
   {}

   /*
   * Destructor.
   */
   template <typename Data>
   ArrayView<Data>::~ArrayView()
   {
      if (ref_.isAssociated()) {
         ref_.dissociate(); // decrements counter of source array
      } 
   }

   /*
   * Associate this object with a slice of an ArraySource.
   */
   template <typename Data>
   void ArrayView<Data>::associate(ArraySource<Data> & source,
                                   int beginId, int size)
   {
      UTIL_CHECK(source.isAllocated());
      UTIL_CHECK(beginId >= 0);
      UTIL_CHECK(size > 0);
      UTIL_CHECK(beginId + size <= source.size());
      UTIL_CHECK(!ref_.isAssociated());

      // Copy data pointer and size
      data_ = source.cArray() + beginId;
      capacity_ = size;

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
   void ArrayView<Data>::associate(ArraySource<Data>& source)
   {  associate(source, 0, source.size()); }

   /*
   * Dissociate this view from the associated source.
   */
   template <typename Data>
   void ArrayView<Data>::dissociate()
   {
      UTIL_CHECK(data_);
      UTIL_CHECK(ref_.isAssociated());

      data_ = nullptr;
      capacity_ = 0;
      ref_.dissociate(); // decrements reference counter of source array
   }

} // namespace Util
#endif
