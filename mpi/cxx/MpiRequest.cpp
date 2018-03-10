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

#include "MpiRequest.h"
#include "MpiDatatype.h"

namespace Util {
namespace Mpi {

   int Request::Waitany(int count, Request array[],
                        Status& status)
   {
      int index, i;
      MPI_Request* array_of_requests = new MPI_Request[count];
      for (i=0; i < count; i++) {
         array_of_requests[i] = array[i];
      }
      MPI_Waitany(count, array_of_requests, &index, &status.mpiStatus_);
      for (i=0; i < count; i++) {
         array[i] = array_of_requests[i];
      }
      delete [] array_of_requests;
      return index;
   }
   
   int Request::Waitany(int count, Request array[])
   {
      int index, i;
      MPI_Request* array_of_requests = new MPI_Request[count];
      for (i=0; i < count; i++) {
        array_of_requests[i] = array[i];
      }
      MPI_Waitany(count, array_of_requests, &index, MPI_STATUS_IGNORE);
      for (i=0; i < count; i++) {
        array[i] = array_of_requests[i];
      }
      delete [] array_of_requests;
      return index; //JGS, Waitany return value
   }
   
   bool Request::Testany(int count, Request array[],
            int& index, Status& status)
   {
      int i, flag;
      MPI_Request* array_of_requests = new MPI_Request[count];
      for (i=0; i < count; i++) {
        array_of_requests[i] = array[i];
      }
      MPI_Testany(count, array_of_requests, &index, &flag, &status.mpiStatus_);
      for (i=0; i < count; i++) {
        array[i] = array_of_requests[i];
      }
      delete [] array_of_requests;
      return (bool)(flag != 0 ? true : false);
   }
   
   bool
   Request::Testany(int count, Request array[], int& index)
   {
      int i, flag;
      MPI_Request* array_of_requests = new MPI_Request[count];
      for (i=0; i < count; i++) {
        array_of_requests[i] = array[i];
      }
      MPI_Testany(count, array_of_requests, &index, &flag,
               MPI_STATUS_IGNORE);
      for (i=0; i < count; i++) {
        array[i] = array_of_requests[i];
      }
      delete [] array_of_requests;
      return OPAL_INT_TO_BOOL(flag);
   }
   
   void
   Request::Waitall(int count, Request req_array[],
                    Status stat_array[])
   {
      int i;
      MPI_Request* array_of_requests = new MPI_Request[count];
      MPI_Status* array_of_statuses = new MPI_Status[count];
      for (i=0; i < count; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Waitall(count, array_of_requests, array_of_statuses);
      for (i=0; i < count; i++) {
        req_array[i] = array_of_requests[i];
        stat_array[i] = array_of_statuses[i];
      }
      delete [] array_of_requests;
      delete [] array_of_statuses;
   }
   
   void
   Request::Waitall(int count, Request req_array[])
   {
      int i;
      MPI_Request* array_of_requests = new MPI_Request[count];
   
      for (i=0; i < count; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Waitall(count, array_of_requests, MPI_STATUSES_IGNORE);
   
      for (i=0; i < count; i++) {
        req_array[i] = array_of_requests[i];
      }
   
      delete [] array_of_requests;
   }
   
   bool
   Request::Testall(int count, Request req_array[],
                    Status stat_array[])
   {
      int i, flag;
      MPI_Request* array_of_requests = new MPI_Request[count];
      MPI_Status* array_of_statuses = new MPI_Status[count];
      for (i=0; i < count; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Testall(count, array_of_requests, &flag, array_of_statuses);
      for (i=0; i < count; i++) {
        req_array[i] = array_of_requests[i];
        stat_array[i] = array_of_statuses[i];
      }
      delete [] array_of_requests;
      delete [] array_of_statuses;
      return OPAL_INT_TO_BOOL(flag);
   }
   
   bool
   Request::Testall(int count, Request req_array[])
   {
      int i, flag;
      MPI_Request* array_of_requests = new MPI_Request[count];
   
      for (i=0; i < count; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Testall(count, array_of_requests, &flag, MPI_STATUSES_IGNORE);
   
      for (i=0; i < count; i++) {
        req_array[i] = array_of_requests[i];
      }
      delete [] array_of_requests;
   
      return OPAL_INT_TO_BOOL(flag);
   }
   
   int
   Request::Waitsome(int incount, Request req_array[],
                     int array_of_indices[], Status stat_array[])
   {
      int i, outcount;
      MPI_Request* array_of_requests = new MPI_Request[incount];
      MPI_Status* array_of_statuses = new MPI_Status[incount];
      for (i=0; i < incount; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Waitsome(incount, array_of_requests, &outcount,
                array_of_indices, array_of_statuses);
      for (i=0; i < incount; i++) {
        req_array[i] = array_of_requests[i];
        stat_array[i] = array_of_statuses[i];
      }
      delete [] array_of_requests;
      delete [] array_of_statuses;
      return outcount;
   }
   
   int
   Request::Waitsome(int incount, Request req_array[],
                     int array_of_indices[])
   {
      int i, outcount;
      MPI_Request* array_of_requests = new MPI_Request[incount];
   
      for (i=0; i < incount; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Waitsome(incount, array_of_requests, &outcount,
                   array_of_indices, MPI_STATUSES_IGNORE);
   
      for (i=0; i < incount; i++) {
        req_array[i] = array_of_requests[i];
      }
      delete [] array_of_requests;
   
      return outcount;
   }
   
   int
   Request::Testsome(int incount, Request req_array[],
                     int array_of_indices[], Status stat_array[])
   {
      int i, outcount;
      MPI_Request* array_of_requests = new MPI_Request[incount];
      MPI_Status* array_of_statuses = new MPI_Status[incount];
      for (i=0; i < incount; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Testsome(incount, array_of_requests, &outcount,
                array_of_indices, array_of_statuses);
      for (i=0; i < incount; i++) {
        req_array[i] = array_of_requests[i];
        stat_array[i] = array_of_statuses[i];
      }
      delete [] array_of_requests;
      delete [] array_of_statuses;
      return outcount;
   }
   
   int Request::Testsome(int incount, Request req_array[],
                         int array_of_indices[])
   {
      int i, outcount;
      MPI_Request* array_of_requests = new MPI_Request[incount];
   
      for (i=0; i < incount; i++) {
        array_of_requests[i] = req_array[i];
      }
      MPI_Testsome(incount, array_of_requests, &outcount,
                   array_of_indices, MPI_STATUSES_IGNORE);
   
      for (i=0; i < incount; i++) {
        req_array[i] = array_of_requests[i];
      }
      delete [] array_of_requests;
   
      return outcount;
   }

}
}

