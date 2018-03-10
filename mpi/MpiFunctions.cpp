/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

/*
* The code in this file implements a variant of the MPI 1.2 C++ 
* bindings. Development of this version of the MPI C++ bindings
* was motivated by the fact that the C++ bindings were officially
* deprecated in MPI 2.2, and slated for removal in MPI 3.
*
* The code in this and other files in the same directory that 
* implement a variant of the MPI C++ bindings was derived from 
* the implementation provided in the Open MPI (ompi) package, 
* starting from corresponding files in the ompi/ompi/mpi/cxx 
* directory of an ompi source code repository that was cloned 
* from the github server in March 2018. A list of copyright 
* holders for the ompi source is given in the file named 
* ompiCopyright in the same directory as this file. 
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
