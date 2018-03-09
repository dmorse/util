/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiStatus.h"
#include "MpiDatatype.h"
#include <util/global.h>

namespace Util {
namespace Mpi {

   // Point-to-Point Communication

   int Status::Get_count(const Datatype& datatype) const
   {
     int count;
     (void)MPI_Get_count(const_cast<MPI_Status*>(&mpiStatus_), datatype, &count);
     return count;
   }

   int Status::Get_elements(const Datatype& datatype) const
   {
     int count;
     (void)MPI_Get_elements(const_cast<MPI_Status*>(&mpiStatus_), datatype, &count);
     return count;
   }

   void Status::Set_elements(const Datatype& datatype, int count)
   {  MPI_Status_set_elements(&mpiStatus_, datatype, count); }

}
}

