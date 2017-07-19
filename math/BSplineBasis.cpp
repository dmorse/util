/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "BSplineBasis.h"
#include <util/global.h>

namespace Util
{

   /**
   * Construct a spline basis of specified order.
   */
   BSplineBasis::BSplineBasis(int order, bool verbose)
   {
      UTIL_CHECK(order >= 0);

      // Allocate the polynomials array
      order_ = order;
      int size = order + 1;
      polynomials_.allocate(size);

      // Set B_{0,0} = 1
      Polynomial<Rational> unity(Rational(1));
      polynomials_[0] = unity;

      if (verbose) {
         int n = 0;
         std::cout << std::endl;
         std::cout << "Order = 0 ";
         std::cout << " Domain [" << n 
                   << " , " << n + 1 << "] : "; 
         std::cout << polynomials_[n];
      }

      if (order > 0) {

         // Allocate and initialize work array 
         DArray< Polynomial<Rational> > integral;
         integral.allocate(size);
         int n;
         for (n = 0; n < size; ++n) {
            integral[n].clear();
         }

         // Recursive construction of spline bases
         int m;
         for (m = 0; m < order; ++m) {


            // Evaluate and store integral of previous order
            for (n = 0; n <= m; ++n) {
               integral[n] = polynomials_[n].integrate();
            }
            for (n = 0; n < size; ++n) {
               polynomials_[n].clear();
            }

            // Evaluate integral
            for (n = 0; n <= m + 1; ++n) {
               if (n < m + 1) {
                  polynomials_[n] += integral[n];
                  polynomials_[n] -= integral[n](Rational(n));
               }
               if (n > 0) {
                  polynomials_[n] += integral[n-1](Rational(n));
                  polynomials_[n] -= integral[n-1].shift(Rational(-1));
               }
            }

            if (verbose) {
               std::cout << std::endl;
               for (n = 0; n <= m + 1; ++n) {
                  std::cout << std::endl;
                  std::cout << "Order = " << m + 1;
                  std::cout << "  Domain [" << n 
                            << " , " << n + 1 << "] : "; 
                  std::cout << polynomials_[n];
               }
            }

         }
         
      }

   }

}
