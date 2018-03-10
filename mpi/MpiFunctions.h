#ifdef UTIL_MPI
#ifndef UTIL_MPI_FUNCTIONS_H
#define UTIL_MPI_FUNCTIONS_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiAddress.h"
#include <mpi.h>

namespace Util {
namespace Mpi {

   class Info;

   // Point-to-Point Communication

   void Attach_buffer(void* buffer, int size);

   int Detach_buffer(void*& buffer);

   // Process Topologies

   void Compute_dims(int nnodes, int ndims, int dims[]);

   // Environmental Inquiry

   int Add_error_class();

   int Add_error_code(int errorclass);

   void Add_error_string(int errorcode, const char* string);

   void Get_processor_name(char* name, int& resultlen);

   void Get_error_string(int errorcode, char* string, int& resultlen);

   int Get_error_class(int errorcode);

   double Wtime();

   double Wtick();

   void Init(int& argc, char**& argv);

   void Init();

   void InitializeIntercepts();

   void Real_init();

   void Finalize();

   bool Is_initialized();

   bool Is_finalized();

   // External Interfaces

   int Init_thread(int &argc, char**&argv, int required);

   int Init_thread(int required);

   bool Is_thread_main();

   int Query_thread();

   // Miscellany

   void* Alloc_mem(Aint size, const Info& info);

   void Free_mem(void* base);

   void Get_version(int& version, int& subversion);

   Aint Get_address(void* location);

   // Process Creation

   void Close_port(const char* port_name);

   void
   Lookup_name(const char* service_name, const Info& info, char* port_name);

   void
   Open_port(const Info& info, char* port_name);

   void
   Publish_name(const char* service_name, const Info& info,
   	     const char* port_name);

   void
   Unpublish_name(const char* service_name, const Info& info,
   	       const char* port_name);

   // Profiling

   void Pcontrol(const int level, ...);

#include "MpiFunctions_inln.h"

}
}
#endif
#endif
