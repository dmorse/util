#ifdef UTIL_MPI
#ifndef UTIL_MPI_STATUS_H
#define UTIL_MPI_STATUS_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>
#include <complex>

namespace Util {
namespace Mpi {

   class Datatype;

   class Status {
   
      friend class Request;  //and also from request.cc
      //friend class Comm;   //so I can access pmpiStatus_ data member in comm.cc
      //friend class File;
   
   public:
   
      Status()
       : mpiStatus_()
      { }
   
      // copy
      Status(const Status& data)
       : mpiStatus_(data.mpiStatus_)
      { }
   
      Status(const MPI_Status &i)
       : mpiStatus_(i)
      { }
   
      virtual ~Status() {}
   
      Status& operator = (const Status& data)
      {  mpiStatus_ = data.mpiStatus_; return *this; }
   
      // Assignment from MPI_Status
      Status& operator= (const MPI_Status &i)
      {  mpiStatus_ = i; return *this; }
   
      operator MPI_Status () const
      {  return mpiStatus_; }
   
      // Point-to-Point Communication
   
      virtual int Get_count(const Datatype& datatype) const;
   
      virtual bool Is_cancelled() const;
   
      virtual int Get_elements(const Datatype& datatype) const;
   
      // Status Access
   
      virtual int Get_source() const;
   
      virtual void Set_source(int source);
   
      virtual int Get_tag() const;
   
      virtual void Set_tag(int tag);
   
      virtual int Get_error() const;
   
      virtual void Set_error(int error);
   
      virtual void Set_elements(const Datatype& datatype, int count);
   
      virtual void Set_cancelled(bool flag);
   
   protected:
   
      MPI_Status mpiStatus_;
   
   };

   #include "MpiStatus_inln.h"

}
}
#endif
#endif

