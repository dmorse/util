/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiIntercomm.h"

namespace Util {
namespace Mpi {

   Intercomm Intercomm::Create(const Group& group) const
   {
      MPI_Comm newcomm;
      MPI_Comm_create(mpiComm_, (MPI_Group) group, &newcomm);
      return newcomm;
   }

   Intercomm Intercomm::Split(int color, int key) const
   {
      MPI_Comm newcomm;
      MPI_Comm_split(mpiComm_, color, key, &newcomm);
      return newcomm;
   }

}
}

