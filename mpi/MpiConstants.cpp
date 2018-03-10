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
#include "MpiGroup.h"
#include "MpiComm.h"
#include "MpiIntracomm.h"
#include "MpiRequest.h"
#include "MpiOp.h"
#include "MpiErrhandler.h"
#include "MpiInfo.h"

namespace Util {
namespace Mpi {

   int mpi_errno = MPI_SUCCESS;
   
   // static void* const BOTTOM = (void*) MPI_BOTTOM;
   // static void* const IN_PLACE = (void*) MPI_IN_PLACE;

   #if 0   
   // Error-handling specifiers
   const Errhandler  ERRORS_ARE_FATAL((MPI_Errhandler)&(ompi_mpi_errors_are_fatal));
   const Errhandler  ERRORS_RETURN((MPI_Errhandler)&(ompi_mpi_errors_return));
   const Errhandler  ERRORS_THROW_EXCEPTIONS((MPI_Errhandler)&(ompi_mpi_errors_throw_exceptions));
   #endif
   
   // Elementary C+ datatypes
   const Datatype CHAR(MPI_CHAR);
   const Datatype SHORT(MPI_SHORT);
   const Datatype INT(MPI_INT);
   const Datatype LONG(MPI_LONG);
   const Datatype SIGNED_CHAR(MPI_SIGNED_CHAR);
   const Datatype UNSIGNED_CHAR(MPI_UNSIGNED_CHAR);
   const Datatype UNSIGNED_SHORT(MPI_UNSIGNED_SHORT);
   const Datatype UNSIGNED(MPI_UNSIGNED);
   const Datatype UNSIGNED_LONG(MPI_UNSIGNED_LONG);
   const Datatype FLOAT(MPI_FLOAT);
   const Datatype DOUBLE(MPI_DOUBLE);
   const Datatype LONG_DOUBLE(MPI_LONG_DOUBLE);
   const Datatype BYTE(MPI_BYTE);
   const Datatype PACKED(MPI_PACKED);
   const Datatype WCHAR(MPI_WCHAR);
   
   // Datatypes for reduction functions (C / C++)
   const Datatype FLOAT_INT(MPI_FLOAT_INT);
   const Datatype DOUBLE_INT(MPI_DOUBLE_INT);
   const Datatype LONG_INT(MPI_LONG_INT);
   const Datatype TWOINT(MPI_2INT);
   const Datatype SHORT_INT(MPI_SHORT_INT);
   const Datatype LONG_DOUBLE_INT(MPI_LONG_DOUBLE_INT);
   
   // optional datatype (C / C++)
   const Datatype UNSIGNED_LONG_LONG(MPI_UNSIGNED_LONG_LONG);
   const Datatype LONG_LONG(MPI_LONG_LONG);
   const Datatype LONG_LONG_INT(MPI_LONG_LONG_INT);
   
   // c++ types
   // const Datatype BOOL((MPI_Datatype)&(ompi_mpi_cxx_bool));
   // const Datatype COMPLEX((MPI_Datatype)&(ompi_mpi_cxx_cplex));
   // const Datatype DOUBLE_COMPLEX((MPI_Datatype)&(ompi_mpi_cxx_dblcplex));
   // const Datatype F_DOUBLE_COMPLEX((MPI_Datatype)&(ompi_mpi_cxx_dblcplex));
   // const Datatype LONG_DOUBLE_COMPLEX((MPI_Datatype)&(ompi_mpi_cxx_ldblcplex));
   
   // reserved communicators
   Intracomm COMM_WORLD(MPI_COMM_WORLD);
   Intracomm COMM_SELF(MPI_COMM_SELF);
   
   // Reported by Paul Hargrove: MIN and MAX are defined on OpenBSD, so
   // we need to #undef them.  See
   // http://www.open-mpi.org/community/lists/devel/2013/12/13521.php.
   #ifdef MAX
   #undef MAX
   #endif
   #ifdef MIN
   #undef MIN
   #endif
   
   // collective operations
   const Op MAX(MPI_MAX);
   const Op MIN(MPI_MIN);
   const Op SUM(MPI_SUM);
   const Op PROD(MPI_PROD);
   const Op MAXLOC(MPI_MAXLOC);
   const Op MINLOC(MPI_MINLOC);
   const Op BAND(MPI_BAND);
   const Op BOR(MPI_BOR);
   const Op BXOR(MPI_BXOR);
   const Op LAND(MPI_LAND);
   const Op LOR(MPI_LOR);
   const Op LXOR(MPI_LXOR);
   const Op REPLACE(MPI_REPLACE);
   
   // null handles
   const Group         GROUP_NULL = MPI_GROUP_NULL;
   const Datatype      DATATYPE_NULL = MPI_DATATYPE_NULL;
   Request             REQUEST_NULL = MPI_REQUEST_NULL;
   const Op            OP_NULL = MPI_OP_NULL;
   const Errhandler    ERRHANDLER_NULL;
   const Info          INFO_NULL = MPI_INFO_NULL;
   //const File        FILE_NULL = MPI_FILE_NULL;
   //const Win         WIN_NULL = MPI_WIN_NULL;
   
   // constants specifying empty or ignored input
   const char**       ARGV_NULL = (const char**) MPI_ARGV_NULL;
   const char***      ARGVS_NULL = (const char***) MPI_ARGVS_NULL;
   
   // empty group
   const Group GROUP_EMPTY(MPI_GROUP_EMPTY);
  
   #if 0 // Deprecated datatypes (compiler warnings) 
   // special datatypes for contstruction of derived datatypes
   const Datatype UB(MPI_UB);
   const Datatype LB(MPI_LB);
   #endif

}
}

