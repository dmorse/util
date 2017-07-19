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
   * \ingroup Math_Module
   */
   class BSplineBasis 
   {

   public:

      /// \name Constructors, Destructors, and Assignment
      //@{

      /**
      * Construct a spline basis of specified order.
      *
      * \param capacity initial capacity of coefficient array.
      */
      BSplineBasis(int order, bool verbose = false);

   private:

      DArray< Polynomial<Rational> > polynomials_;

      int order_;

   };

}
#endif
