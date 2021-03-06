#ifndef UTIL_CONSTANTS_H
#define UTIL_CONSTANTS_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>
#include <complex>

namespace Util
{

   /**
   * Mathematical constants.
   *
   * \ingroup Math_Module
   */
   class Constants
   {

   public:

      /**
      * Initialize static constants.
      */
      static void initStatic();

      /**
      * Trigonometric constant Pi.
      */
      static const double               Pi;

      /**
      * Square root of -1.
      */
      static const std::complex<double> Im;

   };

} 
#endif
