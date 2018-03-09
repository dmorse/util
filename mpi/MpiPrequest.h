#ifdef UTIL_MPI
#ifndef UTIL_MPI_PREQUEST_H
#define UTIL_MPI_PREQUEST_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiRequest.h"
#include <util/global.h>

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
