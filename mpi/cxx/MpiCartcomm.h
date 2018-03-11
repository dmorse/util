#ifdef UTIL_MPI
#ifndef UTIL_MPI_CARTCOMM_H
#define UTIL_MPI_CARTCOMM_H

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
* repository that was cloned from the github server in March 2018. 
* A list of copyright holders for the ompi source code is given in 
* the file named ompiCopyright in the same directory as this file. 
*/

#include "MpiIntracomm.h"

namespace Util {
namespace Mpi {

   class Cartcomm : public Intracomm
   {
   
   public:
   
      // Default constructor
      Cartcomm()
      { }
   
      // Copy constructor.
      Cartcomm(const Cartcomm& data)
       : Intracomm(data.mpiComm_)
      { }
   
      // Copy from Comm (base class).
      Cartcomm(const Comm& data)
       : Intracomm(data)
      {}
   
      // Copy from MPI_Comm.
      inline Cartcomm(const MPI_Comm& data);
   
      // Assignment.
      Cartcomm& operator = (const Cartcomm& data)
      { mpiComm_ = data.mpiComm_; return *this; }
   
      // Assignment from Comm.
      Cartcomm& operator = (const Comm& data) 
      {  mpiComm_ = data; return *this; }
   
      // Assignment from MPI_Comm.
      Cartcomm& operator = (const MPI_Comm& data) 
      {  mpiComm_ = data; return *this; }
   
      // Groups, Contexts, and Communicators
   
      Cartcomm 
      Dup() const;
   
      virtual 
      Cartcomm& Clone() const;
   
      // Groups, Contexts, and Communicators
   
      virtual 
      int Get_dim() const;
   
      virtual 
      void Get_topo(int maxdims, int dims[], bool periods[],
                            int coords[]) const;
   
      virtual 
      int Get_cart_rank(const int coords[]) const;
   
      virtual 
      void Get_coords(int rank, int maxdims, int coords[]) const;
   
      virtual 
      void Shift(int direction, int disp, 
                 int &rank_source, int &rank_dest) const;
   
      virtual 
      Cartcomm Sub(const bool remain_dims[]) const;
   
      virtual 
      int Map(int ndims, const int dims[], const bool periods[]) const;
   
   };
   
   #include "MpiCartcomm_inln.h"

}
}
#endif
#endif
