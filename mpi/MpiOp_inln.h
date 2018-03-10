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

   /* 
   * Default constructor
   */
   inline
   Op::Op() 
    : mpiOp_(MPI_OP_NULL) 
   { }
   
   /*
   * Copy constructor.
   */ 
   inline
   Op::Op(const Op& op)
     : mpiOp_(op.mpiOp_) 
   { }
  
   /*
   * Copy from MPI_Op
   */ 
   inline
   Op::Op(MPI_Op i) 
    : mpiOp_(i) 
   {}
   
   /*
   * Destructor.
   */ 
   inline
   Op::~Op()
   {}
   
   /* 
   * Assignment
   */
   inline 
   Op& Op::operator = (const Op& op) 
   {
       mpiOp_ = op.mpiOp_;
       return *this;
   }
  
   /* 
   * Assign from MPI_Op
   */
   inline Op&
   Op::operator= (const MPI_Op &i) 
   { mpiOp_ = i; return *this; }
  
   /*
   * Conversion to MPI_Op
   */ 
   inline
   Op::operator MPI_Op () const 
   { return mpiOp_; }
   
   /* 
   * Equality comparison
   */
   inline bool
   Op::operator == (const Op &a) 
   { return (bool)(mpiOp_ == a.mpiOp_); }
  
   /*
   * Inequality comparison.
   */ 
   inline bool
   Op::operator != (const Op &a) 
   { return (bool)!(*this == a); }
  
