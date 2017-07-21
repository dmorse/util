#ifndef UTIL_CARDINAL_B_SPLINE_H
#define UTIL_CARDINAL_B_SPLINE_H

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
   * A cardinal B-spline basis function.
   *
   * A cardinal B-Spline of order m or degree k = m - 1 is a piecewise 
   * continuous polynomial of degree k defined over the domain [0, k+1].
   * Such a function is defined by k different polynomials, each of 
   * which has a domain [i, i+1] for an integer i with 0 <= i <=k. 
   * For k > 0, the function and k-1 derivatives are continuous. 
   *
   * A CardinalBSpline object of degree k has k Polynomial<double>
   * objects, indexed by an integer 0 <= i <= k, each of which defines 
   * the polynomial with a domain [i,i+1].
   *
   * If object b is a CardinalBSpline of degree k, then:
   *
   *  - Operator b[i] returns the Polynomial<double> for domain [i,i+1]
   *  - Operator b(x) returns the value of basis function b for real x.
   *
   * \ingroup Math_Module
   */
   class CardinalBSpline 
   {

   public:

      /// \name Constructor and Destructor
      //@{

      /**
      * Construct a spline basis of specified degree.
      *
      * \param degree degree of the function (i.e., degree of polynomials)
      * \param verbose if true, write verbose report to std::cout
      */
      CardinalBSpline(int degree, bool verbose = false);
     
      /**
      * Destructor.
      */ 
      ~CardinalBSpline();

      //@}

      /**
      * Get Polynomial<double> object for domain [i,i+1]
      *
      * If b is a CardinalBSpline, b[i] returns the Polynomial<double>
      * object (the polynomial with double precision floating point
      * coefficients) associated with the domain [i,i+1].
      *
      * \param i integer index in range 0 <= i <= degree.
      * \return polynomial associated with domain [i, i+1]
      */
      Polynomial<double> const & operator [](int i) const;

      /**
      * Compute the value of the spline basis function.
      *
      * If b is a CardinalBSpline, b(x) returns the value of the spline
      * function for specified floating point argument x, giving a
      * nonzero value only for 0 < x < degree + 1.
      *
      * \param x argument of spline basis function
      */
      double operator ()(double x) const;

      /**
      * Return degree of basis function (i.e., degree of polynomials).
      */
      int degree() const;

   private:

      /**
      * Array of polynomials with floating point coefficients.
      *
      * Polynomial i applies in the domain [i, i+1], for index
      * i in the range 0 <= i <= degree. The polynomials_ array
      * is thus allocated with a capacity equal to degree_ + 1.
      */
      DArray< Polynomial<double> > floatPolynomials_;

      /**
      * Degree of the polynomials used to construct the spline.
      * 
      * The number of coefficients in each polynomial, and the
      * number of polynomials are both equal to the order of the
      * cardinal B-spline, which is equal to degree + 1.
      */
      int degree_;

   };

   /*
   * Get polynomial with real coefficients for domain [i,i+1]
   */
   inline
   Polynomial<double> const & CardinalBSpline::operator [](int i) const
   {  return floatPolynomials_[i]; }

   /*
   * Get value of spline.
   */
   inline
   double CardinalBSpline::operator ()(double x) const
   {  
      if (x <= 0.0) return 0.0;
      int i = x;
      UTIL_ASSERT(i >= 0);
      if (i > degree_) return 0.0;
      return floatPolynomials_[i](x);
   }

   /*
   * Return degree of basis function (i.e., degree of polynomials).
   */
   inline
   int CardinalBSpline::degree() const
   {  return degree_; }

}
#endif
