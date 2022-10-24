#ifndef UTIL_F_S_ARRAY_PARAM_H
#define UTIL_F_S_ARRAY_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ArrayParam.h> // base class
#include <util/containers/FSArray.h>  // member
#include <util/global.h>

#include <iomanip> 

namespace Util
{

   /**
   * A Parameter associated with a FSArray container.
   *
   * \ingroup Param_Module
   */
   template <typename Type, int Capacity>
   class FSArrayParam : public ArrayParam<Type>
   {

   public:

      /**
      * Constructor.
      *
      * \param label  label for array
      * \param array  associated FSArray<Type, Capacity> container
      * \param n  expected logical dimension (size) of array
      * \param isRequired  Is this a required parameter (true) or optional ?
      */
      FSArrayParam(const char *label, FSArray<Type, Capacity>& array, 
                   int n, bool isRequired = true);

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
   
      /// Pointer to associated FSArray.
      FSArray<Type, Capacity>* arrayPtr_;
  
   };

   /*
   * FSArrayParam<Type, Capacity> constructor.
   */
   template <typename Type, int Capacity>
   FSArrayParam<Type, Capacity>::FSArrayParam(const char *label, 
                                  FSArray<Type, Capacity>& array, 
                                  int n,
                                  bool isRequired)
    : ArrayParam<Type>(label, n, isRequired),
      arrayPtr_(&array)
   {}

   /*
   * Write a FSArray to a parameter file.
   */
   template <typename Type, int Capacity>
   void FSArrayParam<Type, Capacity>::writeParam(std::ostream &out) const
   {
      if (Parameter::isActive()) {
         UTIL_CHECK(n() <= Capacity);
         UTIL_CHECK(n() == arrayPtr_->size());
         ArrayParam<Type>::writeParam(out);
      }
   }

   /*
   * Read array of element values from istream.
   */
   template <typename Type, int Capacity>
   void FSArrayParam<Type, Capacity>::readValue(std::istream &in)
   {  
      UTIL_CHECK(n() <= Capacity);
      arrayPtr_->clear();
      Type value;
      for (int i = 0; i < n(); ++i) {
         in >> value;
         arrayPtr_->append(value);
      }
      UTIL_CHECK(n() == arrayPtr_->size());
      ArrayParam<Type>::readEndBracket(in);
   }

   /*
   * Load an FSArray from input archive.
   */
   template <typename Type, int Capacity>
   void FSArrayParam<Type, Capacity>::loadValue(Serializable::IArchive& ar)
   {  
      UTIL_CHECK(n() <= Capacity);
      ar >> *arrayPtr_;
   }

   /*
   * Save an FSArray to an output archive.
   */
   template <typename Type, int Capacity>
   void FSArrayParam<Type, Capacity>::saveValue(Serializable::OArchive& ar)
   {  
      UTIL_CHECK(n() <= Capacity);
      ar << *arrayPtr_;
   }

   #ifdef UTIL_MPI
   /*
   * Broadcast a FSArray.
   */
   template <typename Type, int Capacity>
   void FSArrayParam<Type, Capacity>::bcastValue()
   {  bcast<Type>(ioCommunicator(), *arrayPtr_, Capacity, 0); }
   #endif

} 
#endif
