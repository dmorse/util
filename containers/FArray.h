#ifndef UTIL_F_ARRAY_H
#define UTIL_F_ARRAY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, David Morse (morse012@um.edu)
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/ArrayIterator.h>
#include <util/containers/ConstArrayIterator.h>
#include <util/global.h>

#ifdef UTIL_MPI
#include <util/mpi/MpiTraits.h>
#include <util/mpi/MpiStructBuilder.h>
#endif

namespace Util
{

   /**
   * A fixed size, stack-allocated array.
   *
   * An FArray is a simple wraper for a fixed size, stack-allocated
   * C Array, with a capacity that is fixed at compile time. 
   *
   * When bounds checking is on (i.e., when NDEBUG is not defined), the
   * subscript operator [] checks that the index is non-negative and less
   * than the Capacity.
   *
   * Advice: Use an FArray for a small array if you know exactly how many
   * elements will be needed at compile time. Use an FSArray when you need
   * a small stack-allocated array for which a maximum capacity is known
   * at compile time, but the logical size may be less than the capacity.
   * Use a DArray or a GArray if you need an array whose size is not known
   * at compile time.
   *
   * \ingroup Array_Module
   */
   template <typename Data, int Capacity>
   class FArray
   {

   public:

      /**
      * Constructor.
      */
      FArray();

      /**
      * Copy constructor.
      *
      *\param other the FArray to be copied.
      */
      FArray(FArray<Data, Capacity> const & other);

      // Default destructor is okay.

      /**
      * Assignment, element by element.
      *
      * \param other  the RHS FArray
      */
      FArray<Data, Capacity>& operator = (FArray<Data, Capacity> const & other);

      /**
      * Return number of elements in this FArray.
      */
      int size() const;

      /**
      * Return number of elements in this FArray.
      *
      * For an FArray, size and capacity are equal.
      */
      int capacity() const;

      /**
      * Set an ArrayIterator to the beginning of this Array.
      *
      * \param iterator ArrayIterator, initialized on output.
      */
      void begin(ArrayIterator<Data> &iterator);

      /**
      * Set a ConstArrayIterator to the beginning of this Array.
      *
      * \param iterator ConstArrayIterator, initialized on output.
      */
      void begin(ConstArrayIterator<Data> &iterator) const;

      /**
      * Mimic C array subscripting.
      *
      * \param  i array index
      * \return reference to element i
      */
      Data& operator[] (int i);

      /**
      * Mimic C array subscripting.
      *
      * \param i array index
      * \return const reference to element i
      */
      Data const & operator[] (int i) const;

      /**
      * Return pointer to underlying C array.
      */
      Data* cArray();

      /**
      * Return pointer to const to underlying C array.
      */
      Data const * cArray() const;

      /**
      * Serialize a FArray to/from an Archive.
      *
      * \param ar        archive
      * \param version   archive version id
      */
      template <class Archive>
      void serialize(Archive& ar, const unsigned int version);

      /**
      * Return packed size in a MemoryArchive, in bytes.
      */
      int packedSize();

      #ifdef UTIL_MPI
      /**
      * Commit associated MPI DataType.
      */
      static void commitMpiType();
      #endif

   private:

      /// Array of Data elements.
      Data data_[Capacity];

   };

   #ifdef UTIL_MPI
   /**
   * Partial specialization of MpiTraits for FArray<Data, Capacity>.
   */
   template <typename Data, int Capacity>
   class MpiTraits< FArray<Data, Capacity> >
   {
   public:
      static MPI::Datatype type;   ///< MPI Datatype
      static bool hasType;         ///< Is the MPI type initialized?
   };

   template <typename Data, int Capacity>
   MPI::Datatype MpiTraits< FArray<Data, Capacity> >::type = MPI::BYTE;

   template <typename Data, int Capacity>
   bool MpiTraits< FArray<Data, Capacity> >::hasType = false;
   #endif

   // Member functions

   /*
   * Constructor.
   */
   template <typename Data, int Capacity> inline
   FArray<Data, Capacity>::FArray()
   #ifdef UTIL_CXX11
    : data_{}
   #endif
   {}

   /*
   * Copy constructor.
   *
   *\param other the FArray to be copied.
   */
   template <typename Data, int Capacity>
   FArray<Data, Capacity>::FArray(FArray<Data, Capacity> const & other)
   #ifdef UTIL_CXX11
    : data_{}
   #endif
   {
      for (int i = 0; i < Capacity; ++i) {
         data_[i] = other.data_[i];
      }
   }

   // Default destructor is okay.

   /*
   * Assignment, element by element.
   */
   template <typename Data, int Capacity>
   FArray<Data, Capacity>&
   FArray<Data, Capacity>::operator=(FArray<Data, Capacity> const & other)
   {
      // Check for self assignment
      if (this == &other) return *this;

      // Copy elements
      for (int i = 0; i < Capacity; ++i) {
         data_[i] = other[i];
      }
      return *this;
   }

   /*
   * Return number of elements in this FArray.
   */
   template <typename Data, int Capacity> inline
   int FArray<Data, Capacity>::size() const
   {  return Capacity; }

   /*
   * Return number of elements in this FArray.
   */
   template <typename Data, int Capacity> inline
   int FArray<Data, Capacity>::capacity() const
   { return Capacity; }

   /*
   * Set an ArrayIterator to the beginning of this Array.
   */
   template <typename Data, int Capacity> inline
   void FArray<Data, Capacity>::begin(ArrayIterator<Data> &iterator)
   {
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + Capacity);
   }

   /*
   * Set a ConstArrayIterator to the beginning of this Array.
   */
   template <typename Data, int Capacity>
   inline
   void FArray<Data, Capacity>::begin(ConstArrayIterator<Data> &iterator)
   const
   {
      iterator.setCurrent(data_);
      iterator.setEnd(data_ + Capacity);
   }

   /*
   * Subscript operator (returns an element).
   */
   template <typename Data, int Capacity> inline
   Data& FArray<Data, Capacity>::operator[] (int i)
   {
      UTIL_ASSERT(i < Capacity);
      UTIL_ASSERT(i >= 0);
      return data_[i];
   }

   /*
   * Subscript operator (returns an element by const reference).
   */
   template <typename Data, int Capacity> inline
   Data const & FArray<Data, Capacity>::operator[] (int i) const
   {
      UTIL_ASSERT(i < Capacity);
      UTIL_ASSERT(i >= 0 );
      return data_[i];
   }

   /*
   * Return pointer to underlying C array.
   */
   template <typename Data, int Capacity> inline
   Data* FArray<Data, Capacity>::cArray()
   {  return data_; }

   /*
   * Return pointer to const to underlying C array.
   */
   template <typename Data, int Capacity>
   Data const * FArray<Data, Capacity>::cArray() const
   {  return data_; }

   /*
   * Serialize a FArray to/from an Archive.
   */
   template <typename Data, int Capacity>
   template <class Archive>
   void FArray<Data, Capacity>::serialize(Archive& ar,
                                          const unsigned int version)
   {
      for (int i = 0; i < Capacity; ++i) {
         ar & data_[i];
      }
   }

   /*
   * Packed size of FArray in a MemoryArchive, in bytes.
   */
   template <typename Data, int Capacity>
   int FArray<Data, Capacity>::packedSize()
   {  return Capacity*sizeof(Data); }

   #ifdef UTIL_MPI
   /*
   * Commit associated MPI Datatype.
   */
   template <typename Data, int Capacity>
   void FArray<Data, Capacity>::commitMpiType()
   {
      if (!MpiTraits< FArray<Data, Capacity > >::hasType) {
         MpiStructBuilder       builder;
         FArray<Data, Capacity> object;

         // One member with Capacity elements (a builder can hold at
         // most MpiStructBuilder::MaxNBlock members)
         builder.setBase(&object);
         builder.addMember(object.data_, MpiTraits<Data>::type, Capacity);
         builder.commit(MpiTraits< FArray<Data, Capacity> >::type);
         MpiTraits< FArray<Data, Capacity> >::hasType = true;
      }
   }
   #endif

}
#endif
