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
   * CountedReference objects. A class that owns a shareable resource
   * such as a dynamically allocated array, known as a resource owner, may
   * have a private ReferenceCounter member variable that it uses to keep
   * track of the number of objects that currently have access to the
   * resource. A class that can access a reference counted resource that
   * it does not own, known as a resource user, may have a private 
   * CountedReference member variable to keep track of the relationship. 
   *
   * A ReferenceCounter has an integer counter that is equal of the
   * number of associated CountedReference objects. The value of this
   * counter is returned by the nRef() member function. A CountedReference
   * has a pointer member that can hold the address of a single 
   * associated Referrence counter. The CountedReference class is a 
   * friend of the RefererenceCounter class. This allows a CountedReference
   * to directly increment or decrement the integer counter maintained by 
   * an associated ReferenceCounter when the association is created or 
   * destroyed.
   *
   * While nRef() returns a nonzero value, the parent resource owner 
   * class should attempt to prevent actions that de-allocate or otherwise
   * invalidate a shared resource, and output a warning of such actions
   * when they cannot be prevented (e.g., during destruction).
   * 
   * \ingroup Misc_Module
   */
   class ReferenceCounter 
   {
   
   public:
  
      /**
      * Constructor.
      */ 
      ReferenceCounter(); 
   
      /**
      * Get the number of references to a shareable resource.
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
