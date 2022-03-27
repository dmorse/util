#ifndef UTIL_MATRIX_PARAM_H
#define UTIL_MATRIX_PARAM_H

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
   * MatrixParam is a base class for objects that read and write the value
   * of an array containing a list of parameters of the same type. The 
   * parameter file format for a parameter contains a string label followed
   * by values of the elements of the array. 
   *
   * \ingroup Param_Module
   */
   template <typename Type>
   class MatrixParam : public Parameter
   {

   public:

      /**
      * Constructor.
      *
      * \param label  label string (without any opening bracket)
      * \param m  number of rows
      * \param n  number of columns
      * \param isRequired  Is this a required parameter?
      */
      MatrixParam(const char *label, int m, int n, bool isRequired = true);

      /**
      * Destructor.
      */
      virtual ~MatrixParam();

      /**
      * Get the logical array dimension.
      */
      int m() const
      {  return m_; }

      /**
      * Get the logical array dimension.
      */
      int n() const
      {  return n_; }

      using ParamComponent::indent;
      using Parameter::readValue;
      using Parameter::load;
      using Parameter::save;
      using Parameter::label;
      using Parameter::isRequired;
      using Parameter::isActive;

   protected:

      /**
      * Read parameter label from an input stream.
      *
      * \param in input stream from which to read
      */
      virtual void readLabel(std::istream& in);

      /**
      * Read the end bracket, if any.
      *
      * \param in input stream from which to read
      */
      virtual void readEndBracket(std::istream& in);

      /**
      * Are brackets used as delimiters?
      */ 
      bool hasBrackets() const
      {  return hasBrackets_; }

      using Parameter::label_;

   private:

      /// Name of array (i.e., label string, without opening bracket)
      std::string name_;

      /// Number of rows
      int m_;

      /// Number of columns
      int n_;

      /// Is this a required array ?
      bool isRequired_;

      /// Are square brackets ([....]) used as delimiters?
      bool hasBrackets_;

   };

}
#include <util/param/MatrixParam.tpp>
#endif
