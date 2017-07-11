#ifndef UTIL_GCD_H
#define UTIL_GCD_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <stdlib.h>

namespace Util
{

   /*
   * Compute greatest common divisor (gcd) of two integers.
   *
   * Uses Euclidean algorithm to compute gcd.
   *
   * \ingroup Math_Module
   *
   * \param a 1st integer
   * \param b 2nd integer
   * \return greatest common divisor of a and b
   */
   inline int gcd(int a, int b)
   {
      if (a == 0) return b;
      if (b == 0) return a;
      a = abs(a);
      b = abs(b);
      int c;
      // If b > a, swap such that b < a
      if (b > a) {
         c = a;
         a = b;
         b = c;
      }
      while (b !=0) {
         c = a % b;
         a = b;
         b = c;
      }
      return a;
   }

}
#endif
