#ifdef UTIL_MPI
#ifndef UTIL_MPI_GRAPHCOMM_H
#define UTIL_MPI_GRAPHCOMM_H

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

#include "MpiIntracomm.h"

namespace Util {
namespace Mpi {
   
   class Graphcomm : public Intracomm {
   public:
   
      // Default constructor
      Graphcomm()
      {}
  
      // Copy constructor. 
      Graphcomm(const Graphcomm& data) 
       : Intracomm(data.mpiComm_) 
      { }
   
      // Copy from Comm.
      Graphcomm(const Comm& data) 
       : Intracomm(data) 
      {}
   
      // Copy from MPI_Comm
      Graphcomm(const MPI_Comm& data);

      // Assignment.
      Graphcomm& operator=(const Graphcomm& data) 
      {  mpiComm_ = data.mpiComm_; return *this; }
   
      // Assignment from Comm.
      Graphcomm& operator=(const Comm& data) 
      {  mpiComm_ = data; return *this; }
   
      // Assignment from MPI_Comm.
      Graphcomm& operator=(const MPI_Comm& data) 
      {  mpiComm_ = data; return *this; }
   
      // Groups, Contexts, and Communicators
   
      Graphcomm Dup() const;
   
      virtual 
      Graphcomm& Clone() const;
   
      //  Process Topologies
   
      virtual 
      void Get_dims(int nnodes[], int nedges[]) const;
   
      virtual 
      void Get_topo(int maxindex, int maxedges, int index[], int edges[]) 
      const;
   
      virtual 
      int Get_neighbors_count(int rank) const;
   
      virtual 
      void Get_neighbors(int rank, int maxneighbors, int neighbors[]) const;
   
      virtual 
      int Map(int nnodes, const int index[], const int edges[]) const;
   
   };

}
}
#endif
#endif
