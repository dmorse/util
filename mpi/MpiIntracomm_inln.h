
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

   #if 0
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
   #endif

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

   #if 0
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

   inline Intercomm
   Intracomm::Create_intercomm(int local_leader,
                       const Comm& peer_comm,
                       int remote_leader, int tag) const
   {
     MPI_Comm newintercomm;
     (void)MPI_Intercomm_create(mpiComm_, local_leader, peer_comm,
                    remote_leader, tag, &newintercomm);
     return newintercomm;
   }

   inline Cartcomm
   Intracomm::Create_cart(int ndims, const int dims[],
                      const bool periods[], bool reorder) const
   {
     int *int_periods = new int [ndims];
     for (int i=0; i<ndims; i++)
       int_periods[i] = (int) periods[i];

     MPI_Comm newcomm;
     (void)MPI_Cart_create(mpiComm_, ndims, const_cast<int *>(dims),
                 int_periods, (int)reorder, &newcomm);
     delete [] int_periods;
     return newcomm;
   }

   inline Graphcomm
   Intracomm::Create_graph(int nnodes, const int index[],
                       const int edges[], bool reorder) const
   {
     MPI_Comm newcomm;
     (void)MPI_Graph_create(mpiComm_, nnodes, const_cast<int *>(index),
                            const_cast<int *>(edges), (int)reorder, &newcomm);
     return newcomm;
   }
   #endif

   #if 0
   //
   // Process Creation and Management
   //

   inline Intercomm
   Intracomm::Accept(const char* port_name,
                     const Info& info,
                     int root) const
   {
     MPI_Comm newcomm;
     (void) MPI_Comm_accept(const_cast<char *>(port_name), info, root, mpiComm_,
                &newcomm);
     return newcomm;
   }


   inline Intercomm
   Intracomm::Connect(const char* port_name,
                      const Info& info,
                      int root) const
   {
     MPI_Comm newcomm;
     (void) MPI_Comm_connect(const_cast<char *>(port_name), info, root, mpiComm_,
                 &newcomm);
     return newcomm;
   }


   inline Intercomm
   Intracomm::Spawn(const char* command, const char* argv[],
                    int maxprocs, const Info& info,
                    int root) const
   {
     MPI_Comm newcomm;
     (void) MPI_Comm_spawn(const_cast<char *>(command), const_cast<char **>(argv), maxprocs,
               info, root, mpiComm_, &newcomm,
               (int *)MPI_ERRCODES_IGNORE);
     return newcomm;
   }


   inline Intercomm
   Intracomm::Spawn(const char* command, const char* argv[],
                                int maxprocs, const Info& info,
                                int root, int array_of_errcodes[]) const
   {
     MPI_Comm newcomm;
     (void) MPI_Comm_spawn(const_cast<char *>(command), const_cast<char **>(argv), maxprocs,
                           info, root, mpiComm_, &newcomm,
               array_of_errcodes);
     return newcomm;
   }


   inline Intercomm
   Intracomm::Spawn_multiple(int count,
                         const char* array_of_commands[],
                         const char** array_of_argv[],
                         const int array_of_maxprocs[],
                         const Info array_of_info[], int root)
   {
     MPI_Comm newcomm;
     MPI_Info *const array_of_mpi_info =
         convert_info_to_mpi_info(count, array_of_info);

     MPI_Comm_spawn_multiple(count, const_cast<char **>(array_of_commands),
                 const_cast<char ***>(array_of_argv),
                             const_cast<int *>(array_of_maxprocs),
                 array_of_mpi_info, root,
                 mpiComm_, &newcomm, (int *)MPI_ERRCODES_IGNORE);
     delete[] array_of_mpi_info;
     return newcomm;
   }

   inline MPI_Info *
   Intracomm::convert_info_to_mpi_info(int p_nbr, const Info p_info_tbl[])
   {
      MPI_Info *const mpi_info_tbl = new MPI_Info [p_nbr];

      for (int i_tbl=0; i_tbl < p_nbr; i_tbl++) {
          mpi_info_tbl[i_tbl] = p_info_tbl[i_tbl];
      }

      return mpi_info_tbl;
   }

   inline Intercomm
   Intracomm::Spawn_multiple(int count,
                             const char* array_of_commands[],
                             const char** array_of_argv[],
                             const int array_of_maxprocs[],
                             const Info array_of_info[], int root,
                             int array_of_errcodes[])
   {
     MPI_Comm newcomm;
     MPI_Info *const array_of_mpi_info =
         convert_info_to_mpi_info(count, array_of_info);

     MPI_Comm_spawn_multiple(count, const_cast<char **>(array_of_commands),
                             const_cast<char ***>(array_of_argv),
                             const_cast<int *>(array_of_maxprocs),
                             array_of_mpi_info, root,
                             mpiComm_, &newcomm, array_of_errcodes);
     delete[] array_of_mpi_info;
     return newcomm;
   }
   #endif

