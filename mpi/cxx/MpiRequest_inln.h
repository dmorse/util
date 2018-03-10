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

   inline void
   Request::Wait()
   {
      MPI_Wait(&mpiRequest_, MPI_STATUS_IGNORE);
   }

   inline void
   Request::Wait(Status &status)
   {
      MPI_Wait(&mpiRequest_, &status.mpiStatus_);
   }

   inline bool
   Request::Test(Status &status)
   {
      int t;
      MPI_Test(&mpiRequest_, &t, &status.mpiStatus_);
      return (bool)(t);
   }

   inline void
   Request::Free()
   {
      MPI_Request_free(&mpiRequest_);
   }

   inline bool
   Request::Test()
   {
      int t;
      MPI_Test(&mpiRequest_, &t, MPI_STATUS_IGNORE);
      return (bool)(t);
   }

   inline void
   Request::Cancel(void) const
   {
      MPI_Cancel(const_cast<MPI_Request *>(&mpiRequest_));
   }

   inline bool Request::Get_status(Status& status) const
   {
      int flag = 0;
      MPI_Status c_status;

      // Call the underlying MPI function rather than simply returning
      // status.mpiStatus_ because we may have to invoke the generalized
      // request query function
      MPI_Request_get_status(mpiRequest_, &flag, &c_status);
      if (flag) {
          status = c_status;
      }
        return (bool)(flag);
   }

   inline bool Request::Get_status() const
   {
        int flag;

        // Call the underlying MPI function rather than simply returning
        // status.mpiStatus_ because we may have to invoke the generalized
        // request query function
        MPI_Request_get_status(mpiRequest_, &flag, MPI_STATUS_IGNORE);
        return (bool)(flag);
   }

