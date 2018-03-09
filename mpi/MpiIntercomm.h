#ifdef UTIL_MPI
#ifndef UTIL_MPI_INTERCOMM_H
#define UTIL_MPI_INTERCOMM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiGroup.h"
#include "MpiComm.h"
#include "MpiIntracomm.h"
#include <mpi.h>

namespace Util {
namespace Mpi {

   class Intercomm : public Comm 
   {

   public:

      // construction
      Intercomm()
       : Comm(MPI_COMM_NULL)
      { }

      // Copy
      Intercomm(const Intercomm& data)
       : Comm(data.mpiComm_)
      { }

      // Copy from Comm
      Intercomm(const Comm& data)
       : Comm(data)
      { }

      // Copy from MPI_Comm
      Intercomm(MPI_Comm data) 
       : Comm(data) 
      { }

      // Assignment
      Intercomm& operator=(const Intercomm& data)
      {  mpiComm_ = data.mpiComm_; return *this; }

      // Assignment from Comm
      Intercomm& operator=(const Comm& data)
      {  mpiComm_ = data; return *this; }

      // Assignment from MPI_Comm
      Intercomm& operator=(const MPI_Comm& data)
      {  mpiComm_ = data; return *this; }

      // Groups, Contexts, and Communicators

      Intercomm Dup() const;

      virtual Intercomm& Clone() const;

      virtual int Get_remote_size() const;

      virtual Group Get_remote_group() const;

      virtual Intracomm Merge(bool high) const;

      virtual Intercomm Create(const Group& group) const;

      virtual Intercomm Split(int color, int key) const;

   };

#include "MpiIntercomm_inln.h"

}
}
#endif
#endif

