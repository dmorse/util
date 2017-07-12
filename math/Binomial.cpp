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

   int Binomial::maxOrder_ = -1;
   GArray<int> Binomial::coeffs_;

   void Binomial::setup(int maxOrder)
   {
      UTIL_CHECK(maxOrder > 0);
      if (maxOrder <= maxOrder_) return;
      maxOrder_ = maxOrder;

      // Create coeff array of correct size , all zero elements
      int size = (maxOrder + 1)*(maxOrder +2)/2;
      coeffs_.resize(size);
      for (int i = 0; i < size; ++i) {
         coeffs_[i] = 0;
      }
      coeffs_[0] = 1;
   
      for (int n = 1; n <= maxOrder; ++n) {
         int bc = n*(n+1)/2;
         coeffs_[bc] = 1;
         if (n > 1) {
            int bp = (n-1)*n/2;
            for (int m = 1; m < n; ++m) {
               coeffs_[bc + m] = coeffs_[bp + m - 1] + coeffs_[bp + m];
            }
         }
         coeffs_[bc + n] = 1;
         std::cout << n << " : ";
         for (int m = 0; m <= n; ++m) {
            std::cout << " " <<  coeffs_[bc + m];
         }
         std::cout << " (size = " << bc + n + 1 << ")" << std::endl;
      }
   }

}
