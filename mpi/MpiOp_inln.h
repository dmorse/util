/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
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
  
