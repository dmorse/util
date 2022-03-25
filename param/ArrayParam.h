#ifndef UTIL_ARRAY_PARAM_H
#define UTIL_ARRAY_PARAM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/Parameter.h>

namespace Util
{

   /**
   * An array-valued parameter in a parameter file.
   *
   * ArrayParam is a base class for objects that read and write the value
   * of an array containing a list of parameters of the same type. The 
   * parameter file format for a parameter contains a string label followed
   * by values of the elements of the array. 
   *
   * \ingroup Param_Module
   */
   class ArrayParam : public Parameter
   {

   public:

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

      #if 0
      /**
      * Read a label and (if label matches) an array of parameter values.
      *
      * The parameter file format for ArrayParam consists of a label string
      * followed by list of values for elements in an array. 
      *
      * \param in  input stream from which to read
      */
      virtual void readParam(std::istream &in);
      #endif

      /**
      * Enumeration of policies for use of brackets as delimiters.
      */
      enum BracketPolicy {Required, Forbidden, Optional};

   protected:

      /**
      * Read parameter label from an input stream.
      *
      * \param in input stream from which to read
      */
      virtual void readLabel(std::istream& in);

   private:

      /// Name of array (i.e., label string, without opening bracket)
      std::string name_;

      /// Is this a required array ?
      bool isRequired_;

      /// Does the label have a [ bracket appended?
      bool hasBrackets_;

   };

}
#endif
