#ifndef UTIL_REFERENCE_COUNTER_H
#define UTIL_REFERENCE_COUNTER_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2026, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

namespace Util {

   /**
   * Reference counter.
   *
   * A ReferenceCounter may be associated with zero or more 
   * CountedReference objects. An class that owns a shared resource such
   * as an array or memory block may use a private ReferenceCounter 
   * member to keep track of the number of objects that hold handles
   * to the resource. A class that has a handle to an a resource that 
   * it does not own it have a private CountedReference member to 
   * keep track of the relationship.
   *
   * \ingroup Util_Misc_Module
   */
   class ReferenceCounter 
   {
   
   public:
  
      /**
      * Constructor.
      */ 
      ReferenceCounter(); 
   
      /**
      * Get then number of references?
      */
      int nRef() const;
  
      /**
      * Does this counter have references (is nRef > 0)?
      */
      bool hasRefs() const;
   
   private:
  
      /// The number of associated CountedReference objects. 
      int nRef_;
   
      friend class CountedReference;
   
   };

   // Get the number of associated CountedReferences.
   inline int ReferenceCounter::nRef() const
   {  return nRef_; }

   // Does this counter have one or more associated CountedReferences?
   inline bool ReferenceCounter::hasRefs() const
   {  return (nRef_ > 0); }

} // namespace Util
#endif
