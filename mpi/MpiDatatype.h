#ifdef UTIL_MPI
#ifndef UTIL_MPI_DATATYPE_H
#define UTIL_MPI_DATATYPE_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>

namespace Util {
namespace Mpi {
 
   class Datatype
   {
   
   public:
   
      // Default constructor 
      inline 
      Datatype() 
        : mpiDatatype_(MPI_DATATYPE_NULL) 
      { }
   
      // Construction from MPI_Datatype
      inline 
      Datatype(MPI_Datatype i) 
       : mpiDatatype_(i) 
      { }
   
      // Copy construction
      inline 
      Datatype(const Datatype& dt) 
       : mpiDatatype_(dt.mpiDatatype_) 
      { }
   
      // Destructor
      inline virtual ~Datatype() 
      {}
   
      // Assignment
      inline 
      Datatype& operator=(const Datatype& dt)
      {  mpiDatatype_ = dt.mpiDatatype_; return *this; }
   
      // Assignment from MPI_Datatype
      inline 
      Datatype& operator= (const MPI_Datatype &i)
      {  mpiDatatype_ = i; return *this; }
   
      // Cast to MPI_Datatype
      inline 
      operator MPI_Datatype () const 
      { return mpiDatatype_; }
   
      // Equality Comparison
      inline 
      bool operator== (const Datatype &other) const
      { return (bool) (mpiDatatype_ == other.mpiDatatype_); }
   
      // Inequality Comparison
      inline 
      bool operator!= (const Datatype &other) const
      { return (bool) !(*this == other); }

      #if 0   
      //
      // Point-to-Point Communication
      //
   
      virtual 
      Datatype Create_contiguous(int count) const;
   
      virtual 
      Datatype Create_vector(int count, int blocklength,
                             int stride) const;
   
      virtual 
      Datatype Create_indexed(int count,
                              const int array_of_blocklengths[],
                              const int array_of_displacements[]) const;
   
      static 
      Datatype Create_struct(int count, const int array_of_blocklengths[],
                             const Aint array_of_displacements[],
                             const Datatype array_if_types[]);
   
      virtual 
      Datatype Create_hindexed(
                      int count, const int array_of_blocklengths[],
                      const Aint array_of_displacements[]) 
      const;
   
      virtual 
      Datatype Create_hvector(int count, int blocklength, Aint stride)     
      const;
   
      virtual 
      Datatype Create_indexed_block(int count, int blocklength,
                                    const int array_of_blocklengths[]) 
      const;
   
      virtual 
      Datatype Create_resized(const Aint lb, const Aint extent) const;
   
      virtual 
      int Get_size() const;
   
      virtual 
      void Get_extent(Aint& lb, Aint& extent) const;
   
      virtual 
      void Get_true_extent(Aint&, Aint&) const;
      #endif
   
      virtual void Commit();
   
      virtual void Free();
 
      #if 0 
      // Packing and Unpacking 
 
      virtual 
      void Pack(const void* inbuf, int incount, void *outbuf,
                int outsize, int& position, const Comm &comm) const;
   
      virtual 
      void Unpack(const void* inbuf, int insize, void *outbuf, int outcount,
                  int& position, const Comm& comm) const;
   
      virtual 
      int Pack_size(int incount, const Comm& comm) const;
   
      virtual 
      void Pack_external(const char* datarep, const void* inbuf, int incount,
                         void* outbuf, Aint outsize, Aint& position) const;
   
      virtual 
      Aint Pack_external_size(const char* datarep, int incount) const;
   
      virtual 
      void Unpack_external(const char* datarep, const void* inbuf,
                           Aint insize, Aint& position, void* outbuf, 
                           int outcount) const;
   
      // Miscellany
   
      virtual 
      Datatype Create_subarray(int ndims, const int array_of_sizes[],
                               const int array_of_subsizes[],
                               const int array_of_starts[], int order) 
      const;
   
      virtual 
      Datatype Create_darray(int size, int rank, int ndims,
                             const int array_of_gsizes[], 
                             const int array_of_distribs[],
                             const int array_of_dargs[],  
                             const int array_of_psizes[],
                             int order) const;
   
      //
      // External Interfaces
      //
   
      virtual Datatype Dup() const;
      #endif
   
   protected:
   
      MPI_Datatype mpiDatatype_;
   
   };


#include "MpiDatatype_inln.h"

}
}
#endif
#endif
