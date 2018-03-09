
   inline
   Intracomm::Intracomm(MPI_Comm data) 
   {
      int initFlag = 0;
      MPI_Initialized(&initFlag);
      if (initFlag && (data != MPI_COMM_NULL)) {
         int interFlag;
         MPI_Comm_test_inter(data, &interFlag);
         if (interFlag) {
            mpiComm_ = MPI_COMM_NULL;
         } else {
            mpiComm_ = data;
         }
      } else {
         mpiComm_ = data;
      }
   }

   inline void
   Intracomm::Scan(const void *sendbuf, void *recvbuf, int count,
        const Datatype & datatype, const Op& op) const
   {
      MPI_Scan(const_cast<void *>(sendbuf), recvbuf, count, datatype, op, mpiComm_);
   }

   inline void
   Intracomm::Exscan(const void *sendbuf, void *recvbuf, int count,
                     const Datatype & datatype,
                     const Op& op) const
   {
      MPI_Exscan(const_cast<void *>(sendbuf), recvbuf, count, datatype, op, mpiComm_);
   }

   inline Intracomm
   Intracomm::Dup() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      return newcomm;
   }

   inline Intracomm&
   Intracomm::Clone() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      Intracomm* dup = new Intracomm(newcomm);
      return *dup;
   }

   inline Intracomm
   Intracomm::Create(const Group& group) const
   {
      MPI_Comm newcomm;
      MPI_Comm_create(mpiComm_, group, &newcomm);
      return newcomm;
   }

   inline Intracomm
   Intracomm::Split(int color, int key) const
   {
     MPI_Comm newcomm;
     (void)MPI_Comm_split(mpiComm_, color, key, &newcomm);
     return newcomm;
   }


