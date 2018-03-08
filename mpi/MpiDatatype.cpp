
/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiDatatype.h"
#include <util/global.h>
#include <complex>

namespace Util {
namespace Mpi {

void
Datatype::Free()
{
    (void)MPI_Type_free(&mpiDatatype_);
}

}
}
