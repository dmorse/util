   #include <string.h>
   
   // Point-to-Point Communication
   
   inline void
   Attach_buffer(void* buffer, int size)
   {  MPI_Buffer_attach(buffer, size); }
   
   inline int
   Detach_buffer(void*& buffer)
   {
      int size;
      MPI_Buffer_detach(&buffer, &size);
      return size;
   }
   
   // Process Topologies
   
   inline 
   void Compute_dims(int nnodes, int ndims, int dims[])
   {  MPI_Dims_create(nnodes, ndims, dims); }
   
   // Environmental Inquiry
   
   inline 
   int Add_error_class()
   {
      int errcls;
      MPI_Add_error_class(&errcls);
      return errcls;
   }
   
   inline 
   int Add_error_code(int errorclass)
   { 
      int errcode;
      MPI_Add_error_code(errorclass, &errcode);
      return errcode;
   }
   
   inline void
   Add_error_string(int errorcode, const char* string)
   {  MPI_Add_error_string(errorcode, const_cast<char *>(string)); }
   
   inline 
   void Get_processor_name(char* name, int& resultlen)
   {  MPI_Get_processor_name(name, &resultlen); }
   
   inline void
   Get_error_string(int errorcode, char* string, int& resultlen)
   {  MPI_Error_string(errorcode, string, &resultlen); }
   
   inline 
   int Get_error_class(int errorcode)
   {
      int errorclass;
      MPI_Error_class(errorcode, &errorclass);
      return errorclass;
   }
   
   inline double
   Wtime()
   {  return (MPI_Wtime()); }
   
   inline double
   Wtick()
   {  return (MPI_Wtick()); }
   
   #if 0
   inline void
   Real_init()
   {  InitializeIntercepts(); }
   #endif
   
   inline 
   void Init(int& argc, char**& argv)
   {
      MPI_Init(&argc, &argv);
      //Real_init();
   }
   
   inline 
   void Init()
   {
      MPI_Init(0, 0);
      //Real_init();
   }
   
   inline 
   void Finalize()
   {  MPI_Finalize(); }
   
   inline 
   bool Is_initialized()
   {
      int t;
      MPI_Initialized(&t);
      return bool(t);
   }
   
   inline 
   bool Is_finalized()
   {
      int t;
      MPI_Finalized(&t);
      return bool(t);
   }
   
   
   //
   // External Interfaces
   //
   
   inline 
   int Init_thread(int required)
   {
      int provided;
      MPI_Init_thread(0, NULL, required, &provided);
      //Real_init();
      return provided;
   }
   
   inline 
   int Init_thread(int& argc, char**& argv, int required)
   {
      int provided;
      MPI_Init_thread(&argc, &argv, required, &provided);
      //Real_init();
      return provided;
   }
   
   inline 
   bool Is_thread_main()
   {
      int flag;
      MPI_Is_thread_main(&flag);
      return (bool)(flag == 1);
   }
   
   
   inline int
   Query_thread()
   {
      int provided;
      MPI_Query_thread(&provided);
      return provided;
   }
   
   // Miscellany
  
   // Process Creation
   
   inline 
   void Close_port(const char* port_name)
   {  MPI_Close_port(const_cast<char *>(port_name)); }
   
   inline void
   Get_version(int& version, int& subversion)
   { MPI_Get_version(&version, &subversion); }
   
   inline Aint
   Get_address(void* location)
   {
      Aint ret;
      MPI_Get_address(location, &ret);
      return ret;
   }
   
   // Profiling
   
   inline 
   void Pcontrol(const int level, ...)
   {
      va_list ap;
      va_start(ap, level);
   
      MPI_Pcontrol(level, ap);
      va_end(ap);
   }
   
