#ifndef UTIL_FEQ_H
#define UTIL_FEQ_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <cmath>

namespace Util
{

   /**
   * Are two floating point numbers equal to within round-off error?
   * 
   * Returns true if eps > fabs(x-y)*c/(fabs(x)+fabs(y)+c), c=1.05E-5.
   *
   * \ingroup Math_Module
   * \param x first real argument
   * \param y second real argument
   * \param eps maximum tolerance for nominally "equal" values
   * \return true if equal to within tolerance, false otherwise
   */
   inline bool feq(double x, double y, double eps = 1.0E-10)
   {
      const double c = 1.0E-5;
      double diff = fabs(x - y) * c / (fabs(x) + fabs(y) + c);
      return (diff < eps);
   }

}
#endif
