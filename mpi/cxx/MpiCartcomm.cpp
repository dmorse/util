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

#include "MpiCartcomm.h"

namespace Util {
namespace Mpi {

   Cartcomm Cartcomm::Sub(const bool remain_dims[]) const
   {
      int ndims;
      MPI_Cartdim_get(mpiComm_, &ndims);
      int* int_remain_dims = new int[ndims];
      for (int i=0; i<ndims; i++) {
         int_remain_dims[i] = (int)remain_dims[i];
      }
      MPI_Comm newcomm;
      MPI_Cart_sub(mpiComm_, int_remain_dims, &newcomm);
      delete [] int_remain_dims;
      return newcomm;
   }

   int Cartcomm::Map(int ndims, const int dims[], const bool periods[]) 
   const
   {
      int *int_periods = new int [ndims];
      for (int i=0; i<ndims; i++) {
         int_periods[i] = (int) periods[i];
      }
      int newrank;
      MPI_Cart_map(mpiComm_, ndims, const_cast<int *>(dims), int_periods,
                   &newrank);
      delete [] int_periods;
      return newrank;
   }

   Cartcomm& Cartcomm::Clone() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      Cartcomm* dup = new Cartcomm(newcomm);
      return *dup;
   }

}
}
