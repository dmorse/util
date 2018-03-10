#ifdef  UTIL_MPI
#ifndef UTIL_MPI_COMM_H
#define UTIL_MPI_COMM_H

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

#include "MpiDatatype.h"
#include "MpiStatus.h"
#include "MpiGroup.h"
#include "MpiRequest.h"
#include "MpiPrequest.h"
#include "MpiErrhandler.h"
#include "MpiOp.h"
#include <mpi.h>

namespace Util {
namespace Mpi {

   class Op;
   class Intercomm;

   class Comm
   {

   public:
   
      // Default constructor.
      Comm();
   
      // Copy constructor.
      Comm(const Comm& data);
   
      // Copy construction from an MPI_Comm
      Comm(MPI_Comm data);

      // Destructor
      virtual ~Comm();
   
      // Implicit conversion to MPI_Comm
      operator MPI_Comm() const 
      {  return mpiComm_; }
   
      // Comparison operators
   
      inline bool operator == (const Comm& data) const {
      return (bool) (mpiComm_ == data.mpiComm_); }
   
      inline bool operator != (const Comm& data) const {
      return (bool) !(*this == data);}
   
      // Groups, Contexts, and Communicators
   
      virtual Group Get_group() const;
   
      virtual int Get_size() const;
   
      virtual int Get_rank() const;
   
      static int Compare(const Comm & comm1, const Comm & comm2);
   
      virtual Comm& Clone() const = 0;
   
      virtual void Free(void);
   
      virtual bool Is_inter() const;
   
      // Point-to-Point Send and Receive
   
      virtual void
      Send(const void* buf, int count,
           const Datatype & datatype, int dest, int tag) const;
   
      virtual void
      Recv(void* buf, int count, const Datatype & datatype,
           int source, int tag, Status & status) const;
   
   
      virtual void
      Recv(void* buf, int count, const Datatype & datatype,
           int source, int tag) const;
   
      virtual void
      Bsend(const void* buf, int count, const Datatype & datatype,
            int dest, int tag) const;
   
      virtual void
      Ssend(const void* buf, int count,
            const Datatype & datatype, int dest, int tag) const ;
   
      virtual void
      Rsend(const void* buf, int count, const Datatype & datatype,
            int dest, int tag) const;
   
      virtual Request
      Isend(const void* buf, int count, const Datatype & datatype,
           int dest, int tag) const;
   
      virtual Request
      Ibsend(const void* buf, int count, const Datatype & datatype,
             int dest, int tag) const;
   
      virtual Request
      Issend(const void* buf, int count,
            const Datatype & datatype, int dest, int tag) const;
   
      virtual Request
      Irsend(const void* buf, int count, const Datatype & datatype,
             int dest, int tag) const;
   
      virtual Request
      Irecv(void* buf, int count, const Datatype & datatype,
            int source, int tag) const;
  
      // Probe functions
   
      virtual bool
      Iprobe(int source, int tag, Status & status) const;
   
      virtual bool Iprobe(int source, int tag) const;
   
      virtual void Probe(int source, int tag, Status & status) const;
   
      virtual void Probe(int source, int tag) const;
  
      // Point-to-Point send and recv init functions
   
      virtual Prequest
      Send_init(const void* buf, int count,
                const Datatype & datatype, int dest, int tag) const;
   
      virtual Prequest
      Bsend_init(const void* buf, int count,
                 const Datatype & datatype, int dest,
                 int tag) const;
   
      virtual Prequest
      Ssend_init(const void* buf, int count, const Datatype & datatype,
                 int dest, int tag) const;
   
      virtual Prequest
      Rsend_init(const void* buf, int count, const Datatype & datatype,
                 int dest, int tag) const;
   
      virtual Prequest
      Recv_init(void* buf, int count, const Datatype & datatype,
                int source, int tag) const;
   
      // Point-to-Point Sendrecv functions 
   
      virtual void
      Sendrecv(const void* sendbuf, int sendcount,
               const Datatype & sendtype, int dest, int sendtag,
               void* recvbuf, int recvcount,
               const Datatype & recvtype, int source,
               int recvtag, Status & status) const;
   
      virtual void
      Sendrecv(const void* sendbuf, int sendcount,
               const Datatype & sendtype, int dest, int sendtag,
               void* recvbuf, int recvcount,
               const Datatype & recvtype, int source,
               int recvtag) const;
   
      virtual void
      Sendrecv_replace(void* buf, int count,
                       const Datatype & datatype, int dest,
                       int sendtag, int source,
                       int recvtag, Status & status) const;
   
      virtual void
      Sendrecv_replace(void* buf, int count,
                       const Datatype & datatype, int dest,
                       int sendtag, int source,
                       int recvtag) const;
   
      // Collective Communication: Broadcast, Scatter and Gather
   
      virtual void
      Barrier() const;
   
      virtual void
      Bcast(void* buffer, int count,
        const Datatype& datatype, int root) const;
   
      virtual void
      Gather(const void* sendbuf, int sendcount,
         const Datatype & sendtype,
         void* recvbuf, int recvcount,
         const Datatype & recvtype, int root) const;
   
      virtual void
      Gatherv(const void* sendbuf, int sendcount,
          const Datatype & sendtype, void* recvbuf,
          const int recvcounts[], const int displs[],
          const Datatype & recvtype, int root) const;
   
      virtual void
      Scatter(const void* sendbuf, int sendcount,
          const Datatype & sendtype,
          void* recvbuf, int recvcount,
          const Datatype & recvtype, int root) const;
   
      virtual void
      Scatterv(const void* sendbuf, const int sendcounts[],
           const int displs[], const Datatype & sendtype,
           void* recvbuf, int recvcount,
           const Datatype & recvtype, int root) const;
   
      virtual void
      Allgather(const void* sendbuf, int sendcount,
            const Datatype & sendtype, void* recvbuf,
            int recvcount, const Datatype & recvtype) const;
   
      virtual void
      Allgatherv(const void* sendbuf, int sendcount,
             const Datatype & sendtype, void* recvbuf,
             const int recvcounts[], const int displs[],
             const Datatype & recvtype) const;
   
      virtual void
      Alltoall(const void* sendbuf, int sendcount,
           const Datatype & sendtype, void* recvbuf,
           int recvcount, const Datatype & recvtype) const;
   
      virtual void
      Alltoallv(const void* sendbuf, const int sendcounts[],
            const int sdispls[], const Datatype & sendtype,
            void* recvbuf, const int recvcounts[],
            const int rdispls[], const Datatype & recvtype) const;
   
      virtual void
      Alltoallw(const void* sendbuf, const int sendcounts[],
                const int sdispls[], const Datatype sendtypes[],
                void* recvbuf, const int recvcounts[],
                const int rdispls[], const Datatype recvtypes[]) const;

      // Collective Computation: Reduce Operation
   
      virtual void
      Reduce(const void* sendbuf, void *recvbuf, int count,
         const Datatype & datatype, const Op & op,
         int root) const;
   
   
      virtual void
      Allreduce(const void* sendbuf, void *recvbuf, int count,
            const Datatype & datatype, const Op & op) const;
   
      virtual void
      Reduce_scatter(const void* sendbuf, void *recvbuf,
             int recvcounts[],
             const Datatype & datatype,
             const Op & op) const;
   
      //
      // Process Creation
      //
   
      virtual void Disconnect();
  
      static Intercomm Get_parent();
   
      static Intercomm Join(const int fd);
   
      //
      // External Interfaces
      //
   
      virtual void Get_name(char * comm_name, int& resultlen) const;
   
      virtual void Set_name(const char* comm_name);
   
      //
      // Process Topologies
      //
   
      virtual int Get_topology() const;
   
      //
      // Errhandler
      //
   
      //static Errhandler Create_errhandler(Comm::Errhandler_function* function);
   
      virtual void Set_errhandler(const Errhandler& errhandler);
   
      virtual Errhandler Get_errhandler() const;
   
      void Call_errhandler(int errorcode) const;
   
      //
      // Environmental Inquiry
      //
   
      virtual void Abort(int errorcode);
   
   protected:
   
      MPI_Comm mpiComm_;
   
   };

   #include "MpiComm_inln.h"
}
}
#endif
#endif
