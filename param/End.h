#ifndef UTIL_END_H
#define UTIL_END_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/param/ParamComponent.h>
#include <util/param/Label.h>

#include <string>

namespace Util
{

   /**
   * End bracket of a ParamComposite parameter block.
   *
   * \ingroup Param_Module
   */
   class End : public ParamComponent
   {

   public:

      /// Constructor.
      End();

      /// Destructor.
      virtual ~End();

      /**
      * Read the closing bracket.
      *
      * \param in input stream
      */
      virtual void readParam(std::istream &in);

      /**
      * Write the closing bracket.
      *
      * \param out output stream
      */
      virtual void writeParam(std::ostream &out);

      /// Do-nothing implementation of virtual resetParam function.
      void resetParam();

   private:

      Label label_;

   };

} 
#endif
