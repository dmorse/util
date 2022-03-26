#ifndef UTIL_F_ARRAY_PARAM_H
#define UTIL_F_ARRAY_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ArrayParam.h>
#include <util/containers/FArray.h>
#include <util/global.h>

#include <iomanip> 

namespace Util
{

   /**
   * A Parameter associated with a FArray container.
   *
   * \ingroup Param_Module
   */
   template <class Type, int N>
   class FArrayParam : public ArrayParam<Type>
   {
   
   public:

      /**
      * Constructor.
      *
      * \param label  label string for parameter file
      * \param array  associated FArray variable
      * \param isRequired  Is this a required parameter?
      */
      FArrayParam(const char *label, FArray<Type, N>& array, 
                  bool isRequired = true);

      using ArrayParam<Type>::writeParam;

   protected:
   
      using ArrayParam<Type>::readValue;

      /**
      * Return one element by reference.
      *
      * \param i array element index
      */ 
      Type& element(int i)
      {   return (*arrayPtr_)[i]; }

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

   private:
   
      /// Pointer to associated FArray.
      FArray<Type, N>* arrayPtr_;
   
   };

   /*
   * FArrayParam<Type, N> constructor.
   */
   template <class Type, int N>
   FArrayParam<Type, N>::FArrayParam(const char *label, 
                                     FArray<Type, N>& array, 
                                     bool isRequired)
    : ArrayParam<Type>(label, N, isRequired),
      arrayPtr_(&array)
   {}

   /*
   * Load a FArray from input archive.
   */
   template <class Type, int N>
   void FArrayParam<Type, N>::loadValue(Serializable::IArchive& ar)
   {  ar >> *arrayPtr_; }  

   /*
   * Save a FArray to an output archive.
   */
   template <class Type, int N>
   void FArrayParam<Type, N>::saveValue(Serializable::OArchive& ar)
   {  ar << *arrayPtr_; }

   #ifdef UTIL_MPI
   /*
   * Broadcast a FArray.
   */
   template <class Type, int N>
   void FArrayParam<Type, N>::bcastValue()
   {  bcast<Type>(ioCommunicator(), &((*arrayPtr_)[0]), N, 0); }
   #endif

} 
#endif
