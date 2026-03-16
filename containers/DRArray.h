#ifndef UTIL_DR_ARRAY_H
#define UTIL_DR_ARRAY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/Array.h>        // base class
#include <util/misc/ReferenceCounter.h>   // member
#include <util/misc/CountedReference.h>   // member
#include <util/global.h>

namespace Util {

   /**
   * Array that can own or reference a dynamically allocated C array.
   *
   * A DRArray<Data> object wraps a dynamically allocated C array with
   * elements of type Data, and stores the array capacity. A DRArray may
   * either own a C array that it is responsible for de-allocating, or it
   * may reference a slice of an array that is owned by another DRArray.
   * In either case, individual elements may be accessed via a subscript
   * operator (an overloaded operator []) that is inherited from the
   * Array<Data> base class.  Member functions for memory management allow
   * a DRArray to allocate or deallocate a C array that it owns, or to
   * become associated with or dissociated from an array slice that it
   * does not own.
   *
   * A DRArray may be in any of three states:
   *
   *   (1) Unallocated: In this state, there is no associated memory,
   *   so capacity() returns 0, while isAllocated(), isOwner() and
   *   isAssociated() all return false.
   *
   *   (2) A data owner: In this case, this object owns a C array that
   *   it is responsible for de-allocating. In this state, capacity()
   *   returns a positive integer, isAllocated() and isOwner() return
   *   true, and isAssociated() returns false.
   *
   *   (3) A data user: In this case, this object has a pointer to a C
   *   array that is owned by a different DRArray object. We describe this
   *   by saying that this DRArray (the data user) is "associated" with a
   *   C array that is owned by another object (the data owner), or that
   *   the data user "references" that array. In this state, capacity()
   *   returns a positive value, isAllocated() and isAssociated() return
   *   true, and isOwner() returns false.
   *
   * A DRArray that owns a C array that is referenced by one or more other
   * associated DRArray objects maintains a count of how many other such
   * objects reference its data. This counter is automatically incremented
   * when a reference is created and decremented when an existing reference
   * is destroyed.
   *
   * It is a logical error to invoke the deallocate() member function of
   * a DRArray that is unallocated or that references data that it does
   * not own. In either case, an Exception is thrown.  It is also an error
   * to attempt to deallocate a C array that is owned by one DRArray but
   * also referenced by one or more other associated DRArray objects.
   * Attempts to deallocate such a shared array will either cause an
   * Exception to be thrown, if deallocation is attempted by invoking the
   * deallocate() member function, or cause an error message to be written
   * to std::cout, if deallocation is attempted during destruction of the
   * data owner object. Such references must instead be released by
   * invoking the dissociate() member function of every associated data
   * user object before the data owner is destroyed.
   *
   * \ingroup Array_Module
   */
   template <typename Data>
   class DRArray : public Array<Data>
   {

   public:

      /**
      * Default constructor.
      */
      DRArray();

      /**
      * Allocating constructor.
      *
      * This function calls allocate(capacity) internally.
      *
      * \param capacity number of elements to allocate
      */
      DRArray(int capacity);

      /**
      * Copy constructor.
      *
      * \param other  the DRArray to be copied
      */
      DRArray(DRArray<Data> const & other);

      /**
      * Destructor.
      *
      * Deletes any C array that is owned by this object, and releases any
      * association with a C Array that is referred to but not owned by
      * this object. If this object owns an array that is referred to by
      * one or more other DRArray objects, an error message is written to
      * std::cout.
      */
      ~DRArray();

      /**
      * Assignment from another DRArray<Data> container.
      *
      * Performs a deep copy, by copying values of all elements of another
      * DRArray<Data> container. If this LHS array is already allocated
      * on entry, it must have the same capacity as the other RHS array.
      * If this LHS array is not allocated on entry, required memory is
      * allocated before copying values. After exit, isAllocated() and
      * isOwner() return true, while isAssociated() returns false.
      *
      * \throw Exception if other array is not allocated
      * \throw Exception if arrays are allocated with unequal capacities
      *
      * \param other  array container on RHS of assigment (input)
      */
      DRArray<Data>& operator = (DRArray<Data> const & other);

      /**
      * Assignment from an Array<Data> container.
      *
      * Performs a deep copy, by copying values of all elements of an
      * Array<Data> container. If this (LHS) array is already allocated
      * on entry, it must have the same capacity as the other (RHS) array.
      * If this LHS array is not allocated on entry, required memory is
      * allocated before copying values. After exit, isAllocated() and
      * isOwner() return true, while isAssociated() returns false.
      *
      * \throw Exception if other array is not allocated
      * \throw Exception if arrays are allocated with unequal capacities
      *
      * \param other  array container on RHS of assigment (input)
      */
      DRArray<Data>& operator = (Array<Data> const & other);

      /**
      * Allocate an underlying C array, which this container then owns.
      *
      * On entry, this object must be unallocated, i.e., it must not have
      * data that it either owns or references.  After exit, isAllocated()
      * and isOwner() will return true, while isAssociated() will return
      * false.
      *
      * \throw Exception if this array is allocated on entry.
      *
      * \param capacity number of elements to allocate
      */
      void allocate(int capacity);

      /**
      * Dellocate an underlying C array that is owned by this container.
      *
      * After exit, isAllocated(), isOwner(), and isAssociated() will
      * all return false.
      *
      * \throw Exception if this object does not own data.
      */
      void deallocate();

      /**
      * Associate this object with a slice of a different DRArray.
      *
      * On entry, this object must be not be allocated, i.e., it must
      * not have data that it either owns or references.  After exit,
      * isAllocated() and isAssociated() will return true, while isOwner()
      * will return false.
      *
      * \throw Exception if this array is allocated on entry.
      *
      * \param arr  parent array that owns the data
      * \param beginId  index in the parent array at which this array starts
      * \param capacity  number of elements associated with this container
      */
      void associate(DRArray<Data>& arr, int beginId, int capacity);

      /**
      * Dissociate this object from an externally owned array slice.
      *
      * After exit, isAllocated(), isOwner(), and isAssociated() will
      * all return false.
      *
      * \throw Exception if this is not associated with external data
      */
      void dissociate();

      /**
      * Return true if this container has data, false otherwise.
      *
      * A DRArray is considered allocated if it has non-null pointer
      * to a C array, which may either be an array that it owns or a
      * slice of an array that is owned by another DRArray object.
      */
      bool isAllocated() const;

      /**
      * Does this container own a dynamically allocated C array?
      *
      * If isAllocated() is false, isOwner() is also false.
      * If isAllocated() is true, either isOwner() or isAsssociated()
      * must be true, but not both.
      */
      bool isOwner() const;

      /**
      * Is this container associated with a C array it does not own?
      *
      * If isAllocated() is false, isAssociated() is also false.
      */
      bool isAssociated() const;

   protected:

      using Array<Data>::data_;
      using Array<Data>::capacity_;

      /// Counter for any containers that reference data owned by this.
      ReferenceCounter refCounter_;

      /// Reference to a container that owns memory referenced by this.
      CountedReference ref_;

   };

   // Inline member function definitions

   /*
   * Does this DRArray have data (either owned or associated) ?
   */
   template <typename Data> inline
   bool DRArray<Data>::isAllocated() const
   {  return (bool)data_; }

   /*
   * Does this object own data?
   */
   template <typename Data> inline
   bool DRArray<Data>::isOwner() const
   {  return ((bool) data_ && !ref_.isAssociated()); }

   /*
   * Does this object reference data that it does not own?
   */
   template <typename Data> inline
   bool DRArray<Data>::isAssociated() const
   {  return ((bool) data_ && ref_.isAssociated()); }

   // Non-inline member function definitions

   /*
   * Default constructor.
   */
   template <typename Data>
   DRArray<Data>::DRArray()
    : Array<Data>()
   {}

   /*
   * Allocating constructor.
   */
   template <typename Data>
   DRArray<Data>::DRArray(int capacity)
    : Array<Data>()
   {  allocate(capacity); }

   /*
   * Copy constructor.
   */
   template <typename Data>
   DRArray<Data>::DRArray(DRArray<Data> const & other)
    : Array<Data>()
   {
      if (!other.isAllocated()) {
         UTIL_THROW("Other DRArray must be allocated.");
      }
      allocate(other.capacity_);
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other.data_[i];
      }
   }

   /*
   * Destructor.
   */
   template <typename Data>
   DRArray<Data>::~DRArray()
   {
      if (data_) {
         if (ref_.isAssociated()) {
            ref_.dissociate();
         } else {
            if (refCounter_.hasRefs()) {
               int nRef = refCounter_.nRef();
               std::cout
                   << std::endl
                   << "Error: Destroying a DRArray that is referenced by "
                   << nRef << " other(s)" << std::endl;
            }
            Memory::deallocate<Data>(data_, capacity_);
         }
      }
      data_ = nullptr;
      capacity_ = 0;
   }

   /*
   * Assignment from another DRArray<Data> (deep copy).
   */
   template <typename Data>
   DRArray<Data>& DRArray<Data>::operator = (DRArray<Data> const & other)
   {
      // Check for self assignment
      if (this == &other) return *this;

      // Precondition - other array must be allocated
      UTIL_CHECK (other.isAllocated());

      // If this is not allocated, then allocate
      if (!isAllocated()) {
         allocate(other.capacity());
      }

      // Copy elements
      UTIL_CHECK(capacity_ == other.capacity_);
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }

      return *this;
   }

   /*
   * Assignment from an Array<Data> (deep copy).
   */
   template <typename Data>
   DRArray<Data>& DRArray<Data>::operator = (Array<Data> const & other)
   {
      // Check for self assignment
      if (dynamic_cast< Array<Data>* >(this) == &other) return *this;

      // Precondition - other array must be allocated
      UTIL_CHECK(other.capacity() > 0);

      // If this is not allocated, then allocate
      if (!isAllocated()) {
         allocate(other.capacity());
      }

      // Copy elements
      UTIL_CHECK(capacity_ == other.capacity());
      for (int i = 0; i < capacity_; ++i) {
         data_[i] = other[i];
      }

      return *this;
   }

   /*
   * Allocate an underlying C array, which this container then owns.
   */
   template <typename Data>
   void DRArray<Data>::allocate(int capacity)
   {
      if (capacity <= 0) {
         UTIL_THROW("Attempt to allocate with capacity <= 0");
      }
      if (isAllocated()) {
         UTIL_THROW("Attempt to allocate a DRArray that already has data.");
      }
      Memory::allocate<Data>(data_, capacity);
      capacity_ = capacity;
   }

   /*
   * Deallocate a C array that is owned by this container.
   */
   template <typename Data>
   void DRArray<Data>::deallocate()
   {
      UTIL_CHECK(data_);
      UTIL_CHECK(!ref_.isAssociated());
      Memory::deallocate<Data>(data_, capacity_);
      capacity_ = 0;
      UTIL_CHECK(!refCounter_.hasRefs());
   }

   /*
   * Associate this object with a slice of a different DRArray.
   */
   template <typename Data>
   void DRArray<Data>::associate(DRArray<Data>& owner,
                                 int beginId, int capacity)
   {
      UTIL_CHECK(owner.isAllocated());
      UTIL_CHECK(owner.isOwner());
      UTIL_CHECK(beginId >= 0);
      UTIL_CHECK(capacity > 0);
      UTIL_CHECK(beginId + capacity <= owner.capacity());
      UTIL_CHECK(!data_);
      UTIL_CHECK(!ref_.isAssociated());

      // Copy data pointer and capacity
      data_ = owner.cArray() + beginId;
      capacity_ = capacity;

      // Associate private ReferencecCounter of the data owner with the
      // CountedReference ref_ member variable of this data user.
      ref_.associate(owner.refCounter_);

      // On exit from CountedReference::associate, the ReferenceCounter
      // is incremented and the CountedReference has a pointer to the
      // ReferenceCounter.
   }

   /*
   * Dissociate this object from array sliced owned by another object.
   */
   template <typename Data>
   void DRArray<Data>::dissociate()
   {
      UTIL_CHECK(data_);
      UTIL_CHECK(ref_.isAssociated());

      data_ = nullptr;
      capacity_ = 0;
      ref_.dissociate();
   }

} // namespace Util
#endif
