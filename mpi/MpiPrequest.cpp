/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
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
      (void) MPI_Startall(count, mpi_requests);
      for (i=0; i < count; i++) {
        array_of_requests[i].mpiRequest_ = mpi_requests[i] ;
      }
      delete [] mpi_requests;
   }

}
}

