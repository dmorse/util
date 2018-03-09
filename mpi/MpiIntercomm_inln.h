
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

