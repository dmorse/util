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
* deprecated in MPI 2.2, and slated for removal in MPI 3.
*
* The code in this and other files in the same directory that implement
* a variant of the MPI C++ bindings was derived from the implementation 
* provided in the Open MPI (ompi) package, starting from corresponding 
* files in the ompi/ompi/mpi/cxx directory of an ompi source code 
* repository that was cloned from the github server in March 2018. A 
* list of copyright holders for the ompi source code is given in the 
* file named ompiCopyright in the same directory as this file. 
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

