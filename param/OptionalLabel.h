#ifndef UTIL_OPTIONAL_LABEL_H
#define UTIL_OPTIONAL_LABEL_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/Label.h>

namespace Util
{

   /**
   * An optional Label string in a file format.
   *
   * A subclass of Label that is always optional.
   *
   * \ingroup Param_Module
   */
   class OptionalLabel  : public Label
   {

   public:

      /**
      * Default constructor.
      */
      OptionalLabel();

      /**
      * Constructor.
      *
      * \param string  label string that precedes value in file format
      */
      explicit OptionalLabel(std::string string);

      /**
      * Constructor.
      *
      * \param string  label string that precedes value in file format
      */
      explicit OptionalLabel(const char* string);

      /**
      * Copy constructor.
      *
      * \param other OptionalLabel being cloned.
      */
      OptionalLabel(const OptionalLabel& other);

      /**
      * Destructor.
      */
      virtual ~OptionalLabel();

   };

} 
#endif
