#ifndef UTIL_B_SPLINE_BASIS_H
#define UTIL_B_SPLINE_BASIS_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/DArray.h>    
#include <util/math/Polynomial.h>    
#include <util/math/Rational.h>    
#include <util/global.h>


#include <iostream>

namespace Util
{

   /**
   * A BSplineBasis.
   *
   * A BSplineBasis of order m is a piecewise continuous mth
   * order polynomial defined over the domain [0, m+1]. For
   * m >= 1, the function and m-1 derivatives are continuous. 
   *
   * If b is a BSpline basis of order m, then:
   *
   *  - Array element b[i] returns the polynomial for [i,i+1]
   *  - Call operator b(x) returns the value of b for real x.
   *
   * \ingroup Math_Module
   */
   class BSplineBasis 
   {

   public:

      /// \name Constructor and Destructor
      //@{

      /**
      * Construct a spline basis of specified order.
      *
      * \param order order of polynomials
      * \param verbose if true, write report to std::cout
      */
      BSplineBasis(int order, bool verbose = false);
     
      /**
      * Destructor.
      */ 
      ~BSplineBasis();

      //@}

      /**
      * Get Polynomial<double> object for domain [i,i+1]
      *
      * If b is a BSplineBasis, b[i] returns the polynomial
      * associated with the domain [i,i+1].
      *
      * \param i integer index in range 0 <= i <= order.
      * \return polynomial associated with domain [i, i+1]
      */
      Polynomial<double> const & operator [](int i);

      /**
      * Compute the value of the spline basis function.
      *
      * If b is a BSplineBasis, b(x) returns the value of the
      * spline for specified floating point argument x, giving
      * a nonzero value only for 0 < x < order + 1.
      *
      * \param x argument of spline basis function
      */
      double operator ()(double x);

   private:

      /**
      * Array of polynomials with Rational coefficients.
      *
      * Polynomial i applies in the domain [i, i+1], for index
      * i in the range 0 <= i <= order. The polynomials_ array
      * is thus allocated with a capacity equal to order_ + 1.
      */
      DArray< Polynomial<Rational> > exactPolynomials_;

      /**
      * Array of polynomials with floating point coefficients.
      */
      DArray< Polynomial<double> > floatPolynomials_;

      /**
      * Order of the polynomials used to construct the spline.
      */
      int order_;

   };

   /*
   * Get polynomial with real coefficients for domain [i,i+1]
   */
   inline
   Polynomial<double> const & BSplineBasis::operator [](int i)
   {  return floatPolynomials_[i]; }

   /*
   * Get value of spline.
   */
   inline
   double BSplineBasis::operator ()(double x)
   {  
      if (x <= 0.0) return 0.0;
      int i = x;
      UTIL_ASSERT(i >= 0);
      if (i > order_) return 0.0;
      return floatPolynomials_[i](x);
   }

}
#endif
