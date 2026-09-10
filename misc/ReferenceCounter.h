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
   * have a ReferenceCounter member variable or base class that it uses to 
   * keep track of the number of objects that currently have access to the
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
   * an associated ReferenceCounter when such an association is created or 
   * destroyed.
   *
   * The parent resource owner class should check that nRef() > 0 before
   * attempting to delete or destroy the shared resource, and signal an
   * error if nRef() > 0. The nature of the response to such an error
   * (e.g., throwing an Exception, returning an error code, printing an
   * error message, etc.) depends on the context. 
   *
   * Design note: The nRef_ integer counter variable is declared "mutable"
   * to allow a CountedReference to created and destroyed associations for 
   * a resource owner that is an instance of a const data type without
   * it being treated as a change in the state of the resource owner.
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
      mutable int nRef_;
   
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
