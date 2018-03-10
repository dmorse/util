#ifdef UTIL_MPI
#ifndef UTIL_MPI_ERRHANDLER_H
#define UTIL_MPI_ERRHANDLER_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
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
