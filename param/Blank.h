#ifndef UTIL_BLANK_H
#define UTIL_BLANK_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, David Morse (morse012@um.edu) 
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ParamComponent.h>

namespace Util
{

   /**
   * An empty line within a parameter file. 
   *
   * A Param represents an empty line within a file format that is
   * represented as a ParamComposite.
   *
   * \ingroup Param_Module
   */
   class Blank : public ParamComponent
   {

   public:

      /**
      * Constructor.
      */
      Blank();

      /**
      * Destructor
      */
      virtual ~Blank();

      /**
      * Read a blank line
      *
      * Skips white space of any length up to and including the end of
      * the current line. Text that is not white space is not consumed,
      * so that it is read as the next item of the parameter file.
      *
      * \param in input stream
      */
      virtual void readParam(std::istream &in);

      /**
      * Write a blank line
      *
      * \param out output stream
      */
      virtual void writeParam(std::ostream &out) const;

   };

} 
#endif
