/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2026, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/


#include "CountedReference.h"
#include "ReferenceCounter.h"
#include <util/global.h>

namespace Util {

   /*
   * Default constructor.
   */
   CountedReference::CountedReference()
    : ptr_(nullptr)
   {}

   /*
   * Create an association with a ReferenceCounter.
   */
   void CountedReference::associate(ReferenceCounter& owner)
   {
      UTIL_CHECK(!isAssociated());
      ptr_ = &owner;
      ++(ptr_->nRef_);
   }

   /*
   * Destroy an association with a ReferenceCounter.
   */
   void CountedReference::dissociate()
   {
      UTIL_CHECK(isAssociated());
      UTIL_CHECK(ptr_->nRef_ > 0);
      --(ptr_->nRef_);
      ptr_ = nullptr;
   }

} // namespace Util
