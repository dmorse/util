#ifndef UTIL_INIT_STATIC_H
#define UTIL_INIT_STATIC_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

namespace Util
{

   /**
   * Guarantee initialization of all static class members in Util namespace.
   */
   void initStatic();

}
#endif
