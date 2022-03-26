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
   template <typename Type>
   class ArrayParam : public Parameter
   {

   public:

      /**
      * Constructor.
      *
      * \param label  label string preceding value in file format
      * \param n  logical array dimension
      * \param isRequired  Is this a required parameter?
      */
      ArrayParam(const char *label, int n, bool isRequired = true);

      /**
      * Destructor.
      */
      virtual ~ArrayParam();

      /** 
      * Write parameter to stream.
      *
      * \param out output stream
      */
      void writeParam(std::ostream &out);

      /**
      * Get the logical array dimension.
      */
      int n() const
      {  return n_; }

      using ParamComponent::indent;
      using Parameter::load;
      using Parameter::save;
      using Parameter::label;
      using Parameter::isRequired;
      using Parameter::isActive;

   protected:

      /// Logical array dimension
      int n_;

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
      virtual void readValue(std::istream& in);

      /**
      * Return reference to one element.
      */
      virtual Type& element(int i) = 0;

      /**
      * Are brackets used as delimiters?
      */ 
      bool hasBrackets() const
      {  return hasBrackets_; }

      using Parameter::label_;

   private:

      /// Name of array (i.e., label string, without opening bracket)
      std::string name_;

      /// Is this a required array ?
      bool isRequired_;

      /// Are square brackets ([....]) used as delimiters?
      bool hasBrackets_;

   };

}
#include <util/param/ArrayParam.tpp>
#endif
