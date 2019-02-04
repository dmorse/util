/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MemoryOArchive.h"
#include <util/misc/Memory.h>

#include <sstream>

namespace Util
{

   /*
   * Constructor.
   */
   MemoryOArchive::MemoryOArchive()
    : buffer_(0),
      begin_(0),
      cursor_(0),
      endAllocated_(0),
      capacity_(0),
      version_(0),
      isLocked_(false),
      ownsData_(false)
   {}

   /*
   * Destructor.
   */
   MemoryOArchive::~MemoryOArchive()
   {  
      if (buffer_ && ownsData_) {
         //delete buffer_; 
         Memory::deallocate<Byte>(buffer_, capacity_ + sizeof(size_t));
      }
   }

   /*
   * Allocate a block of memory.
   */
   void MemoryOArchive::allocate(size_t capacity)
   {
      if (begin_) {
         UTIL_THROW("Re-allocation is prohibited");
      }
      // buffer_ = new Byte[capacity + sizeof(size_t)];
      Memory::allocate<Byte>(buffer_, capacity + sizeof(size_t));
      begin_  = buffer_ + sizeof(size_t);
      cursor_ = begin();
      endAllocated_ = begin_ + capacity; 
      capacity_ = capacity;
      ownsData_ = true; 
      isLocked_ = false;
   }

   /*
   * Return cursor to beginning.
   */
   void MemoryOArchive::clear()
   {
      if (!isAllocated()) {
         UTIL_THROW("Archive is not allocated");
      }  
      cursor_ = begin(); 
   }

   #ifdef UTIL_MPI
   /*
   * Send a block.
   */
   void MemoryOArchive::send(MPI_Comm comm, int dest)
   {
      int  comm_size;
      MPI_Comm_size(comm, &comm_size);
      int  myRank;
      MPI_Comm_rank(comm, &myRank);

      // Preconditions
      if (dest > comm_size - 1 || dest < 0) {
         UTIL_THROW("Destination rank out of bounds");
      }
      if (dest == myRank) {
         UTIL_THROW("Source and desination identical");
      }

      size_t  sendBytes = cursor_ - buffer_;
      size_t* sizePtr = (size_t*)buffer_;
      *sizePtr = sendBytes;
      MPI_Send(buffer_, sendBytes, MPI_UNSIGNED_CHAR, dest, 5, comm);

   }

   /*
   * Send a block (nonblocking)
   */
   void MemoryOArchive::iSend(MPI_Comm comm, MPI_Request& req, int dest)
   {
      int  comm_size;
      MPI_Comm_size(comm, &comm_size);
      int  myRank;
      MPI_Comm_rank(comm, &myRank);

      // Preconditions
      if (dest > comm_size - 1 || dest < 0) {
         UTIL_THROW("Destination rank out of bounds");
      }
      if (dest == myRank) {
         UTIL_THROW("Source and desination identical");
      }

      size_t  sendBytes = cursor_ - buffer_;
      size_t* sizePtr = (size_t*)buffer_;
      *sizePtr = sendBytes;
      MPI_Isend(buffer_, sendBytes, MPI_UNSIGNED_CHAR, dest, 5, comm, &req);
   }
 
   #endif

}
