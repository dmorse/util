#ifndef UTIL_COUNTED_REFERENCE_H
#define UTIL_COUNTED_REFERENCE_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2026, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

namespace Util {

   // Forward reference
   class ReferenceCounter;

   /**
   * Reference to a shared resource.
   *
   * \ingroup Misc_Module
   */
   class CountedReference 
   {
   public:
  
      /**
      * Constructor.
      */
      CountedReference();
   
      /**
      * Is this associated with a ReferenceCounter?
      */
      bool isAssociated() const;
   
      /**
      * Create an association with a ReferenceCounter.
      *
      * \param counter  associated ReferenceCounter
      */
      void associate(ReferenceCounter& counter);
   
      /**
      * Destroy an association with a ReferenceCounter.
      *
      * Throws an Exception in there is no associated counter.
      */
      void dissociate();
   
   private:
  
      // Pointer to associated counter, if any. 
      ReferenceCounter* ptr_; 
   
   };

   /**
   * Is this reference associated with a counter?
   */
   inline 
   bool CountedReference::isAssociated() const
   { return (bool) ptr_; }

} // namespace Util
#endif
