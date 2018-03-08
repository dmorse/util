
   // Point-to-Point Send and Receive

   inline void
   Comm::Send(const void *buf, int count,
           const Datatype & datatype, int dest, int tag) const
   {
      MPI_Send(const_cast<void *>(buf), count, datatype, dest, tag, mpiComm_);
   }

   #if 0
   inline void
   Comm::Recv(void *buf, int count, const Datatype & datatype,
           int source, int tag, Status & status) const
   {
      MPI_Recv(buf, count, datatype,
               source, tag, mpiComm_, &status.mpi_status);
   }
   #endif

   inline void
   Comm::Recv(void *buf, int count, const Datatype & datatype,
                       int source, int tag) const
   {
      MPI_Recv(buf, count, datatype, source,
              tag, mpiComm_, MPI_STATUS_IGNORE);
   }

   inline void
   Comm::Bsend(const void *buf, int count,
            const Datatype & datatype, int dest, int tag) const
   {
      MPI_Bsend(const_cast<void *>(buf), count, datatype,
             dest, tag, mpiComm_);
   }

   inline void
   Comm::Ssend(const void *buf, int count,
                    const Datatype & datatype, int dest, int tag) const
   {
      MPI_Ssend(const_cast<void *>(buf), count,  datatype,
                dest, tag, mpiComm_);
   }

   inline void
   Comm::Rsend(const void *buf, int count,
            const Datatype & datatype, int dest, int tag) const
   {
      MPI_Rsend(const_cast<void *>(buf), count, datatype, dest,
                tag, mpiComm_);
   }

   #if 0
   inline Request
   Comm::Isend(const void *buf, int count,
            const Datatype & datatype, int dest, int tag) const
   {
      MPI_Request request;
      (void)MPI_Isend(const_cast<void *>(buf), count, datatype,
                      dest, tag, mpiComm_, &request);
      return request;
   }

   inline Request
   Comm::Ibsend(const void *buf, int count,
             const Datatype & datatype, int dest, int tag) const
   {
      MPI_Request request;
      MPI_Ibsend(const_cast<void *>(buf), count, datatype,
                 dest, tag, mpiComm_, &request);
      return request;
   }

   inline Request
   Comm::Issend(const void *buf, int count,
             const Datatype & datatype, int dest, int tag) const
   {
      MPI_Request request;
      MPI_Issend(const_cast<void *>(buf), count, datatype,
                 dest, tag, mpiComm_, &request);
      return request;
   }

   inline Request
   Comm::Irsend(const void *buf, int count,
             const Datatype & datatype, int dest, int tag) const
   {
      MPI_Request request;
      MPI_Irsend(const_cast<void *>(buf), count, datatype,
                 dest, tag, mpiComm_, &request);
      return request;
   }

   inline Request
   Comm::Irecv(void *buf, int count,
            const Datatype & datatype, int source, int tag) const
   {
      MPI_Request request;
      MPI_Irecv(buf, count, datatype, source,
                tag, mpiComm_, &request);
      return request;
   }

   inline bool
   Comm::Iprobe(int source, int tag, Status & status) const
   {
      int t;
      MPI_Iprobe(source, tag, mpiComm_, &t, &status.mpi_status);
      return bool(t);
   }

   inline bool
   Comm::Iprobe(int source, int tag) const
   {
     int t;
     (void)MPI_Iprobe(source, tag, mpiComm_, &t, MPI_STATUS_IGNORE);
     return bool(t);
   }

   inline void
   Comm::Probe(int source, int tag, Status & status) const
   {
     (void)MPI_Probe(source, tag, mpiComm_, &status.mpi_status);
   }

   inline void
   Comm::Probe(int source, int tag) const
   {
     (void)MPI_Probe(source, tag, mpiComm_, MPI_STATUS_IGNORE);
   }

   inline Prequest
   Comm::Send_init(const void *buf, int count,
                const Datatype & datatype, int dest, int tag) const
   {
     MPI_Request request;
     (void)MPI_Send_init(const_cast<void *>(buf), count, datatype,
                 dest, tag, mpiComm_, &request);
     return request;
   }

   inline Prequest
   Comm::Bsend_init(const void *buf, int count,
                 const Datatype & datatype, int dest, int tag) const
   {
     MPI_Request request;
     (void)MPI_Bsend_init(const_cast<void *>(buf), count, datatype,
                  dest, tag, mpiComm_, &request);
     return request;
   }

   inline Prequest
   Comm::Ssend_init(const void *buf, int count,
                 const Datatype & datatype, int dest, int tag) const
   {
     MPI_Request request;
     (void)MPI_Ssend_init(const_cast<void *>(buf), count, datatype,
                  dest, tag, mpiComm_, &request);
     return request;
   }

   inline Prequest
   Comm::Rsend_init(const void *buf, int count,
                 const Datatype & datatype, int dest, int tag) const
   {
     MPI_Request request;
     (void)MPI_Rsend_init(const_cast<void *>(buf), count,  datatype,
                  dest, tag, mpiComm_, &request);
     return request;
   }

   inline Prequest
   Comm::Recv_init(void *buf, int count,
                const Datatype & datatype, int source, int tag) const
   {
     MPI_Request request;
     (void)MPI_Recv_init(buf, count, datatype, source,
                 tag, mpiComm_, &request);
     return request;
   }
   #endif

   #if 0
   inline void
   Comm::Sendrecv(const void *sendbuf, int sendcount,
               const Datatype & sendtype, int dest, int sendtag,
               void *recvbuf, int recvcount,
               const Datatype & recvtype, int source,
               int recvtag, Status & status) const
   {
     (void)MPI_Sendrecv(const_cast<void *>(sendbuf), sendcount,
                sendtype,
                dest, sendtag, recvbuf, recvcount,
                recvtype,
                source, recvtag, mpiComm_, &status.mpi_status);
   }
   #endif

   inline void
   Comm::Sendrecv(const void *sendbuf, int sendcount,
               const Datatype & sendtype, int dest, int sendtag,
               void *recvbuf, int recvcount,
               const Datatype & recvtype, int source,
               int recvtag) const
   {
     (void)MPI_Sendrecv(const_cast<void *>(sendbuf), sendcount,
                sendtype,
                dest, sendtag, recvbuf, recvcount,
                recvtype,
                source, recvtag, mpiComm_, MPI_STATUS_IGNORE);
   }

   #if 0
   inline void
   Comm::Sendrecv_replace(void *buf, int count,
                   const Datatype & datatype, int dest,
                   int sendtag, int source,
                   int recvtag, Status & status) const
   {
      MPI_Sendrecv_replace(buf, count, datatype, dest,
                           sendtag, source, recvtag,
                           mpiComm_,
                           &status.mpi_status);
   }
   #endif

   inline void
   Comm::Sendrecv_replace(void *buf, int count,
                          const Datatype & datatype, int dest,
                          int sendtag, int source,
                          int recvtag) const
   {
      MPI_Sendrecv_replace(buf, count, datatype, dest,
                           sendtag, source, recvtag, mpiComm_,
                           MPI_STATUS_IGNORE);
   }

   //
   // Groups, Contexts, and Communicators
   //

   #if 0
   inline Group
   Comm::Get_group() const
   {
      MPI_Group group;
      MPI_Comm_group(mpiComm_, &group);
      return group;
   }
   #endif

   inline int
   Comm::Get_size() const
   {
      int size;
      MPI_Comm_size (mpiComm_, &size);
      return size;
   }

   inline int
   Comm::Get_rank() const
   {
      int myrank;
      MPI_Comm_rank (mpiComm_, &myrank);
      return myrank;
   }

   inline int
   Comm::Compare(const Comm & comm1,
              const Comm & comm2)
   {
     int result;
     (void)MPI_Comm_compare(comm1, comm2, &result);
     return result;
   }

   inline void
   Comm::Free(void)
   {
       (void)MPI_Comm_free(&mpiComm_);
   }

   inline bool
   Comm::Is_inter() const
   {
      int t;
      MPI_Comm_test_inter(mpiComm_, &t);
      return bool(t);
   }
   #if 0
   #endif

   //
   // Collective Communication
   //

   inline void
   Comm::Barrier() const
   {
      (void)MPI_Barrier(mpiComm_);
   }

   inline void
   Comm::Bcast(void *buffer, int count,
                    const Datatype& datatype, int root) const
   {
      MPI_Bcast(buffer, count, datatype, root, mpiComm_);
   }

   inline void
   Comm::Gather(const void *sendbuf, int sendcount,
                     const Datatype & sendtype,
                     void *recvbuf, int recvcount,
                     const Datatype & recvtype, int root) const
   {
      MPI_Gather(const_cast<void *>(sendbuf), sendcount, sendtype,
                 recvbuf, recvcount, recvtype, root, mpiComm_);
   }

   inline void
   Comm::Gatherv(const void *sendbuf, int sendcount,
                      const Datatype & sendtype, void *recvbuf,
                      const int recvcounts[], const int displs[],
                      const Datatype & recvtype, int root) const
   {
      MPI_Gatherv(const_cast<void *>(sendbuf), sendcount,  sendtype,
                  recvbuf, const_cast<int *>(recvcounts),
                  const_cast<int *>(displs),
                         recvtype, root, mpiComm_);
   }

   inline void
   Comm::Scatter(const void *sendbuf, int sendcount,
                      const Datatype & sendtype,
                      void *recvbuf, int recvcount,
                      const Datatype & recvtype, int root) const
   {
      MPI_Scatter(const_cast<void *>(sendbuf), sendcount, sendtype,
                  recvbuf, recvcount, recvtype, root, mpiComm_);
   }

   inline void
   Comm::Scatterv(const void *sendbuf, const int sendcounts[],
                       const int displs[], const Datatype & sendtype,
                       void *recvbuf, int recvcount,
                       const Datatype & recvtype, int root) const
   {
       MPI_Scatterv(const_cast<void *>(sendbuf),
                    const_cast<int *>(sendcounts),
                    const_cast<int *>(displs), sendtype,
                    recvbuf, recvcount, recvtype,
                    root, mpiComm_);
   }

   inline void
   Comm::Allgather(const void *sendbuf, int sendcount,
                        const Datatype & sendtype, void *recvbuf,
                        int recvcount, const Datatype & recvtype) const
   {
      MPI_Allgather(const_cast<void *>(sendbuf), sendcount,
                    sendtype, recvbuf, recvcount,
                    recvtype, mpiComm_);
   }

   inline void
   Comm::Allgatherv(const void *sendbuf, int sendcount,
                         const Datatype & sendtype, void *recvbuf,
                         const int recvcounts[], const int displs[],
                         const Datatype & recvtype) const
   {
      MPI_Allgatherv(const_cast<void *>(sendbuf), sendcount,
                     sendtype, recvbuf,
                     const_cast<int *>(recvcounts),
                     const_cast<int *>(displs),
                     recvtype, mpiComm_);
   }

   inline void
   Comm::Alltoall(const void *sendbuf, int sendcount,
                       const Datatype & sendtype, void *recvbuf,
                       int recvcount, const Datatype & recvtype) const
   {
       MPI_Alltoall(const_cast<void *>(sendbuf), sendcount,
                    sendtype, recvbuf, recvcount,
                    recvtype, mpiComm_);
   }

   inline void
   Comm::Alltoallv(const void *sendbuf, const int sendcounts[],
                        const int sdispls[], const Datatype & sendtype,
                        void *recvbuf, const int recvcounts[],
                        const int rdispls[],
                        const Datatype & recvtype) const
   {
      MPI_Alltoallv(const_cast<void *>(sendbuf),
                    const_cast<int *>(sendcounts),
                    const_cast<int *>(sdispls), sendtype, recvbuf,
                    const_cast<int *>(recvcounts),
                    const_cast<int *>(rdispls),
                    recvtype,mpiComm_);
   }

   inline void
   Comm::Alltoallw(const void *sendbuf, const int sendcounts[],
                        const int sdispls[], const Datatype sendtypes[],
                        void *recvbuf, const int recvcounts[],
                        const int rdispls[],
                        const Datatype recvtypes[]) const
   {
      const int comm_size = Get_size();
      MPI_Datatype *const data_type_tbl = new MPI_Datatype [2*comm_size];

      // This must be done because Datatype arrays cannot be
      // converted directly into MPI_Datatype arrays.
      for (int i_rank=0; i_rank < comm_size; i_rank++) {
          data_type_tbl[i_rank] = sendtypes[i_rank];
          data_type_tbl[i_rank + comm_size] = recvtypes[i_rank];
      }

      MPI_Alltoallw(const_cast<void *>(sendbuf),
                    const_cast<int *>(sendcounts),
                    const_cast<int *>(sdispls),
                    data_type_tbl, recvbuf,
                    const_cast<int *>(recvcounts),
                    const_cast<int *>(rdispls),
                          &data_type_tbl[comm_size], mpiComm_);

      delete[] data_type_tbl;
   }

   #if 0
   inline void
   Comm::Reduce(const void *sendbuf, void *recvbuf, int count,
                     const Datatype & datatype, const Op& op,
                     int root) const
   {
      MPI_Reduce(const_cast<void *>(sendbuf), recvbuf, count, datatype,
                 op, root, mpiComm_);
   }

   inline void
   Comm::Allreduce(const void *sendbuf, void *recvbuf, int count,
                        const Datatype & datatype, const Op& op)
   const
   {
      MPI_Allreduce (const_cast<void *>(sendbuf), recvbuf, count,
                     datatype,  op, mpiComm_);
   }

   inline void
   Comm::Reduce_scatter(const void *sendbuf, void *recvbuf,
                             int recvcounts[],
                             const Datatype & datatype,
                             const Op& op) const
   {
      MPI_Reduce_scatter(const_cast<void *>(sendbuf), recvbuf, recvcounts,
                         datatype, op, mpiComm_);
   }
   #endif

   #if 0
   // Process Creation and Management

   inline void
   Comm::Disconnect()
   {
      MPI_Comm_disconnect(&mpiComm_);
   }


   inline Intercomm
   Comm::Get_parent()
   {
      MPI_Comm parent;
      MPI_Comm_get_parent(&parent);
      return parent;
   }

   inline Intercomm
   Comm::Join(const int fd)
   {
      MPI_Comm newComm;
      MPI_Comm_join((int) fd, &newComm);
      return newComm;
   }
   #endif

   #if 0
   //
   // External Interfaces
   //

   inline void
   Comm::Get_name(char* comm_name, int& resultlen) const
   {
      MPI_Comm_get_name(mpiComm_, comm_name, &resultlen);
   }

   inline void
   Comm::Set_name(const char* comm_name)
   {
      MPI_Comm_set_name(mpiComm_, const_cast<char *>(comm_name));
   }

   //
   //Process Topologies
   //

   inline int
   Comm::Get_topology() const
   {
     int status;
     MPI_Topo_test(mpiComm_, &status);
     return status;
   }
   #endif

   //
   // Environmental Inquiry
   //

   inline void
   Comm::Abort(int errorcode)
   {
     MPI_Abort(mpiComm_, errorcode);
   }

   #if 0
   //  These C++ bindings are for MPI-2.
   //  The MPI-1.2 functions called below are all
   //  going to be deprecated and replaced in MPI-2.

   inline Errhandler
   Comm::Get_errhandler() const
   {
       MPI_Errhandler errhandler;
       MPI_Comm_get_errhandler(mpiComm_, &errhandler);
       return errhandler;
   }

   inline void
   Comm::Set_errhandler(const Errhandler& errhandler)
   {
      MPI_Comm_set_errhandler(mpiComm_, errhandler);
   }

   inline void
   Comm::Call_errhandler(int errorcode) const
   {
     (void) MPI_Comm_call_errhandler(mpiComm_, errorcode);
   }
   #endif

