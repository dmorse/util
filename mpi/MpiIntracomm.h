#ifdef UTIL_MPI
#ifndef UTIL_MPI_INTRACOMM_H
#define UTIL_MPI_INTRACOMM_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiComm.h"
#include <mpi.h>

namespace Util {
namespace Mpi {

   class Group;
   class Info;
   class Cartcomm;
   class Graphcomm;

   class Intracomm : public Comm {
   public:

      // Default constructor.
      Intracomm();

      // Copy constructor;
      Intracomm(const Intracomm& data);

      // Copy from Comm
      Intracomm(const Comm& data);

      // Copy from MPI_Comm
      Intracomm(MPI_Comm data);

      // assignment
      Intracomm& operator=(const Intracomm& data)
      {  mpiComm_ = data.mpiComm_; return *this; }

      Intracomm& operator=(const Comm& data)
      {  mpiComm_ = data; return *this; }

      // Assign from MPI_Comm
      Intracomm& operator=(const MPI_Comm& data) {
        mpiComm_ = data; return *this; }

      // Collective Communication

      virtual void
      Scan(const void *sendbuf, void *recvbuf, int count,
           const Datatype & datatype, const Op & op) const;

      virtual void
      Exscan(const void *sendbuf, void *recvbuf, int count,
   	 const Datatype & datatype, const Op & op) const;

      //
      // Communicator maintenance
      //

      Intracomm Dup() const;

      virtual Intracomm& Clone() const;

      virtual Intracomm
      Create(const Group& group) const;

      virtual Intracomm
      Split(int color, int key) const;

      virtual Intercomm
      Create_intercomm(int local_leader, const Comm& peer_comm,
   		   int remote_leader, int tag) const;

      virtual Cartcomm
      Create_cart(int ndims, const int dims[],
   	      const bool periods[], bool reorder) const;

      virtual Graphcomm
      Create_graph(int nnodes, const int index[],
   	       const int edges[], bool reorder) const;


      // Process Creation and Management

      virtual 
      Intercomm Accept(const char* port_name, const Info& info, int root) 
      const;

      virtual 
      Intercomm Connect(const char* port_name, const Info& info, int root)
      const;

      virtual 
      Intercomm Spawn(const char* command, const char* argv[],
                      int maxprocs, const Info& info, int root) const;

      virtual 
      Intercomm Spawn(const char* command, const char* argv[],
                      int maxprocs, const Info& info,
                      int root, int array_of_errcodes[]) const;

      virtual 
      Intercomm Spawn_multiple(int count, const char* array_of_commands[],
                               const char** array_of_argv[],
                               const int array_of_maxprocs[],
                               const Info array_of_info[], int root);

      virtual 
      Intercomm Spawn_multiple(int count, const char* array_of_commands[],
                               const char** array_of_argv[],
                               const int array_of_maxprocs[],
                               const Info array_of_info[], int root,
                               int array_of_errcodes[]);


   private:
   
      MPI_Info *
      convert_info_to_mpi_info(int p_nbr, const Info p_info_tbl[]);

   };

#include "MpiIntracomm_inln.h"

}
}
#endif
#endif
