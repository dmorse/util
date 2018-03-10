#ifdef UTIL_MPI
#ifndef UTIL_MPI_INFO_H
#define UTIL_MPI_INFO_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

/*
* The code in this file and related files implements a variant of t
* the MPI 1.2 C++ bindings. Development of this version of the MPI C++ 
* bindings was motivated by the fact that the C++ bindings were 
* officially deprecated in MPI 2.2, and slated for removal in MPI 3.
*
* The code in this and other files in the same directory that implement
* a variant of the MPI C++ bindings was derived from the implementation 
* provided in the Open MPI (ompi) package, starting from corresponding 
* files in the ompi/ompi/mpi/cxx directory of an ompi source code 
* repository that was cloned from the github server in March 2018. A 
* list of copyright holders for the ompi source code is given in the 
* file named ompiCopyright in the same directory as this file. 
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
