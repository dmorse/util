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

#include "MpiIntraComm.h"
#include "MpiInterComm.h"
#include "MpiCartComm.h"
#include "MpiGraphComm.h"
#include "MpiInfo.h"

namespace Util {
namespace Mpi {

   // Default constructor.
   Intracomm::Intracomm()
    : Comm()
   {}

   // Copy constructor
   Intracomm::Intracomm(const Intracomm& data)
    : Comm(data.mpiComm_)
   {}

   // Copy from Comm
   Intracomm::Intracomm(const Comm& data)
    : Comm(data)
   {}

   // Create and intercommunicator
   Intercomm
   Intracomm::Create_intercomm(int local_leader,
                               const Comm& peer_comm,
                               int remote_leader, int tag) const
   {
      MPI_Comm newintercomm;
      MPI_Intercomm_create(mpiComm_, local_leader, peer_comm,
                           remote_leader, tag, &newintercomm);
      return newintercomm;
   }

   // Create a Cartesian communicator
   Cartcomm  
   Intracomm::Create_cart(int ndims, const int dims[],
                          const bool periods[], bool reorder) 
   const
   {
      int *int_periods = new int [ndims];
      for (int i=0; i<ndims; i++) {
         int_periods[i] = (int) periods[i];
      }

      MPI_Comm newcomm;
      MPI_Cart_create(mpiComm_, ndims, const_cast<int *>(dims),
                      int_periods, (int)reorder, &newcomm);
      delete [] int_periods;
      return newcomm;
   }

   // Create a Graph communicator
   Graphcomm
   Intracomm::Create_graph(int nnodes, const int index[],
                       const int edges[], bool reorder) const
   {
      MPI_Comm newcomm;
      MPI_Graph_create(mpiComm_, nnodes, const_cast<int *>(index),
                       const_cast<int *>(edges), (int)reorder, &newcomm);
      return newcomm;
   }

   // Process Creation and Management

   Intercomm
   Intracomm::Accept(const char* port_name, const Info& info, int root) 
   const
   {
      MPI_Comm newcomm;
      MPI_Comm_accept(const_cast<char *>(port_name), info, root, mpiComm_,
                      &newcomm);
      return newcomm;
   }


   Intercomm
   Intracomm::Connect(const char* port_name, const Info& info, int root) 
   const
   {
      MPI_Comm newcomm;
      MPI_Comm_connect(const_cast<char *>(port_name), info, root, 
                       mpiComm_, &newcomm);
      return newcomm;
   }


   Intercomm
   Intracomm::Spawn(const char* command, const char* argv[],
                    int maxprocs, const Info& info,
                    int root) const
   {
      MPI_Comm newcomm;
      MPI_Comm_spawn(const_cast<char *>(command), 
                     const_cast<char **>(argv), maxprocs,
                     info, root, mpiComm_, &newcomm,
                     (int *)MPI_ERRCODES_IGNORE);
      return newcomm;
   }


   Intercomm
   Intracomm::Spawn(const char* command, const char* argv[],
                    int maxprocs, const Info& info,
                    int root, int array_of_errcodes[]) const
   {
      MPI_Comm newcomm;
      MPI_Comm_spawn(const_cast<char *>(command), 
                     const_cast<char **>(argv), maxprocs,
                     info, root, mpiComm_, &newcomm,
                     array_of_errcodes);
      return newcomm;
   }

   Intercomm
   Intracomm::Spawn_multiple(int count,
                             const char* array_of_commands[],
                             const char** array_of_argv[],
                             const int array_of_maxprocs[],
                             const Info array_of_info[], int root)
   {
      MPI_Comm newcomm;
      MPI_Info *const array_of_mpi_info =
          convert_info_to_mpi_info(count, array_of_info);

      MPI_Comm_spawn_multiple(count, 
                              const_cast<char **>(array_of_commands),
                              const_cast<char ***>(array_of_argv),
                              const_cast<int *>(array_of_maxprocs),
                              array_of_mpi_info, root,
                              mpiComm_, &newcomm, 
                              (int *)MPI_ERRCODES_IGNORE);
      delete[] array_of_mpi_info;
      return newcomm;
   }

   MPI_Info *
   Intracomm::convert_info_to_mpi_info(int p_nbr, const Info p_info_tbl[])
   {
      MPI_Info *const mpi_info_tbl = new MPI_Info [p_nbr];
      for (int i_tbl=0; i_tbl < p_nbr; i_tbl++) {
         mpi_info_tbl[i_tbl] = p_info_tbl[i_tbl];
      }
      return mpi_info_tbl;
   }

   Intercomm
   Intracomm::Spawn_multiple(int count,
                             const char* array_of_commands[],
                             const char** array_of_argv[],
                             const int array_of_maxprocs[],
                             const Info array_of_info[], int root,
                             int array_of_errcodes[])
   {
      MPI_Comm newcomm;
      MPI_Info *const array_of_mpi_info =
         convert_info_to_mpi_info(count, array_of_info);

      MPI_Comm_spawn_multiple(count, 
                              const_cast<char **>(array_of_commands),
                              const_cast<char ***>(array_of_argv),
                              const_cast<int *>(array_of_maxprocs),
                              array_of_mpi_info, root,
                              mpiComm_, &newcomm, array_of_errcodes);
      delete[] array_of_mpi_info;
      return newcomm;
   }

}
}
