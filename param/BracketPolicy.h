#ifndef UTIL_BRACKET_POLICY_H
#define UTIL_BRACKET_POLICY_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>

namespace Util
{

   /**
   * Namespace to define of policies for brackets on arrays and matrices.
   *
   * \ingroup Param_Module
   */
   namespace BracketPolicy 
   {

      /**
      * Typeeration of policies regarding use of delimiters on arrays
      */
      enum Type {Required, Forbidden, Optional};

      /**
      * Set policy regarding use of bracket delimiters on arrays.
      */
      void set(BracketPolicy::Type policy);

      /**
      * Get value of bracket policy.
      */
      Type get();

   };

}
#endif
