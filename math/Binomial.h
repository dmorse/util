#ifndef UTIL_BINOMIAL_H
#define UTIL_BINOMIAL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/GArray.h>  // base class
#include <util/math/Rational.h>      // default template argument
#include <util/containers/Array.h>   // function argument
#include <util/global.h>


#include <iostream>

namespace Util
{

   /**
   * Class for binomial coefficients (all static functions)
   *
   * \ingroup Math_Module
   */
   class Binomial 
   {

   public:
   
      static void setup(int order); 
     
      // static int int(int n, int m); 

      // static double double(int n, int m); 

   private:

      /**
      * Integer binomial coefficients.
      */
      static
      GArray<int>  coeffs_;

      /**
      * Floating point binomial coefficients.
      */
      // GArray<double> rcoeffs_;

      static int maxOrder_;

      /**
      * Constructor (not implemented, to prevent instantiation)
      */
      Binomial();

   };

}
#endif
