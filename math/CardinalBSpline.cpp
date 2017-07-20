/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "CardinalBSpline.h"
#include <util/global.h>

namespace Util
{

   /*
   * Construct a spline basis of specified degree.
   */
   CardinalBSpline::CardinalBSpline(int degree, bool verbose)
   {
      UTIL_CHECK(degree >= 0);

      // Allocate the polynomial arrays
      degree_ = degree;
      int size = degree + 1;
      exactPolynomials_.allocate(size);
      floatPolynomials_.allocate(size);

      // Set B_{0,0} = 1
      Polynomial<Rational> unity(Rational(1));
      exactPolynomials_[0] = unity;

      if (verbose) {
         int n = 0;
         std::cout << std::endl;
         std::cout << "Degree = 0 ";
         std::cout << " [" << n 
                   << " , " << n + 1 << "] : "; 
         std::cout << exactPolynomials_[n];
      }

      if (degree > 0) {

         // Allocate and initialize work array 
         DArray< Polynomial<Rational> > work;
         work.allocate(size);
         int n;
         for (n = 0; n < size; ++n) {
            work[n].setToZero();
         }

         // Recursive construction of spline bases
         int m; // Degree of previously calculated spline polynomials
         for (m = 0; m < degree; ++m) {

            // Evaluate and store integrals of degree m polynomials
            for (n = 0; n <= m; ++n) {
               work[n] = exactPolynomials_[n].integrate();
            }

            // Clear exactPolynomials_ array
            for (n = 0; n < size; ++n) {
               exactPolynomials_[n].setToZero();
            }

            // Applying recursion relation to obtain degree m+1 polynomials
            for (n = 0; n <= m + 1; ++n) {
               if (n < m + 1) {
                  exactPolynomials_[n] += work[n];
                  exactPolynomials_[n] -= work[n](Rational(n));
               }
               if (n > 0) {
                  exactPolynomials_[n] += work[n-1](Rational(n));
                  exactPolynomials_[n] -= work[n-1].shift(Rational(-1));
               }
            }

            // Optionally output intermediate results
            if (verbose) {
               std::cout << std::endl;
               for (n = 0; n <= m + 1; ++n) {
                  std::cout << std::endl;
                  std::cout << "Degree = " << m + 1;
                  std::cout << " [" << n 
                            << " , " << n + 1 << "] : "; 
                  std::cout << exactPolynomials_[n] << "   ";
                  std::cout << exactPolynomials_[n](Rational(n)) << " ";
                  std::cout << exactPolynomials_[n](Rational(n+1)) << " ";
               }
            }

         }

         // Check continuity of function and m-1 derivatives
         for (n = 0; n <= degree_; ++n) {
            work[n] = exactPolynomials_[n];
         }
         Rational lower;
         Rational upper;
         for (m = 0; m < degree_; ++m) {
            for (n = 1; n <= degree_; ++n) {
               lower = work[n-1](Rational(n));
               upper = work[n](Rational(n));
               UTIL_CHECK(lower == upper);
            }
            for (n = 0; n <= degree_; ++n) {
               work[n] = work[n].differentiate();
            }
         }

         // Convert polynomials coefficients from Rational to double.
         for (n = 0; n <= degree_; ++n) {
            floatPolynomials_[n] = exactPolynomials_[n];
         }

      }

   }

   /*
   * Destructor.
   */
   CardinalBSpline::~CardinalBSpline()
   {}

}
