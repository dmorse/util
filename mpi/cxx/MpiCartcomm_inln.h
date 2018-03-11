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


   //   ========   Cartcomm member functions  ========

   inline
   Cartcomm::Cartcomm(const MPI_Comm& data) {
      int initFlag = 0;
      MPI_Initialized(&initFlag);
      if (initFlag && (data != MPI_COMM_NULL)) {
         //if (MPI_Initialized() && (data != MPI_COMM_NULL)) {
         int status = 0;
         MPI_Topo_test(data, &status) ;
         if (status == MPI_CART)
           mpiComm_ = data;
         else
           mpiComm_ = MPI_COMM_NULL;
      }
      else {
         mpiComm_ = data;
      }
   }

   // Groups, Contexts, and Communicators

   inline
   Cartcomm Cartcomm::Dup() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      return newcomm;
   }

   //
   //  Process Topologies
   //

   inline
   int Cartcomm::Get_dim() const
   {
      int ndims;
      MPI_Cartdim_get(mpiComm_, &ndims);
      return ndims;
   }

   inline void
   Cartcomm::Get_topo(int maxdims, int dims[], bool periods[],
                       int coords[]) const
   {
      int *int_periods = new int [maxdims];
      int i;
      for (i=0; i<maxdims; i++) {
         int_periods[i] = (int)periods[i];
      }
      MPI_Cart_get(mpiComm_, maxdims, dims, int_periods, coords);
      for (i=0; i<maxdims; i++) {
         periods[i] = OPAL_INT_TO_BOOL(int_periods[i]);
      }
      delete [] int_periods;
   }

   inline
   int Cartcomm::Get_cart_rank(const int coords[]) const
   {
      int myrank;
      MPI_Cart_rank(mpiComm_, const_cast<int *>(coords), &myrank);
      return myrank;
   }

   inline 
   void Cartcomm::Get_coords(int rank, int maxdims, int coords[]) const
   {
      MPI_Cart_coords(mpiComm_, rank, maxdims, coords);
   }

   inline 
   void Cartcomm::Shift(int direction, int disp,
                        int &rank_source, int &rank_dest) const
   {  MPI_Cart_shift(mpiComm_, direction, disp, &rank_source, &rank_dest); }

