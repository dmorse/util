/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Rational.h"

namespace Util
{

   /*
   * Output stream inserter for a Rational.
   */
   std::ostream& operator << (std::ostream& out, Rational const &a)
   {
      UTIL_CHECK(a.den_ > 0);
      out << a.num_;
      if (a.den_ != 1) {
         out << "/" << a.den_ ;
      }
      return out;
   }

   #ifdef UTIL_CXX11
   /*
   * Input stream extractor for a Rational.
   */
   std::istream& operator >> (std::istream& in, Rational &a)
   {
      std::string word;
      in >> word;
      int size = word.size();

      // Search for '/' character in word
      std::size_t slashId = word.find('/');
      bool hasSlash = false;
      if (slashId != std::string::npos) {
         hasSlash = true;
      }

      // Extract numerator and denominator 
      if (hasSlash) {
         UTIL_CHECK(slashId > 0);
         UTIL_CHECK(slashId < size - 1);
         int numSize = slashId;
         int denSize = size - slashId - 1;
         std::string numStr = word.substr(0, numSize);
         std::string denStr = word.substr(slashId + 1, denSize);
         a.num_ = std::stoi(numStr);
         a.den_ = std::stoi(denStr);
      } else {
         a.num_ = std::stoi(word);
         a.den_ = 1;
      }
      UTIL_CHECK(a.den_  > 0);

      return in;
   }
   #endif

}
