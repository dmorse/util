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


   //
   // Groups, Contexts, and Communicators
   //
   
   inline
   Graphcomm Graphcomm::Dup() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      return newcomm;
   }
   
   //  Process Topologies
   
   inline 
   void Graphcomm::Get_dims(int nnodes[], int nedges[]) const
   {  MPI_Graphdims_get(mpiComm_, nnodes, nedges); }
   
   inline 
   void Graphcomm::Get_topo(int maxindex, int maxedges, int index[],
                            int edges[]) const
   {  MPI_Graph_get(mpiComm_, maxindex, maxedges, index, edges); }
   
   inline int
   Graphcomm::Get_neighbors_count(int rank) const
   {
      int nneighbors;
      MPI_Graph_neighbors_count(mpiComm_, rank, &nneighbors);
      return nneighbors;
   }
   
   inline 
   void Graphcomm::Get_neighbors(int rank, int maxneighbors,
                                 int neighbors[]) const
   {  MPI_Graph_neighbors(mpiComm_, rank, maxneighbors, neighbors); }
   
   inline 
   int Graphcomm::Map(int nnodes, const int index[],
                      const int edges[]) const
   {
      int newrank;
      MPI_Graph_map(mpiComm_, nnodes, const_cast<int *>(index), 
                    const_cast<int *>(edges), &newrank);
      return newrank;
   }
   
   inline 
   Graphcomm& Graphcomm::Clone() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      Graphcomm* dup = new Graphcomm(newcomm);
      return *dup;
   }
