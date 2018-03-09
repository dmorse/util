
/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiDatatype.h"
#include "MpiComm.h"
#include <util/global.h>

namespace Util {
namespace Mpi {

   void
   Datatype::Free()
   {
      (void)MPI_Type_free(&mpiDatatype_);
   }
  
   void
   Datatype::Pack(const void* inbuf, int incount,
                  void *outbuf, int outsize,
                  int& position, const Comm &comm) const
   {
      MPI_Pack(const_cast<void *>(inbuf), incount,  mpiDatatype_, outbuf,
               outsize, &position, comm);
   }

   void
   Datatype::Unpack(const void* inbuf, int insize,
                    void *outbuf, int outcount, int& position,
                    const Comm& comm) const
   {
      MPI_Unpack(const_cast<void *>(inbuf), insize, &position,
                 outbuf, outcount, mpiDatatype_, comm);
   }
   
   int Datatype::Pack_size(int incount, const Comm& comm) const
   {
      int size;
       MPI_Pack_size(incount, mpiDatatype_, comm, &size);
      return size;
   }
   
}
}
