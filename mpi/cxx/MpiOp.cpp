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

#include "MpiOp.h"
#include "MpiDatatype.h"

namespace Util {
namespace Mpi {

   inline 
   void Op::Free()
   {  MPI_Op_free(&mpiOp_); }
   
   inline void
   Op::Reduce_local(const void *inbuf, void *inoutbuf, int count,
                    const Datatype& datatype) const
   {
      MPI_Reduce_local(const_cast<void*>(inbuf), inoutbuf, count,
                       datatype, mpiOp_);
   }
   
   inline bool
   Op::Is_commutative(void) const
   {
      int commute;
      MPI_Op_commutative(mpiOp_, &commute);
      return (bool) commute;
   }

}
}
  
