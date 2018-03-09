   
   //
   // Point-to-Point Communication
   //
   
   inline Datatype
   Datatype::Create_contiguous(int count) const
   {
      MPI_Datatype newtype;
      MPI_Type_contiguous(count, mpiDatatype_, &newtype);
      return newtype;
   }
   
   inline Datatype
   Datatype::Create_vector(int count, int blocklength,
                    int stride) const
   {
      MPI_Datatype newtype;
      MPI_Type_vector(count, blocklength, stride, mpiDatatype_, &newtype);
      return newtype;
   }
   
   inline Datatype
   Datatype::Create_indexed(int count,
                            const int array_of_blocklengths[],
                            const int array_of_displacements[]) const
   {
      MPI_Datatype newtype;
      MPI_Type_indexed(count, const_cast<int *>(array_of_blocklengths),
                       const_cast<int *>(array_of_displacements), 
                       mpiDatatype_, &newtype);
      return newtype;
   }
   
   inline Datatype
   Datatype::Create_struct(int count, const int array_of_blocklengths[],
                       const Aint array_of_displacements[],
                       const Datatype array_of_types[])
   {
      MPI_Datatype newtype;
      int i;
      MPI_Datatype* type_array = new MPI_Datatype[count];
      for (i=0; i < count; i++) {
         type_array[i] = array_of_types[i];
      }
   
      MPI_Type_create_struct(count, const_cast<int *>(array_of_blocklengths),
                              const_cast<MPI_Aint*>(array_of_displacements),
                              type_array, &newtype);
      delete[] type_array;
      return newtype;
   }
   
   inline Datatype
   Datatype::Create_hindexed(int count, const int array_of_blocklengths[],
                          const Aint array_of_displacements[]) const
   {
      MPI_Datatype newtype;
      MPI_Type_create_hindexed(count, const_cast<int *>(array_of_blocklengths),
                               const_cast<MPI_Aint*>(array_of_displacements),
                               mpiDatatype_, &newtype) ;
      return newtype;
   }
   
   inline Datatype
   Datatype::Create_hvector(int count, int blocklength,
                            Aint stride) const
   {
      MPI_Datatype newtype;
      MPI_Type_create_hvector(count, blocklength, (MPI_Aint)stride,
                              mpiDatatype_, &newtype);
   
      return newtype;
   }
   
   inline Datatype
   Datatype::Create_indexed_block(int count, int blocklength,
                        const int array_of_displacements[]) const
   {
      MPI_Datatype newtype;
      MPI_Type_create_indexed_block(count, blocklength, 
                                    const_cast<int *>(array_of_displacements),
                                    mpiDatatype_, &newtype);
      return newtype;
   }
   
   inline Datatype
   Datatype::Create_resized(const Aint lb, const Aint extent) const
   {
      MPI_Datatype newtype;
      MPI_Type_create_resized(mpiDatatype_, lb, extent, &newtype);
      return(newtype);
   }
   
   inline int
   Datatype::Get_size() const
   {
      int size;
      MPI_Type_size(mpiDatatype_, &size);
      return size;
   }
   
   inline void
   Datatype::Get_extent(Aint& lb, Aint& extent) const
   {
      MPI_Type_get_extent(mpiDatatype_, &lb, &extent);
   }
   
   inline void
   Datatype::Get_true_extent(Aint& lb, Aint& extent) const
   {
      MPI_Type_get_true_extent(mpiDatatype_, &lb, &extent);
   }
   
   inline void
   Datatype::Commit()
   {
      MPI_Type_commit(&mpiDatatype_);
   }
 
   #if 0 
   inline void
   Datatype::Pack(const void* inbuf, int incount,
                  void *outbuf, int outsize,
                  int& position, const Comm &comm) const
   {
      MPI_Pack(const_cast<void *>(inbuf), incount,  mpiDatatype_, outbuf,
               outsize, &position, comm);
   }
   
   inline void
   Datatype::Unpack(const void* inbuf, int insize,
                    void *outbuf, int outcount, int& position,
                    const Comm& comm) const
   {
      MPI_Unpack(const_cast<void *>(inbuf), insize, &position,
                 outbuf, outcount, mpiDatatype_, comm);
   }
   
   inline int
   Datatype::Pack_size(int incount, const Comm& comm) const
   {
      int size;
       MPI_Pack_size(incount, mpiDatatype_, comm, &size);
      return size;
   }
   #endif
   
   inline void
   Datatype::Pack_external(const char* datarep, const void* inbuf, 
                           int incount, void* outbuf, Aint outsize, 
                           Aint& position) const
   {
      MPI_Pack_external(const_cast<char *>(datarep), 
                        const_cast<void *>(inbuf),
                        incount, mpiDatatype_, outbuf, 
                        outsize, &position);
   }
   
   inline Aint
   Datatype::Pack_external_size(const char* datarep, int incount) const
   {
      MPI_Aint addr;
      MPI_Pack_external_size(const_cast<char *>(datarep), incount, 
                             mpiDatatype_, &addr);
      return addr;
   }
   
   inline void
   Datatype::Unpack_external(const char* datarep, const void* inbuf,
                             Aint insize, Aint& position, void* outbuf, 
                             int outcount) const
   {
      MPI_Unpack_external(const_cast<char *>(datarep), 
                          const_cast<void *>(inbuf),
                          insize, &position, outbuf, outcount, mpiDatatype_);
   }
   
   //
   // Miscellany
   //
   
   inline Datatype
   Datatype::Create_subarray(int ndims, const int array_of_sizes[],
                             const int array_of_subsizes[],
                             const int array_of_starts[], int order) const
   {
      MPI_Datatype type;
      MPI_Type_create_subarray(ndims, const_cast<int *>(array_of_sizes),
                               const_cast<int *>(array_of_subsizes),
                               const_cast<int *>(array_of_starts),
                               order, mpiDatatype_, &type);
      return type;
   }
   
   inline Datatype
   Datatype::Create_darray(int size, int rank, int ndims,
                           const int array_of_gsizes[], 
                           const int array_of_distribs[],
                           const int array_of_dargs[],  
                           const int array_of_psizes[],
                           int order) const
   {
      MPI_Datatype type;
      MPI_Type_create_darray(size, rank, ndims,
                             const_cast<int *>(array_of_gsizes),
                             const_cast<int *>(array_of_distribs),
                             const_cast<int *>(array_of_dargs),
                             const_cast<int *>(array_of_psizes),
                             order, mpiDatatype_, &type);
      return type;
   }
   
   inline Datatype
   Datatype::Match_size(int typeclass, int size)
   {
       MPI_Datatype type;
       MPI_Type_match_size(typeclass, size, &type);
       return type;
   }
   
   //
   // External Interfaces
   //
   
   inline Datatype
   Datatype::Dup() const
   {
      MPI_Datatype type;
      MPI_Type_dup(mpiDatatype_, &type);
      return type;
   }
   
