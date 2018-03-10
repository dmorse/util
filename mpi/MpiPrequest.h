#ifdef UTIL_MPI
#ifndef UTIL_MPI_PREQUEST_H
#define UTIL_MPI_PREQUEST_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

/*
* The code in this file and related files implements a variant of the
* MPI 1.2 C++ bindings. Development of this version of the MPI C++ 
* bindings was motivated by the fact that the C++ bindings were 
* deprecated in MPI 2.2 and slated for removal in MPI 3.
*
* The code in this and other files in the same directory that implement
* a variant of the MPI C++ bindings was derived from the implementation 
* provided in the Open MPI (ompi) package, starting from corresponding 
* files in the ompi/ompi/mpi/cxx directory of an ompi source code 
* repository that was cloned from the github server in March 2018. A 
* list of copyright holders for the ompi source code is given in the 
* file named ompiCopyright in the same directory as this file. 
*/

#include "MpiRequest.h"
#include <mpi.h>

namespace Util {
namespace Mpi {

   class Prequest : public Request
   {

   public:

      Prequest() 
      {}

      Prequest(const Request& p) 
       : Request(p) 
      {}

      Prequest(const MPI_Request &i) 
       : Request(i) 
      {}

      virtual ~Prequest() 
      {}

      Prequest& operator=(const Request& r) 
      {  
         mpiRequest_ = r; 
         return *this; 
      }

      Prequest& operator=(const Prequest& r) 
      {  
         mpiRequest_ = r.mpiRequest_; 
         return *this; 
      }

      virtual void Start();

      static void Startall(int count, Prequest array_of_requests[]);

   };

   // Inline function

   inline void Prequest::Start()
   {  MPI_Start(&mpiRequest_); }

}
}
#endif
#endif
