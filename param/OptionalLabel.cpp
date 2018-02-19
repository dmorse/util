/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "OptionalLabel.h"

namespace Util
{

   /*
   * Constructor.
   */
   OptionalLabel::OptionalLabel()
    : Label(false)
   {}

   /*
   * Constructor.
   */
   OptionalLabel::OptionalLabel(std::string string)
    : Label(string, false)
   {}

   /*
   * Constructor.
   */
   OptionalLabel::OptionalLabel(const char* string)
    : Label(string, false)
   {}

   /*
   * Copy constructor.
   */
   OptionalLabel::OptionalLabel(const OptionalLabel& other)
    : Label(other.string(), false)
   {}

   /*
   * Destructor.
   */
   OptionalLabel::~OptionalLabel()
   {}

} 
