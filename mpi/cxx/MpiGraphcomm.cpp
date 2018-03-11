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

#include "MpiGraphcomm.h"

namespace Util {
namespace Mpi {

   Graphcomm::Graphcomm(const MPI_Comm& data) 
   {
      int initFlag;
      MPI_Initialized(&initFlag);
      if (initFlag && (data != MPI_COMM_NULL)) {
         int status = 0;
         MPI_Topo_test(data, &status) ;
         if (status == MPI_GRAPH) {
            mpiComm_ = data;
         } else {
            mpiComm_ = MPI_COMM_NULL;
         }
      } else {
         mpiComm_ = data;
      }
   }

}
}
