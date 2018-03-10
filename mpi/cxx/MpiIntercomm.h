#ifdef UTIL_MPI
#ifndef UTIL_MPI_INTERCOMM_H
#define UTIL_MPI_INTERCOMM_H

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

