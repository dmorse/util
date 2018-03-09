/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
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
  
