/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "End.h"
#include <util/global.h>

namespace Util
{

   /* 
   * Constructor.
   */
   End::End()
    : label_("}")
   {}

   /* 
   * Destructor.
   */
   End::~End()
   {}

   /* 
   * Read and check end bracket.
   */
   void End::readParam(std::istream &in)
   {
      if (isIoProcessor()) {
         in >> label_;
         if (ParamComponent::echo()) {
            writeParam(Log::file());
         }
      }
   }

   /* 
   * Write end bracket.
   */
   void End::writeParam(std::ostream &out) const
   {  out << indent() << "}" << std::endl; }

   /* 
   * Empty implementation of virtual resetParam() method.
   */
   void End::resetParam()
   {}

} 
