/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiFunctions.h"
#include "MpiAddress.h"
#include "MpiInfo.h"

namespace Util {
namespace Mpi {

   
   void* Alloc_mem(Aint size, const Info& info)
   {
      void* baseptr;
      MPI_Alloc_mem(size, info, &baseptr);
      return baseptr;
   }
   
   
   void Free_mem(void* base)
   {  MPI_Free_mem(base); }
   
   void Lookup_name(const char * service_name,
                    const Info& info,
                    char* port_name)
   { 
      MPI_Lookup_name(const_cast<char *>(service_name), info, port_name);
   }
   
   
   void Open_port(const Info& info, char* port_name)
   {  MPI_Open_port(info, port_name); }
   
   
   void Publish_name(const char* service_name,
                     const Info& info,
                     const char* port_name)
   {
      MPI_Publish_name(const_cast<char *>(service_name), info,
                       const_cast<char *>(port_name));
   }
   
   
   void Unpublish_name(const char* service_name,
                       const Info& info,
                       const char* port_name)
   {
      MPI_Unpublish_name(const_cast<char *>(service_name), info,
                         const_cast<char *>(port_name));
   }
   
}
}
