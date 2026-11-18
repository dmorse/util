/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, David Morse (morse012@um.edu) 
* Distributed under the terms of the GNU General Public License.
*/

#include "Blank.h"

#include <cctype>
#include <istream>

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

         // Skip white space up to and including the end of the current
         // line, of any length. Stop before any other character: such
         // text belongs to the next item and is left in the stream.
         int c = in.peek();
         while (c != std::istream::traits_type::eof() && c != '\n'
                && std::isspace(c)) {
            in.get();
            c = in.peek();
         }
         if (c == '\n') {
            in.get();
         }

         if (ParamComponent::echo()) {
            writeParam(Log::file());
         }
      }
   }

   // Write a blank line
   void Blank::writeParam(std::ostream &out) const
   {  out << std::endl; }

} 
