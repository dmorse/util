#ifndef UTIL_CARRAY_PARAM_H
#define UTIL_CARRAY_PARAM_H

#include <util/param/ArrayParam.h>
#include <util/global.h>

#ifdef UTIL_MPI
#include <util/mpi/MpiSendRecv.h>
#endif

#include <iomanip> 

namespace Util
{

   /**
   * A Parameter associated with a 1D C array. 
   *
   * \ingroup Param_Module
   */
   template <class Type>
   class CArrayParam : public ArrayParam<Type>
   {
   
   public:

      /**   
      * Constructor.
      *
      * \param label  label string (name of array variable)
      * \param value  associated C array (pointer to first element)
      * \param n  logical size of array
      * \param isRequired  Is this a required parameter ?
      */
      CArrayParam(const char* label, Type* value, int n, 
                  bool isRequired = true);

      using ArrayParam<Type>::writeParam;

   protected:

      using ArrayParam<Type>::readValue;
      using ArrayParam<Type>::n;

      /**
      * Return a reference to one element of the array.
      *
      * \param i element index
      */
      Type& element(int i) 
      {  return value_[i]; }
 
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
   
      /// Pointer to array (i.e., to first element)
      Type* value_;
  
   };

   /*
   * CArrayParam<Type> constructor.
   */
   template <class Type>
   CArrayParam<Type>::CArrayParam(const char *label, Type* value, int n, 
                                  bool isRequired)
    : ArrayParam<Type>(label, n, isRequired),
      value_(value)
   {}

   /*
   * Load C-array of n values from an input archive
   */
   template <class Type>
   void CArrayParam<Type>::loadValue(Serializable::IArchive& ar)
   {  ar.unpack(value_, n()); }

   /*
   * Save C-array of n values to an output archive
   */
   template <class Type>
   void CArrayParam<Type>::saveValue(Serializable::OArchive& ar)
   {  ar.pack(value_, n()); }

   #ifdef UTIL_MPI
   /*
   * Broadcast an array of n values
   */
   template <class Type>
   void CArrayParam<Type>::bcastValue()
   {  bcast<Type>(ioCommunicator(), value_, n(), 0); }
   #endif

} 
#endif
