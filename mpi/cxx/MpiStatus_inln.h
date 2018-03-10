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


   // Point-to-Point Communication

   inline 
   bool Status::Is_cancelled() const
   {
      int t;
      (void)MPI_Test_cancelled(const_cast<MPI_Status*>(&mpiStatus_), &t);
      return OPAL_INT_TO_BOOL(t);
   }

   // Status Access

   inline 
   int Status::Get_source() const
   {
      int source;
      source = mpiStatus_.MPI_SOURCE;
      return source;
   }

   inline 
   void Status::Set_source(int source)
   {  mpiStatus_.MPI_SOURCE = source; }

   inline 
   int Status::Get_tag() const
   {
      int tag;
      tag = mpiStatus_.MPI_TAG;
      return tag;
   }

   inline 
   void Status::Set_tag(int tag)
   {  mpiStatus_.MPI_TAG = tag; }

   inline 
   int Status::Get_error() const
   {
      int error;
      error = mpiStatus_.MPI_ERROR;
      return error;
   }

   inline void
   Status::Set_error(int error)
   {  mpiStatus_.MPI_ERROR = error; }

   inline void
   Status::Set_cancelled(bool flag)
   {  MPI_Status_set_cancelled(&mpiStatus_, (int) flag); }

