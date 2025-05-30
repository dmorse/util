/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Constants.h"
#include <cmath>

namespace Util
{

   const double               Constants::Pi = 2.0*acos(0.0);
   const std::complex<double> Constants::Im = std::complex<double>(0.0, 1.0);

   /*
   * This function exists to guarantee initialization of static constants.
   * Calling it guarantees that the contents of this file will be linked,
   * rather than optimized away. It may only be called once.
   */
   void Constants::initStatic() 
   {
      static int nCall = 0; // This initializer is only called once
      UTIL_CHECK(nCall == 0);
      ++nCall;
   }

}
