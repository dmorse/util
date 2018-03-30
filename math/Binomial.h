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
   * Class for binomial coefficients (all static members)
   *
   * \ingroup Math_Module
   */
   class Binomial 
   {

   public:
  
      /**
      * Precompute all combinations C(n, m) up to n = nMax.
      *
      * Algorithm: Construct rows [0,...,nMax] of Pascal's triangle.
      *
      * \param nMax maximum value of n to precompute.
      */ 
      static void setup(int nMax);
     
      /**
      * Release all static memory.
      */ 
      static void clear();
     
      /**
      * Return coefficient "n choose m", or C(n, m) = n!/(m!(n-m)!).
      *
      * Algorithm: Returns precomputed value C(n,m) if already known. 
      * Otherwise, calls setup(n) to computes and stores values of
      * C(n', m) for all n' <= n, then returns desired value.
      *
      * \param n larger integer (overall power in binomial)
      * \param m parameter in range [0,n]
      */ 
      static int coeff(int n, int m); 

   private:

      /**
      * Integer binomial coefficients.
      */
      static GArray<int> coeffs_;

      /**
      * Maximum value of n index (order of polynomial).
      */
      static int maxN_;

      /**
      * Constructor (private & not implemented, to prevents instantiation)
      */
      Binomial();

   };

}
#endif
