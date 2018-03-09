
   // Point-to-Point Communication

   inline bool
   Status::Is_cancelled() const
   {
     int t;
     (void)MPI_Test_cancelled(const_cast<MPI_Status*>(&mpiStatus_), &t);
     return OPAL_INT_TO_BOOL(t);
   }

   // Status Access

   inline int
   Status::Get_source() const
   {
     int source;
     source = mpiStatus_.MPI_SOURCE;
     return source;
   }

   inline void
   Status::Set_source(int source)
   {  mpiStatus_.MPI_SOURCE = source; }

   inline int
   Status::Get_tag() const
   {
     int tag;
     tag = mpiStatus_.MPI_TAG;
     return tag;
   }

   inline void
   Status::Set_tag(int tag)
   {  mpiStatus_.MPI_TAG = tag; }

   inline int
   Status::Get_error() const
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
   {
      MPI_Status_set_cancelled(&mpiStatus_, (int) flag);
   }

