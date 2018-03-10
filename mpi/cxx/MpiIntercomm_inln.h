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

   inline Intercomm
   Intercomm::Dup() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      return newcomm;
   }

   inline Intercomm&
   Intercomm::Clone() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      Intercomm* dup = new Intercomm(newcomm);
      return *dup;
   }

   inline int
   Intercomm::Get_remote_size() const
   {
      int size;
      MPI_Comm_remote_size(mpiComm_, &size);
      return size;
   }

   inline Group
   Intercomm::Get_remote_group() const
   {
      MPI_Group group;
      MPI_Comm_remote_group(mpiComm_, &group);
      return group;
   }

   inline Intracomm
   Intercomm::Merge(bool high) const
   {
      MPI_Comm newcomm;
      MPI_Intercomm_merge(mpiComm_, (int)high, &newcomm);
      return newcomm;
   }

