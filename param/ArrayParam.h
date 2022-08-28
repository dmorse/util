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
   * ArrayParam is a base class for objects that read and write the 
   * value of an array containing a list of parameters of the same type. 
   * The parameter file format for a parameter contains a string label 
   * followed by values of the elements of the array. 
   *
   * Arrays can be read and written in either of two formats:
   * 
   *   - Bracketed format begins with a label immediately followed by an
   *     opening left bracket "[" on a line by itself, followed by several 
   *     data lines, and ends with a closing bracket ("]") on a line by
   *     itself.
   *
   *   - Bracket-free format begins with a label on the same line as the 
   *     first line of data, with no opening or closing delimit
   *
   * The choice of whether to use bracketed or bracket-free format 
   * is determined by the value of the global policy returned by the 
   * function Util::BracketPolicy::get() :
   *
   *   - If the policy is BracketPolicy::Required, the bracketed format
   *     must be used for both reading and writing.
   *
   *   - If the policy is BracketPolicy::Forbidden, the bracket-free 
   *     format must be used for both reading and writing.
   *
   *   - If the policy is BracketPolicy::Optional, then either format
   *     can be read, but the bracketed format is used for writing.
   *
   * If the bracket policy is optional, the code determines if brackets
   * are being used on input by looking for an opening bracket at the
   * end of the label. A closing bracket is then required if an opening
   * bracket is found, and forbidden if no opening bracket is found.
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
      * \param isRequired  Is this a required array-valued parameter?
      */
      ArrayParam(const char *label, int n, bool isRequired = true);

      /**
      * Destructor.
      */
      virtual ~ArrayParam();

      /** 
      * Write an array-valued parameter to stream.
      *
      * The array is written if and only if isActive() is true.
      *
      * \param out output stream
      */
      void writeParam(std::ostream &out) const;

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

      /**
      * Read parameter label from an input stream.
      *
      * \param in input stream from which to read
      */
      virtual void readLabel(std::istream& in);

      /**
      * Read array of element values from an input stream.
      *
      * This function should be called after readLabel. It reads all the
      * elements and then calls readEndBracket to read the final bracket,
      * if any.
      * 
      * \param in input stream from which to read
      */
      virtual void readValue(std::istream& in);

      /**
      * Read a closing bracket, if necessary.
      *
      * This function attempts to read the closing "]" bracket if and 
      * only if hasBrackets is true. An Exception is thrown if hasBrackets 
      * is true and no bracket is found. Before returning, the format is 
      * also reset to the appropriate default format for output.
      * 
      * \param in input stream from which to read
      */
      void readEndBracket(std::istream& in);

      /**
      * Return a non-const reference to one element of the array.
      *
      * This function is used to access individual elements within the
      * readValue function. It must be implemented by subclasses.
      * 
      * \param i  array element index
      */
      virtual Type& element(int i) = 0;

      /**
      * Return a non-const reference to one element of the array.
      *
      * This function is used to access individual elements within the
      * readValue function. It must be implemented by subclasses.
      * 
      * \param i  array element index
      */
      virtual Type const & element(int i) const = 0;

      /**
      * Are square brackets being used as delimiters?
      */ 
      bool hasBrackets() const
      {  return hasBrackets_; }

      using Parameter::label_;

   private:

      /// Name of array (i.e., label string, without opening bracket)
      std::string name_;

      /// Logical array dimension
      int n_;

      /// Is this a required array ?
      bool isRequired_;

      /// Are square brackets ([....]) being used as delimiters?
      bool hasBrackets_;

   };

}
#include <util/param/ArrayParam.tpp>
#endif
