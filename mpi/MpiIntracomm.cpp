/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiIntraComm.h"
#include <util/global.h>

namespace Util {
namespace Mpi {

   // Default constructor.
   Intracomm::Intracomm()
    : Comm()
   {}

   // Copy
   Intracomm::Intracomm(const Comm& data)
    : Comm(data)
   {}

   // Copy constructor
   Intracomm::Intracomm(const Intracomm& data)
    : Comm(data.mpiComm_)
   {}

}
}
