   
   inline Info
   Info::Create()
   {
      MPI_Info newinfo;
      MPI_Info_create(&newinfo);
      return newinfo;
   }
   
   inline void
   Info::Delete(const char* key)
   {
       MPI_Info_delete(mpiInfo_, const_cast<char *>(key));
   }
   
   inline Info
   Info::Dup() const
   {
      MPI_Info newinfo;
      MPI_Info_dup(mpiInfo_, &newinfo);
      return newinfo;
   }
   
   inline void
   Info::Free()
   {
      MPI_Info_free(&mpiInfo_);
   }
   
   inline bool
   Info::Get(const char* key, int valuelen, char* value) const
   {
      int flag;
      MPI_Info_get(mpiInfo_, const_cast<char *>(key), valuelen, 
                   value, &flag);
      return bool(flag);
   }
   
   inline int
   Info::Get_nkeys() const
   {
      int nkeys;
      MPI_Info_get_nkeys(mpiInfo_, &nkeys);
      return nkeys;
   }
   
   inline void
   Info::Get_nthkey(int n, char* key) const
   {
      MPI_Info_get_nthkey(mpiInfo_, n, key);
   }
   
   inline bool
   Info::Get_valuelen(const char* key, int& valuelen) const
   {
      int flag;
      MPI_Info_get_valuelen(mpiInfo_, const_cast<char *>(key), 
                            &valuelen, &flag);
      return bool(flag);
   }
   
   inline void
   Info::Set(const char* key, const char* value)
   {
      MPI_Info_set(mpiInfo_, const_cast<char *>(key), 
                   const_cast<char *>(value));
   }
