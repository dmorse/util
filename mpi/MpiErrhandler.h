#ifdef UTIL_MPI
#ifndef UTIL_MPI_ERRHANDLER_H
#define UTIL_MPI_ERRHANDLER_H

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

#include <mpi.h>

namespace Util {
namespace Mpi {

   
   class Errhandler {
   public:
   
      // Default constructor
      inline Errhandler()
       : mpi_errhandler(MPI_ERRHANDLER_NULL) 
      {}
   
       // Copy constructor.
      inline 
      Errhandler(const Errhandler& e) 
       : mpi_errhandler(e.mpi_errhandler) 
      {}
   
      // Copy from MPI_Errhandler
      inline 
      Errhandler(MPI_Errhandler i)
       : mpi_errhandler(i) 
      {}
   
      // Destructor
      inline 
      virtual ~Errhandler() 
      { }
   
      // Assignment
      inline Errhandler& operator=(const Errhandler& e)
      {
         mpi_errhandler = e.mpi_errhandler;
         return *this;
      }
   
      // Assignment from MPI_Errhandler
      inline 
      Errhandler& operator= (const MPI_Errhandler &i) 
      {  mpi_errhandler = i; return *this; }
   
      // Conversion to MPI_Errhandler
      inline 
      operator MPI_Errhandler() const 
      {  return mpi_errhandler; }
   
      // Equality comparison
      inline 
      bool operator==(const Errhandler &a) 
      {  return (bool)(mpi_errhandler == a.mpi_errhandler); }
   
      // Inequality comparison
      inline 
      bool operator!=(const Errhandler &a) 
      {  return (bool)!(*this == a); }
   
      //  inline operator MPI_Errhandler*() { return &mpi_errhandler; }
   
      // Errhandler access functions
   
      virtual void Free();
   
   private:
   
      MPI_Errhandler mpi_errhandler;
   
   };

   inline 
   void Errhandler::Free()
   {  MPI_Errhandler_free(&mpi_errhandler); }

}
}
#endif
#endif
