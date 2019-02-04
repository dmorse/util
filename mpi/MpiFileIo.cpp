/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiFileIo.h"

namespace Util
{

   /*
   * Constructor.
   *
   * Note: Default constructor for _indent string creates an empty string.
   */
   MpiFileIo::MpiFileIo() 
    : isIoProcessor_(true)
      #ifdef UTIL_MPI
      , hasCommunicator_(false)
      #endif
   {}

   /*
   * Copy constructor.
   */
   MpiFileIo::MpiFileIo(const MpiFileIo& other) 
    : isIoProcessor_(other.isIoProcessor_)
      #ifdef UTIL_MPI
      , communicator_(other.communicator_)
      , hasCommunicator_(other.hasCommunicator_)
      #endif
   {}

   #ifdef UTIL_MPI
   void MpiFileIo::setIoCommunicator(MPI_Comm communicator)
   {
      communicator_ = communicator; 
      hasCommunicator_ = true;
      int rank;
      MPI_Comm_rank(communicator, &rank);
      if (rank == 0) {
         isIoProcessor_ = true;
      } else {
         isIoProcessor_ = false;
      }
   }

   void MpiFileIo::clearCommunicator()
   {
      hasCommunicator_ = false; 
      isIoProcessor_  = true;
   }
   #endif

} 
