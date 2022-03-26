#ifndef UTIL_D_ARRAY_PARAM_H
#define UTIL_D_ARRAY_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ArrayParam.h> // base class
#include <util/containers/DArray.h>  // member
#include <util/global.h>

#include <iomanip> 

namespace Util
{

   /**
   * A Parameter associated with a DArray container.
   *
   * \ingroup Param_Module
   */
   template <typename Type>
   class DArrayParam : public ArrayParam<Type>
   {

   public:

      /**
      * Constructor.
      *
      * \param label  label for array
      * \param array  associated DArray<Type> container
      * \param n  logical dimension of array
      * \param isRequired Is this a required parameter (true) or optional ?
      */
      DArrayParam(const char *label, DArray<Type>& array, int n, 
                  bool isRequired = true);

      /** 
      * Write parameter to stream.
      *
      * \param out output stream
      */
      void writeParam(std::ostream &out);

      using ArrayParam<Type>::readParam;

   protected:
  
      /**
      * Return a reference to one element of the array.
      */ 
      Type& element(int i)
      {  return (*arrayPtr_)[i]; }
 
      /**
      * Read parameter value from an input stream.
      * 
      * \param in input stream from which to read
      */
      virtual void readValue(std::istream& in);

      /**
      * Load bare parameter value from an archive.
      *
      * \param ar input archive from which to load
      */
      virtual void loadValue(Serializable::IArchive& ar);

      /**
      * Save parameter value to an archive.
      *
      * \param ar output archive to which to save
      */
      virtual void saveValue(Serializable::OArchive& ar);

      #ifdef UTIL_MPI
      /**
      * Broadcast parameter value within the ioCommunicator.
      */
      virtual void bcastValue();
      #endif

      using ArrayParam<Type>::n;
      
   private:
   
      /// Pointer to associated DArray.
      DArray<Type>* arrayPtr_;
  
   };

   /*
   * DArrayParam<Type> constructor.
   */
   template <class Type>
   DArrayParam<Type>::DArrayParam(const char *label, 
                                  DArray<Type>& array, int n, 
                                  bool isRequired)
    : ArrayParam<Type>(label, n, isRequired),
      arrayPtr_(&array)
   {}

   /*
   * Write a DArray to a parameter file.
   */
   template <class Type>
   void DArrayParam<Type>::writeParam(std::ostream &out) 
   {
      if (Parameter::isActive()) {
         if (!(arrayPtr_->isAllocated())) {
            UTIL_THROW("Cannot write unallocated DArray");
         }
         if (arrayPtr_->capacity() != n()) {
            UTIL_THROW("Error: DArray capacity != n in writeParam");
         }
         ArrayParam<Type>::writeParam(out);
      }
   }

   /*
   * Read array of values from isteam.
   */
   template <class Type>
   void DArrayParam<Type>::readValue(std::istream &in)
   {  
      if (!(arrayPtr_->isAllocated())) {
         UTIL_THROW("Cannot read unallocated DArray");
      }
      if (arrayPtr_->capacity() != n()) {
         UTIL_THROW("Error: DArray capacity < n");
      }
      ArrayParam<Type>::readValue(in);
   }

   /*
   * Load a DArray from input archive.
   */
   template <class Type>
   void DArrayParam<Type>::loadValue(Serializable::IArchive& ar)
   {  
      if (!(arrayPtr_->isAllocated())) {
         arrayPtr_->allocate(n());
      }
      ar >> *arrayPtr_;
      if (arrayPtr_->capacity() < n()) {
         UTIL_THROW("Error: DArray capacity < n");
      }
   }

   /*
   * Save a DArray to an output archive.
   */
   template <class Type>
   void DArrayParam<Type>::saveValue(Serializable::OArchive& ar)
   {  
      if (!(arrayPtr_->isAllocated())) {
         UTIL_THROW("Cannot save unallocated DArray");
      }
      if (arrayPtr_->capacity() != n()) {
         UTIL_THROW("Error: DArray capacity < n");
      }
      ar << *arrayPtr_;
   }

   #ifdef UTIL_MPI
   /*
   * Broadcast a DArray.
   */
   template <class Type>
   void DArrayParam<Type>::bcastValue()
   {  bcast<Type>(ioCommunicator(), *arrayPtr_, n(), 0); }
   #endif

} 
#endif
