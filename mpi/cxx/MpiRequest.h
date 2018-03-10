#ifdef UTIL_MPI
#ifndef UTIL_MPI_REQUEST_H
#define UTIL_MPI_REQUEST_H

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

#include "MpiStatus.h"
#include <mpi.h>

namespace Util {
namespace Mpi {

   class Status;
   class Datatype;

   class Request
   {

   public:

      // Default constructor.
      Request()
       : mpiRequest_(MPI_REQUEST_NULL)
      { }

      // Copy constructor.
      Request(const Request& r)
       : mpiRequest_(r.mpiRequest_)
      { }

      // Copy from MPI_Request
      Request(MPI_Request i)
       : mpiRequest_(i)
      { }

      // Destructor.
      virtual ~Request()
      {}

      // Assignment.
      Request& operator=(const Request& r) {
        mpiRequest_ = r.mpiRequest_; return *this; }

      // Assignment from MPI_Request
      Request& operator= (const MPI_Request &i)
      {  mpiRequest_ = i; return *this; }

      // Conversion to MPI_Request.
      operator MPI_Request () const
      { return mpiRequest_; }

      // Equality comparison.
      bool operator== (const Request &a)
      { return (bool)(mpiRequest_ == a.mpiRequest_); }

      // Inequality comparison.
      bool operator!= (const Request &a)
      { return (bool)!(*this == a); }

      //  operator MPI_Request* () const { return (MPI_Request*)&mpiRequest_; }

      // Point-to-Point Communication

      virtual void Wait(Status &status);

      virtual void Wait();

      virtual bool Test(Status &status);

      virtual bool Test();

      virtual void Free(void);

      static int Waitany(int count, Request array[], Status& status);

      static int Waitany(int count, Request array[]);

      static bool Testany(int count, Request array[], int& index, Status& status);

      static bool Testany(int count, Request array[], int& index);

      static void Waitall(int count, Request req_array[], Status stat_array[]);

      static void Waitall(int count, Request req_array[]);

      static bool Testall(int count, Request req_array[], Status stat_array[]);

      static bool Testall(int count, Request req_array[]);

      static int Waitsome(int incount, Request req_array[],
   			     int array_of_indices[], Status stat_array[]) ;

      static int Waitsome(int incount, Request req_array[],
   			     int array_of_indices[]);

      static int Testsome(int incount, Request req_array[],
   			     int array_of_indices[], Status stat_array[]);

      static int Testsome(int incount, Request req_array[],
   			     int array_of_indices[]);

      virtual void Cancel(void) const;

      virtual bool Get_status(Status& status) const;

      virtual bool Get_status() const;

   protected:

      MPI_Request mpiRequest_;

   };

   #include "MpiRequest_inln.h"
}
}
#endif
#endif

