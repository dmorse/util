/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiComm.h"
#include "MpiInterComm.h"

namespace Util {
namespace Mpi {

   // Default constructor.
   Comm::Comm()
     : mpiComm_(MPI_COMM_NULL)
   { }
   
   // Copy constructor.
   Comm::Comm(const Comm& data)
    : mpiComm_(data.mpiComm_)
   { }
   
   // Copy construction from an MPI_Comm
   Comm::Comm(MPI_Comm data)
    : mpiComm_(data)
   { }
   
   // Destructor
   Comm::~Comm() 
   { }
   
   Intercomm Comm::Get_parent()
   {
      MPI_Comm parent;
      MPI_Comm_get_parent(&parent);
      return parent;
   }

   Intercomm Comm::Join(const int fd)
   {
      MPI_Comm newComm;
      MPI_Comm_join((int) fd, &newComm);
      return newComm;
   }
}
}

