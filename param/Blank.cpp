/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Blank.h"

namespace Util
{

   // Constructor.
   Blank::Blank()
    : ParamComponent()
   {}

   /// Virtual Destructor
   Blank::~Blank()
   {}

   // Read a blank line
   void Blank::readParam(std::istream &in)
   {
      if (isIoProcessor()) {
         char buf[255];
         in.getline(buf,255);
         if (ParamComponent::echo()) {
            writeParam(Log::file());
         }
      }
   }

   // Write a blank line
   void Blank::writeParam(std::ostream &out) const
   {  out << std::endl; }

} 
