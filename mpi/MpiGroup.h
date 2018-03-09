#ifdef UTIL_MPI
#ifndef UTIL_MPI_GROUP_H
#define UTIL_MPI_GROUP_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>

namespace Util {
namespace Mpi {

   class Group {

   public:

      // Default constructor
      inline 
      Group() 
       : mpiGroup_(MPI_GROUP_NULL) 
      { }

      // Constructor from MPI_Group
      inline 
      Group(MPI_Group i) 
       : mpiGroup_(i) 
      { }

      // Copy constructor
      inline 
      Group(const Group& g) 
       : mpiGroup_(g.mpiGroup_) 
      { }

      // Destructor
      inline 
      virtual ~Group() 
      {}

      // Assignment
      inline 
      Group& operator = (const Group& g) 
      { mpiGroup_ = g.mpiGroup_; return *this; }

      // Assignment from MPI_Group
      inline 
      Group& operator = (const MPI_Group &i) 
      { mpiGroup_ = i; return *this; }

      // Conversion to MPI_Group
      inline 
      operator MPI_Group () const 
      { return mpiGroup_; }

      //  inline operator MPI_Group* () const { return (MPI_Group*)&mpiGroup_; }

      // Return value
      inline MPI_Group mpi() const 
      { return mpiGroup_; }

      // Equality Comparison
      inline 
      bool operator== (const Group &a) 
      { return (bool)(mpiGroup_ == a.mpiGroup_); }

      // Inequality Comparison
      inline 
      bool operator!= (const Group &a) 
      { return (bool)!(*this == a); }

      // Groups, Contexts, and Communicators

      virtual int Get_size() const;

      virtual int Get_rank() const;

      static void Translate_ranks (const Group& group1, int n, const int ranks1[],
   			       const Group& group2, int ranks2[]);

      static int Compare(const Group& group1, const Group& group2);

      static Group Union(const Group &group1, const Group &group2);

      static Group Intersect(const Group &group1, const Group &group2);

      static Group Difference(const Group &group1, const Group &group2);

      virtual Group Incl(int n, const int ranks[]) const;

      virtual Group Excl(int n, const int ranks[]) const;

      virtual Group Range_incl(int n, const int ranges[][3]) const;

      virtual Group Range_excl(int n, const int ranges[][3]) const;

      virtual void Free();

   protected:

      MPI_Group mpiGroup_;

   };

   #include "MpiGroup_inln.h"
}
}
#endif
#endif

