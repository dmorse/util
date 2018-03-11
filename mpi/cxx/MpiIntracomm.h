#ifdef UTIL_MPI
#ifndef UTIL_MPI_INTRACOMM_H
#define UTIL_MPI_INTRACOMM_H

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

      // Assignment
      Intracomm& operator = (const Intracomm& data);

      // Assign from Comm (base class)
      Intracomm& operator = (const Comm& data);

      // Assign from MPI_Comm
      Intracomm& operator = (const MPI_Comm& data);

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
