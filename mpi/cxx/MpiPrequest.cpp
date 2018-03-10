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

#include "MpiPrequest.h"

namespace Util {
namespace Mpi {

   void Prequest::Startall(int count,  Prequest array_of_requests[])
   {
      // Convert the array of Prequests to an array of MPI_requests
      MPI_Request* mpi_requests = new MPI_Request[count];
      int i;
      for (i=0; i < count; i++) {
         mpi_requests[i] = array_of_requests[i];
      }
      MPI_Startall(count, mpi_requests);
      for (i=0; i < count; i++) {
         array_of_requests[i].mpiRequest_ = mpi_requests[i] ;
      }
      delete [] mpi_requests;
   }

}
}

