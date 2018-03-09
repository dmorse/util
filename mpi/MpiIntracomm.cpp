/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiIntraComm.h"
#include "MpiInterComm.h"

namespace Util {
namespace Mpi {

   // Default constructor.
   Intracomm::Intracomm()
    : Comm()
   {}

   // Copy
   Intracomm::Intracomm(const Comm& data)
    : Comm(data)
   {}

   // Copy constructor
   Intracomm::Intracomm(const Intracomm& data)
    : Comm(data.mpiComm_)
   {}

   Intercomm
   Intracomm::Create_intercomm(int local_leader,
                       const Comm& peer_comm,
                       int remote_leader, int tag) const
   {
     MPI_Comm newintercomm;
     (void)MPI_Intercomm_create(mpiComm_, local_leader, peer_comm,
                    remote_leader, tag, &newintercomm);
     return newintercomm;
   }

   #if 0
   Cartcomm
   Intracomm::Create_cart(int ndims, const int dims[],
                      const bool periods[], bool reorder) const
   {
     int *int_periods = new int [ndims];
     for (int i=0; i<ndims; i++)
       int_periods[i] = (int) periods[i];

     MPI_Comm newcomm;
     (void)MPI_Cart_create(mpiComm_, ndims, const_cast<int *>(dims),
                 int_periods, (int)reorder, &newcomm);
     delete [] int_periods;
     return newcomm;
   }

   Graphcomm
   Intracomm::Create_graph(int nnodes, const int index[],
                       const int edges[], bool reorder) const
   {
     MPI_Comm newcomm;
     (void)MPI_Graph_create(mpiComm_, nnodes, const_cast<int *>(index),
                            const_cast<int *>(edges), (int)reorder, &newcomm);
     return newcomm;
   }
   #endif

   //
   // Process Creation and Management
   //

   #if 0
   Intercomm
   Intracomm::Accept(const char* port_name,
                     const Info& info,
                     int root) const
   {
     MPI_Comm newcomm;
     (void) MPI_Comm_accept(const_cast<char *>(port_name), info, root, mpiComm_,
                &newcomm);
     return newcomm;
   }


   Intercomm
   Intracomm::Connect(const char* port_name,
                      const Info& info,
                      int root) const
   {
     MPI_Comm newcomm;
     (void) MPI_Comm_connect(const_cast<char *>(port_name), info, root, mpiComm_,
                 &newcomm);
     return newcomm;
   }


   Intercomm
   Intracomm::Spawn(const char* command, const char* argv[],
                    int maxprocs, const Info& info,
                    int root) const
   {
     MPI_Comm newcomm;
     (void) MPI_Comm_spawn(const_cast<char *>(command), const_cast<char **>(argv), maxprocs,
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
     (void) MPI_Comm_spawn(const_cast<char *>(command), const_cast<char **>(argv), maxprocs,
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

     MPI_Comm_spawn_multiple(count, const_cast<char **>(array_of_commands),
                 const_cast<char ***>(array_of_argv),
                             const_cast<int *>(array_of_maxprocs),
                 array_of_mpi_info, root,
                 mpiComm_, &newcomm, (int *)MPI_ERRCODES_IGNORE);
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

     MPI_Comm_spawn_multiple(count, const_cast<char **>(array_of_commands),
                             const_cast<char ***>(array_of_argv),
                             const_cast<int *>(array_of_maxprocs),
                             array_of_mpi_info, root,
                             mpiComm_, &newcomm, array_of_errcodes);
     delete[] array_of_mpi_info;
     return newcomm;
   }
   #endif

}
}
