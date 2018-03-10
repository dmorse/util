#ifdef UTIL_MPI
#ifndef UTIL_MPI_INFO_H
#define UTIL_MPI_INFO_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <mpi.h>

namespace Util {
namespace Mpi {


   class Info
   {

      friend class MPI::Comm;
      friend class MPI::Request;

   public:

      // Default constructor.
      Info() 
       : mpiInfo_(MPI_INFO_NULL) 
      { }

      // Copy constructor.
      Info(const Info& data) 
       : mpiInfo_(data.mpiInfo_) 
      {}

      // Copy from MPI_Info
      Info(MPI_Info i) 
       : mpiInfo_(i) 
      {}

      // Destructor
      virtual ~Info() {}

      Info& operator = (const Info& data) 
      {  
         mpiInfo_ = data.mpiInfo_; 
         return *this; 
      }

      // Assign from MPI_Info
      Info& operator= (const MPI_Info &i) 
      {  
         mpiInfo_ = i; 
         return *this; 
      }

      operator MPI_Info () const 
      {  return mpiInfo_; }

      //  operator MPI_Info* () const { return (MPI_Info*)&mpiInfo_; }

      static Info Create();

      void Delete(const char* key);

      Info Dup() const;

      void Free();

      bool Get(const char* key, int valuelen, char* value) const;

      int Get_nkeys() const;

      void Get_nthkey(int n, char* key) const;

      bool Get_valuelen(const char* key, int& valuelen) const;

      void Set(const char* key, const char* value);

   protected:

      MPI_Info mpiInfo_;

   };
   
   #include "MpiInfo_inln.h"

}
}
#endif
#endif
