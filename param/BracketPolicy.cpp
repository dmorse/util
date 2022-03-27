/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "BracketPolicy.h"

namespace Util
{

  
   // Anonymous namespace for private quasi-static variables 
   namespace{

      /// Policy regarding use of brackets.
      BracketPolicy::Type policy_ = BracketPolicy::Forbidden;

   }

   namespace BracketPolicy 
   {

      /**
      * Set policy regarding use of bracket delimiters on arrays.
      */
      void set(BracketPolicy::Type policy)
      {   policy_ = policy; }

      /**
      * Get value of bracket policy.
      */
      BracketPolicy::Type get()
      {  return policy_; }


   } // namespace BracketPolicy

} // namespace Util
