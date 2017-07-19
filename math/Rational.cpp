/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Rational.h"

namespace Util
{

   #if 0
   /*
   * istream extractor for a Rational.
   */
   std::istream& operator >> (std::istream& in, Rational& a)
   {
      in >> a.num_;
      //std::string dummy;
      //in >> dummy;
      in >> a.den_;
      return in;
   }
   #endif

   /*
   * ostream inserter for a Rational.
   */
   std::ostream& operator << (std::ostream& out, Rational const &a)
   {
      out << " " << a.num_;
      if (a.den_ != 1) {
         out << "/" << a.den_ ;
      }
      return out;
   }

}
