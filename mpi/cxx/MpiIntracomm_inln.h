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

   // Default constructor.
   inline
   Intracomm::Intracomm()
    : Comm()
   {}

   // Copy constructor
   inline
   Intracomm::Intracomm(const Intracomm& data)
    : Comm(data.mpiComm_)
   {}

   // Copy from Comm
   inline
   Intracomm::Intracomm(const Comm& data)
    : Comm(data)
   {}

   // Copy from MPI_Comm
   inline
   Intracomm::Intracomm(MPI_Comm data) 
   {
      int initFlag = 0;
      MPI_Initialized(&initFlag);
      if (initFlag && (data != MPI_COMM_NULL)) {
         int interFlag;
         MPI_Comm_test_inter(data, &interFlag);
         if (interFlag) {
            mpiComm_ = MPI_COMM_NULL;
         } else {
            mpiComm_ = data;
         }
      } else {
         mpiComm_ = data;
      }
   }

   // Assignment
   inline
   Intracomm& Intracomm::operator = (const Intracomm& data)
   {  
      mpiComm_ = data.mpiComm_; 
      return *this; 
   }

   // Assign from Comm
   inline
   Intracomm& Intracomm::operator = (const Comm& data)
   {  
      mpiComm_ = data; 
      return *this; 
   }

   // Assign from MPI_Comm
   inline
   Intracomm& Intracomm::operator = (const MPI_Comm& data) 
   { 
      mpiComm_ = data; 
      return *this; 
   }

   inline void
   Intracomm::Scan(const void *sendbuf, void *recvbuf, int count,
                   const Datatype & datatype, const Op& op) const
   {
      MPI_Scan(const_cast<void *>(sendbuf), recvbuf, 
               count, datatype, op, mpiComm_);
   }

   inline void
   Intracomm::Exscan(const void *sendbuf, void *recvbuf, int count,
                     const Datatype & datatype,
                     const Op& op) const
   {
      MPI_Exscan(const_cast<void *>(sendbuf), recvbuf, 
                 count, datatype, op, mpiComm_);
   }

   inline Intracomm
   Intracomm::Dup() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      return newcomm;
   }

   inline Intracomm&
   Intracomm::Clone() const
   {
      MPI_Comm newcomm;
      MPI_Comm_dup(mpiComm_, &newcomm);
      Intracomm* dup = new Intracomm(newcomm);
      return *dup;
   }

   inline Intracomm
   Intracomm::Create(const Group& group) const
   {
      MPI_Comm newcomm;
      MPI_Comm_create(mpiComm_, group, &newcomm);
      return newcomm;
   }

   inline Intracomm
   Intracomm::Split(int color, int key) const
   {
      MPI_Comm newcomm;
      MPI_Comm_split(mpiComm_, color, key, &newcomm);
      return newcomm;
   }


