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
   * of an matrix or 2D array containing a list of parameters of the same  
   * type. 
   *
   * Matrices can be read and written in either of two formats:
   * 
   *   - Bracketed format begins with a label immediately followed by an
   *     opening delimiter on a line by itself, followed by several data 
   *     lines, and ends with a closing delimiter. 
   *
   *   - Bracket-free format begins with a label on the same line as the 
   *     first line of data, with no opening or closing bracket delimiters.
   *
   * Different subclasses may use different formats for the data lines, 
   * and different choices of delmiting brackets (e.g., square brackets 
   * or parentheses). Two different conventions are in use:
   *
   *   - Row data format puts values of all the elements in each row of 
   *     the matrix on a single line, with rows appearing in order of 
   *     increasing index, as in standard linear algebra matrix format.
   * 
   *   - Element format puts each element on a single line, in which
   *     each line contains the row and column index followed by the
   *     value.
   *
   * Either row or element data format may be input and output in either 
   * bracketed or bracket-free format. The choice of whether to use 
   * bracketed or bracket-free format is determined by the global bracket 
   * policy returned by the function Util::BracketPolicy::get().
   *
   *   - If the policy is BracketPolicy::Forbidden, the bracket-free 
   *     format must be used for both reading and writing.
   *
   *   - If the policy is BracketPolicy::Required, the bracketed format
   *     must be used for both reading and writing.
   *
   *   - If the policy is BracketPolicy::Optional, then either format
   *     can be read, but the bracketed format is used for writing.
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
      * Read the closing delimiter, if any.
      *
      * Attempts to read closing bracket iff hasBrackets is true.
      * Throws an exception if hasBrackets is true but the expected
      * delimiter is not found.
      *
      * \param in  input stream from which to read
      */
      void readEndBracket(std::istream& in);

      /**
      * Write the end bracket delimiter, if any.
      *
      * \param out  output stream to which to write
      */
      void writeEndBracket(std::ostream& out) const;

      /**
      * Are brackets being used as delimiters?
      */ 
      bool hasBrackets() const
      {  return hasBrackets_; }

      /**
      * Set left and right bracket / delimiter strings.
      *
      * \param lBracket  left bracket string
      * \param rBracket  right bracket string
      */
      void setBrackets(std::string lBracket, std::string rBracket);

      using Parameter::label_;

   private:

      /// Name of array (i.e., label string, without opening bracket)
      std::string name_;

      /// Left bracket delimiter string 
      std::string lBracket_;

      /// Right bracket delimiter string 
      std::string rBracket_;

      /// Number of rows (logical)
      int m_;

      /// Number of columns (logical)
      int n_;

      /// Is this a required array ?
      bool isRequired_;

      /// Are brackets being used as delimiters?
      bool hasBrackets_;

   };

}
#include <util/param/MatrixParam.tpp>
#endif
