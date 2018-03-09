/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiGroup.h"
#include <util/global.h>

namespace Util {
namespace Mpi {

   Group Group::Range_incl(int n, const int ranges[][3]) const
   {
      MPI_Group newgroup;
      MPI_Group_range_incl(mpiGroup_, n,
                           (int(*)[3]) ranges, &newgroup);
      return newgroup;
   }

   Group Group::Range_excl(int n, const int ranges[][3]) const
   {
      MPI_Group newgroup;
      MPI_Group_range_excl(mpiGroup_, n,
                           (int(*)[3]) ranges,
                            &newgroup);
      return newgroup;
   }

}
}

