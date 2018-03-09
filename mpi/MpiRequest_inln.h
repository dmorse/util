
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
        (void)MPI_Request_get_status(mpiRequest_, &flag, MPI_STATUS_IGNORE);
        return (bool)(flag);
   }

