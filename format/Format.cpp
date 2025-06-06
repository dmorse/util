/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Format.h"
#include <util/global.h>

namespace Util
{

   // Define and initialize static constants
   int Format::defaultWidth_     = 15;
   int Format::defaultPrecision_ =  7;

   /**
   * Set Format::defaultWidth_
   */
   void Format::setDefaultWidth(int width)
   {  Format::defaultWidth_ = width; }

   /*
   * Set Format::defaultPrecision_
   */
   void Format::setDefaultPrecision(int precision)
   {  Format::defaultPrecision_ = precision; }

   /*
   * Get the default output field width.
   */
   int Format::defaultWidth()
   { return defaultWidth_; }

   /*
   * Get the default output precision.
   */
   int Format::defaultPrecision()
   {  return defaultPrecision_; }

   /*
   * This static method exists to guarantee initialization of static 
   * constants that are defined in the same file.  Call it somewhere 
   * in the program to guarantee that the contents of this file will 
   * be linked, rather than optimized away. It may only be called once.
   */
   void Format::initStatic()
   {  
      // This function can only be called once.
      static int nCall = 0;  // static value is only initialized once
      UTIL_CHECK(nCall == 0);
      Format::defaultWidth_     = 15;
      Format::defaultPrecision_ =  7;
      ++nCall;
   }

} 
