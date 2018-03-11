/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

/*
* The code in this file implements a variant of the MPI 1.2 C++ 
* bindings. Development of this version of the MPI C++ bindings
* was motivated by the fact that the C++ bindings were officially
* deprecated in MPI 2.2, and slated for removal in MPI 3.
*
* The code in this and other files in the same directory that 
* implement a variant of the MPI C++ bindings was derived from 
* the implementation provided in the Open MPI (ompi) package, 
* starting from corresponding files in the ompi/ompi/mpi/cxx 
* directory of an ompi source code repository that was cloned 
* from the github server in March 2018. A list of copyright 
* holders for the ompi source is given in the file named 
* ompiCopyright in the same directory as this file. 
*/

#include "MpiComm.h"
#include "MpiInterComm.h"

namespace Util {
namespace Mpi {

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

   Comm& Comm::Clone() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      Comm* dup = new Comm(newcomm);
      return *dup;
   }

}
}

