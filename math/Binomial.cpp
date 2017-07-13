/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Binomial.h"
#include <util/global.h>

namespace Util
{

   int Binomial::maxN_ = -1;
   GArray<int> Binomial::coeffs_;

   void Binomial::setup(int maxN)
   {
      UTIL_CHECK(maxN >= 0);
      if (maxN <= maxN_) return;
      maxN_ = maxN;

      // Create coeff array of correct size , all zero elements
      int size = (maxN + 1)*(maxN +2)/2;
      coeffs_.resize(size);
      for (int i = 0; i < size; ++i) {
         coeffs_[i] = 0;
      }

      // Generate Pascal's triangle to set coefficients
      coeffs_[0] = 1;
      if (maxN == 0) return;
      int n, m, bc, bp;
      for (n = 1; n <= maxN; ++n) {
         bc = n*(n+1)/2;
         coeffs_[bc] = 1;
         if (n > 1) {
            bp = (n-1)*n/2;
            for (m = 1; m < n; ++m) {
               coeffs_[bc + m] = coeffs_[bp + m - 1] + coeffs_[bp + m];
            }
         }
         coeffs_[bc + n] = 1;
      }
   }

   int Binomial::coeff(int n, int m) 
   {
      UTIL_CHECK(n >= 0);
      UTIL_CHECK(m >= 0 && m <= m);
      if (n > maxN_) setup(n);
      return coeffs_[(n*(n+1)/2) + m] ;
   }

}
