#ifdef  UTIL_MPI

#include <string.h>
/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiSendRecv.h"

namespace Util
{

   // bool explicit specializations
 
   template <>
   void send<bool>(MPI_Comm comm, bool& data, int dest, int tag)
   { 
      int value = data ? 1 : 0;
      send<int>(comm, value, dest, tag);
   }

   template <>
   void recv<bool>(MPI_Comm comm, bool& data, int source, int tag)
   { 
      int value;
      recv<int>(comm, value, source, tag);
      data = value ? true : false;
   }

   template <>
   void bcast<bool>(MPI_Comm comm, bool& data, int root)
   { 
      int value;
      int rank;
      MPI_Comm_rank(comm, &rank);
      if (rank == root) 
         value = data ? 1 : 0;
      bcast<int>(comm, value, root);
      if (rank != root) 
         data = value ? true : false;
   }

   // std::string explicit specializations
 
   template <>
   void send<std::string>(MPI_Comm comm, std::string& data, int dest, int tag)
   { 

      // Send size of char C array
      int count = data.size() + 1;
      send<int>(comm, count, dest, tag);

      // Send string contents as char array
      char* cstr = new char[count];
      strcpy(cstr, data.c_str());
      send<char>(comm, cstr, count, dest, tag); 
      delete [] cstr;

   }

   template <>
   void recv<std::string>(MPI_Comm comm, std::string& data, int source, int tag)
   { 

      // Receive size of char C array
      int  count;
      recv<int>(comm, count, source, tag);

      // Receive contents as char C array
      char* cstr = new char[count];
      recv<char>(comm, cstr, count, source, tag); 
      data = cstr;
      delete [] cstr;

   }

   template <>
   void bcast<std::string>(MPI_Comm comm, std::string& data, int root)
   { 
      int rank;
      MPI_Comm_rank(comm, &rank);
      int count;

      // Broadcast string count
      if (rank == root) 
         count = data.size() + 1;
      bcast<int>(comm, count, root);

      // Broadcast std::string contents as C string
      char* cstr = new char[count];
      if (rank == root) 
         strcpy(cstr, data.c_str());
      bcast<char>(comm, cstr, count, root); 
      if (rank != root) 
         data = cstr;
      delete [] cstr;

   }

}
#endif
