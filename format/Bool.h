#ifndef UTIL_BOOL_H
#define UTIL_BOOL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <iostream>

namespace Util
{

   /**
   * Wrapper for an bool value, for formatted ostream output.
   *
   * An Bool object has a bool value, and a minimum output field width.
   * The << operator for a Bool uses the specified width. The value 
   * and width may both be specified as parameters to a constructor.
   * If the width is not specified as a constructor parameter, it is 
   * set within the constructor to the default Format::defaultWidth().
   *
   * An Bool object may be passed to an ostream as a temporary object.
   * For example, the expression:
   * \code
   *    std::cout << Bool(true) << Bool(false, 10) << std::endl;
   * \endcode
   * outputs the value true using the default width, followed by the
   * false value in a field of minimum width 10.
   *
   * \ingroup Format_Module
   */
   class Bool
   {

   public:

      /// \name Constructors
      //@{ 
     
      /** 
      * Default constructor.
      */
      Bool();

      /**
      * Constructor, set value.
      *
      * \param value  value of the variable
      */
      explicit Bool(bool value);

      /**
      * Constructor, value and width.
      *
      * \param value  value of the variable
      * \param width  output width (number of characters)
      */
      Bool(bool value, int width);

      //@}
      ///\name Setters
      //@{
      
      /**
      * Set the value.
      *
      * \param value  value of the variable
      */
      void setValue(bool value);

      /**
      * Set the output width.
      *
      * \param width output width (number of characters)
      */
      void setWidth(int width);

      //@}
      ///\name Accessors
      //@{
     
      /// Return value. 
      bool value();

      /// Return default width (number of characters). 
      int width();

      //@}
      
   private:

      /// Value.
      bool value_;

      /// Output width (number of characters).
      int  width_;

   //friends:

      friend std::istream& operator>>(std::istream& in, Bool &object);
      friend std::ostream& operator<<(std::ostream& out, const Bool &object);

   };

   /**
   * Input stream extractor for an Bool object.
   *
   * \param in  input stream
   * \param object  Bool object to be read from stream
   * \return modified input stream
   */
   std::istream& operator>>(std::istream& in, Bool &object);

   /**
   * Output stream inserter for an Bool object.
   *
   * \param  out  output stream
   * \param  object  Bool to be written to stream
   * \return modified output stream
   */
   std::ostream& operator<<(std::ostream& out, const Bool &object);

} 
#endif
