#ifdef UTIL_MPI
#ifndef UTIL_MPI_OP_H
#define UTIL_MPI_OP_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <mpi.h>

namespace Util {
namespace Mpi {

   class Datatype;

   class Op {
   public:

      // Default Constructor
      Op();

      // Copy constructor
      Op(const Op& op);

      // Copy from MPI_Op
      Op(MPI_Op i);

      // Destructor
      virtual ~Op();

      // Assignment
      Op& operator = (const Op& op);

      // Assignment from MPI_Op
      Op& operator = (const MPI_Op &i);

      // Conversion functions
      operator MPI_Op () const;

      // Equality comparison
      bool operator == (const Op &a);

      // Inequality comparison
      bool operator != (const Op &a);

      virtual void Free();

      virtual void Reduce_local(const void *inbuf, void *inoutbuf, int count,
                                const Datatype& datatype) const;

      virtual bool Is_commutative(void) const;

   private:

      MPI_Op mpiOp_;

   };

#include "MpiOp_inln.h"

}
}
#endif
#endif
