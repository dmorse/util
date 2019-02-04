#ifdef  UTIL_MPI
/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiLogger.h"
#include "MpiSendRecv.h"

namespace Util
{

   /*
   * Constructor.
   */
   MpiLogger::MpiLogger()
    : communicatorPtr_(&MPI_COMM_WORLD),
      rank_(-1),
      size_(-1)
   {}

   /*
   * Constructor.
   */
   MpiLogger::MpiLogger(MPI_Comm& comm)
    : communicatorPtr_(&comm),
      rank_(-1),
      size_(-1)
   {}

   /*
   */
   void MpiLogger::begin()
   {
      MPI_Barrier(*communicatorPtr_);
      MPI_Comm_rank(*communicatorPtr_, &rank_);
      MPI_Comm_size(*communicatorPtr_, &size_);
      int data;
      if (rank_ > 0) {
         recv<int>(*communicatorPtr_, data, rank_ - 1, 0);
      } else {
         std::cout << std::endl;
         std::cout.flush();
      }
   }

   /*
   */
   void MpiLogger::end()
   {
      std::cout.flush();
      if (rank_ < size_ - 1) {
         send<int>(*communicatorPtr_, rank_, rank_ + 1, 0);
      }
      MPI_Barrier(*communicatorPtr_);
   }

}
#endif
