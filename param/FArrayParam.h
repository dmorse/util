#ifndef UTIL_F_ARRAY_PARAM_H
#define UTIL_F_ARRAY_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ArrayParam.h> // base class
#include <util/containers/FArray.h>  // member
#include <util/global.h>

#include <iomanip> 

namespace Util
{

   /**
   * A Parameter associated with a FArray container.
   *
   * \ingroup Param_Module
   */
   template <typename Type, int Capacity>
   class FArrayParam : public ArrayParam<Type>
   {

   public:

      /**
      * Constructor.
      *
      * \param label  label for array
      * \param array  associated FArray<Type, Capacity> container
      * \param isRequired  Is this a required parameter (true) or optional ?
      */
      FArrayParam(const char *label, FArray<Type, Capacity>& array, 
                  bool isRequired = true);

      /** 
      * Write parameter to stream.
      *
      * \param out output stream
      */
      void writeParam(std::ostream &out) const;

      using ArrayParam<Type>::readParam;

   protected:
  
      /**
      * Return a reference to one element of the array (non-const).
      */ 
      Type& element(int i)
      {  return (*arrayPtr_)[i]; }
 
      /**
      * Return a reference to one element of the array (const).
      */ 
      Type const & element(int i) const
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
   
      /// Pointer to associated FArray.
      FArray<Type, Capacity>* arrayPtr_;
  
   };

   /*
   * FArrayParam<Type, Capacity> constructor.
   */
   template <typename Type, int Capacity>
   FArrayParam<Type, Capacity>::FArrayParam(const char *label, 
                                  FArray<Type, Capacity>& array, 
                                  bool isRequired)
    : ArrayParam<Type>(label, Capacity, isRequired),
      arrayPtr_(&array)
   {}

   /*
   * Write a FArray to a parameter file.
   */
   template <typename Type, int Capacity>
   void FArrayParam<Type, Capacity>::writeParam(std::ostream &out) const
   {
      if (Parameter::isActive()) {
         if (Capacity != n()) {
            UTIL_THROW("Error: FArray capacity != n in writeParam");
         }
         ArrayParam<Type>::writeParam(out);
      }
   }

   /*
   * Read array of values from isteam.
   */
   template <typename Type, int Capacity>
   void FArrayParam<Type, Capacity>::readValue(std::istream &in)
   {  
      if (Capacity != n()) {
         UTIL_THROW("Error: FArray capacity != n");
      }
      ArrayParam<Type>::readValue(in);
   }

   /*
   * Load a FArray from input archive.
   */
   template <typename Type, int Capacity>
   void FArrayParam<Type, Capacity>::loadValue(Serializable::IArchive& ar)
   {  
      if (Capacity != n()) {
         UTIL_THROW("Error: FArray capacity != n");
      }
      ar >> *arrayPtr_;
   }

   /*
   * Save a FArray to an output archive.
   */
   template <typename Type, int Capacity>
   void FArrayParam<Type, Capacity>::saveValue(Serializable::OArchive& ar)
   {  
      if (Capacity != n()) {
         UTIL_THROW("Error: FArray capacity != n");
      }
      ar << *arrayPtr_;
   }

   #ifdef UTIL_MPI
   /*
   * Broadcast a FArray.
   */
   template <typename Type, int Capacity>
   void FArrayParam<Type, Capacity>::bcastValue()
   {  bcast<Type>(ioCommunicator(), *arrayPtr_, Capacity, 0); }
   #endif

} 
#endif
