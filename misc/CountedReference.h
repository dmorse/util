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
   * A class that makes use of a resource that it does not own, known as a
   * resource user, may have a private CountedReference member variable to
   * keep track of the association with the class that owns the resource,
   * known as the resource owner. In this pattern, the resource owner 
   * class should have a private ReferenceCounter member variable that
   * maintains an integer counter of the number of associated resource 
   * users. A CountedReference may only be associated with a single
   * ReferenceCounter, but a ReferenceCounter may be associated with
   * any number of instances of CountedReference.
   *
   * A CountedReference has a private pointer member that can store
   * the address of an associated ReferenceCounter. A ReferenceCounter
   * has an integer member variable that keeps track of the number of
   * associated CountedReference objects. The CountedReference class is
   * a friend of ReferenceCounter, which allows it to increment and
   * decrement the counter maintained by an associated ReferenceCounter
   * whenever an association is created or destroyed.
   *
   * Each resource user class should provide public functions, typically
   * named associated and dissociate, that can create and destroy an
   * association with a single instance of a related resource owner class.
   * The associate member function of the parent resource user class 
   * should retain a handle to the shared resource and also call the 
   * associate member function of its CountedReference member variable.
   * The dissociate member function of the parent resource user class
   * should nullify the handle to the resource and call the dissociate
   * function of the CountedReference member variable. 
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
      * On entry, isAssociated() must return false. After return, 
      * isAssociated() will return true. 
      *
      * This function retains a pointer to the associated ReferenceCounter
      * that is passed as a parameter. It also increments the integer 
      * reference counter maintained by that object, which is returned
      * by the function ReferenceCounter::nRef().
      *
      * \param counter  associated ReferenceCounter
      */
      void associate(ReferenceCounter& counter);
   
      /**
      * Destroy an association with a ReferenceCounter.
      *
      * On entry, isAssociated() must true true. After return, 
      * isAssociated() will return false. 
      *
      * This function decrements the integer counter maintained by an
      * associated ReferenceCounter, and then nullifies the pointer to
      * to that object. 
      */
      void dissociate();
   
   private:
  
      // Pointer to associated ReferenceCounter, if any. 
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
