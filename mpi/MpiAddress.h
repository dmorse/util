#ifdef UTIL_MPI
#ifndef UTIL_MPI_ADDRESS_H
#define UTIL_MPI_ADDRESS_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <mpi.h>

namespace Util {
namespace Mpi {

  typedef MPI_Aint Aint;
  typedef MPI_Fint Fint;
  typedef MPI_Offset Offset;

}
}
#endif
#endif

