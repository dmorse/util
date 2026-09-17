#ifndef UTIL_ARRAY_SOURCE_H
#define UTIL_ARRAY_SOURCE_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/containers/Array.h>        // base class
#include <util/misc/ReferenceCounter.h>   // base class

namespace Util {

   /**
   * An Array<Data> and ReferenceCounter.
   *
   * An ArraySource<Data> is an array that can be referencd by another
   * array or array view, and that implements reference counting. This
   * class is designed to be used as a base class for classes that
   * implement this behavior. Subclasses are responsible for memory 
   * management, i.e., allocation, de-allocation, and error checking 
   * on de-allocation. 
   *
   * \ingroup Array_Module
   * \ingroup Util_Containers_Module
   */
   template <typename Data>
   class ArraySource : public Array<Data>, public ReferenceCounter
   {
   protected:

      // Protected to prevent direct instantiation or destruction
      ArraySource() = default;
      ArraySource(ArraySource<Data>  const&) = default;
      ~ArraySource() = default;
      ArraySource<Data>& operator = (ArraySource<Data>  const&) = default;

   };

} // namespace Util
#endif
