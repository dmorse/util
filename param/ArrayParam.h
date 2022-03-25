#ifndef UTIL_ARRAY_PARAM_H
#define UTIL_ARRAY_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ParamComponent.h>
#include <util/archives/Serializable_includes.h>
#include <util/param/Label.h>
#include <util/global.h>

namespace Util
{

   /**
   * An array-valued parameter in a parameter file.
   *
   * ArrayParam is a base class for objects that read and write the value
   * of an array containing a list of parameters of the same type. The 
   * parameter file format for a parameter contains a string label followed 
   * by value of the elements of the array. 
   *
   * A ArrayParam may be required or optional element in a parameter file,
   * depending on the value of the bool isRequired parameter of the
   * constructor. An optional element becomes "active" when an entry
   * with the correct label is read from a parameter file, or when an
   * active value is loaded from an archive. By convention, a required 
   * ArrayParam is always active, even before its value is read or loaded. 
   * The bool functions isRequired() and isActive() can be used to query
   * the state of a ArrayParam.
   *
   * The overloaded saveOptional() static member functions can be used
   * to save optional parameters to an archive in a form that records
   * whether or not they are active.
   *
   * \ingroup Param_Module
   */
   class ArrayParam : public ParamComponent
   {

   public:

      // Static members

      /// Width of output field for a scalar variable.
      static const int Width = 20;

      /// Precision for io of floating point data field.
      static const int Precision = 12;

      /**
      * Save an optional parameter value to an output archive
      *
      * \param ar  output archive to which to save
      * \param value  reference to value of optional parameter
      * \param isActive  Is this parameter present in the parameter file?
      */
      template <class Type>
      static void
      saveOptional(Serializable::OArchive& ar, Type& value, bool isActive);

      /**
      * Save an optional C-array of n values to an output archive
      *
      * \param ar  output archive to which to save
      * \param ptr  pointer to first element of optional C-array parameter
      * \param n  number of elements in array
      * \param isActive  Is this parameter present in the parameter file?
      */
      template <class Type>
      static void
      saveOptionalCArray(Serializable::OArchive& ar, Type* ptr, int n,
                         bool isActive);

      /**
      * Save an optional two-dimensional C array to an output archive.
      *
      * \param ar  output archive to which to save
      * \param ptr  pointer to first element optional 2D C-array parameter
      * \param m  logical number of rows in array
      * \param n  logical number of columns in array
      * \param np  logical number of columns in array
      * \param isActive  Is this parameter present in the parameter file?
      */
      template <class Type>
      static void
      saveOptionalCArray2D(Serializable::OArchive& ar, Type* ptr, 
                           int m, int n, int np, bool isActive);

      // Non-static member functions

      /**
      * Constructor.
      *
      * \param label  label string preceding value in file format
      * \param isRequired  Is this a required parameter?
      */
      ArrayParam(const char *label, bool isRequired = true);

      /**
      * Destructor.
      */
      virtual ~ArrayParam();

      /**
      * Read a label and (if the label matches) an array of parameter values.
      *
      * The parameter file format for a ArrayParam consists of a label string
      * followed by list of values for elements in an array. The element 
      * values are read if and only if the label matches the expected value 
      * for this ArrayParam. If this ArrayParam is required and the input label 
      * does not match, an error message is printed to the log file and an
      * Exception is thrown. If the ArrayParam is not required and the input
      * label does not match, the label string is retained in an buffer for 
      * later processing by the readParam method of other ParamComponent
      * objects.
      *
      * Upon entry to this function, a label string is read into a label buffer
      * if and only if the buffer is empty. This buffer is a static member of
      * the Label class, which can retain a label between invocations of the
      * readArrayParam method of different ParamComponent objects.  Once a
      * label string is read from file, it remains in the label buffer until
      * until it is matched, at which point the buffer is cleared to allow
      * processing of the next label.
      *
      * \param in  input stream from which to read
      */
      virtual void readParam(std::istream &in);

      /**
      * Load from an archive.
      *
      * An optional ArrayParam loads the value of an isActive flag, and then
      * loads the array element values only if the isActive is true. A required
      * ArrayParam simply loads the array element values. The variable associated
      * with an optional ArrayParam must be set to its default value before
      * attempting to load the parameter. Optional parameters should be saved
      * either by using the save() method of an associated ArrayParam or by
      * using the appropriate overloaded ArrayParam::saveOptional() static
      * member function, which both use the required format.
      *
      * \param ar input archive from which to load
      */
      virtual void load(Serializable::IArchive& ar);

      /**
      * Save to an archive.
      *
      * An optional ArrayParam saves the value of the isActive flag, and then
      * saves a parameter value only if the isActive is true. A required
      * ArrayParam simply saves its value. The label string is not saved to
      * the archive.
      *
      * The overloaded static saveOptional functions can also be used to 
      * save optional parameter values in this format.
      *
      * \param ar output archive to which to save
      */
      virtual void save(Serializable::OArchive& ar);

      /**
      * Return label string.
      */
      std::string label() const;

      /**
      * Is this an optional parameter?
      */
      bool isRequired() const;

      /**
      * Is this parameter active?
      */
      bool isActive() const;

   protected:

      /// Label object that contains parameter label string.
      Label label_;

      /// Name of array (label string without opening bracket)
      std::string name_;

      /// Is this parameter required?
      bool isRequired_;

      /// Is this parameter active (always true if isRequired).
      bool isActive_;

      /// Does the label have a [ bracket appended?
      bool hasBrackets_;

      /**
      * Read parameter label from an input stream.
      *
      * \param in input stream from which to read
      */
      virtual void readLabel(std::istream& in);

      /**
      * Read parameter value from an input stream.
      *
      * \param in input stream from which to read
      */
      virtual void readValue(std::istream& in){}

      /**
      * Load bare parameter value from an archive.
      *
      * \param ar input archive from which to load
      */
      virtual void loadValue(Serializable::IArchive& ar){}

      /**
      * Save parameter value to an archive.
      *
      * \param ar output archive to which to save
      */
      virtual void saveValue(Serializable::OArchive& ar){}

      #ifdef UTIL_MPI
      /**
      * Broadcast parameter value within the ioCommunicator.
      */
      virtual void bcastValue(){}
      #endif

   };

   /*
   * Save a parameter value to an output archive
   */
   template <class Type>
   void ArrayParam::saveOptional(Serializable::OArchive& ar, 
                                Type& value, bool isActive)
   {
      ar << isActive;
      if (isActive) {
         ar & value;
      }
   }

   /*
   * Save C-array of n ptrs to an output archive
   */
   template <class Type>
   void ArrayParam::saveOptionalCArray(Serializable::OArchive& ar, 
                                      Type* ptr, int n, bool isActive)
   {
      ar << isActive;
      if (isActive) {
         ar.pack(ptr, n);
      }
   }

   /*
   * Save a two-dimensional C array to an output archive.
   */
   template <class Type> 
   void ArrayParam::saveOptionalCArray2D(Serializable::OArchive& ar, 
                                        Type* ptr, int m, int n, int np, 
                                        bool isActive)
   {
      ar << isActive;
      if (isActive) {
         ar.pack(ptr, m, n, np);
      }
   }

}
#endif
