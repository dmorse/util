#ifdef UTIL_MPI
#ifndef UTIL_MPI_OP_H
#define UTIL_MPI_OP_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

/*
* The code in this file and related files implements a variant of the
* MPI 1.2 C++ bindings. Development of this version of the MPI C++ 
* bindings was motivated by the fact that the C++ bindings were 
* deprecated in MPI 2.2 and slated for removal in MPI 3.
*
* The code in this and other files in the same directory that implement
* a variant of the MPI C++ bindings was derived from the implementation 
* provided in the Open MPI (ompi) package, starting from corresponding 
* files in the ompi/ompi/mpi/cxx directory of an ompi source code 
* repository that was cloned from the github server in March 2018. A 
* list of copyright holders for the ompi source code is given in the 
* file named ompiCopyright in the same directory as this file. 
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
