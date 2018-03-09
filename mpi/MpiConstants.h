#ifdef UTIL_MPI
#ifndef UTIL_MPI_CONSTANTS_H
#define UTIL_MPI_CONSTANTS_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <mpi.h>

namespace Util {
namespace Mpi {

   class Datatype;
   class Group;
   class Comm;
   class Request;
   class Op;
   class Errhandler;
   //class File;
   //class Win;
   //class Info;

   // return  codes
   static const int SUCCESS = MPI_SUCCESS;
   static const int ERR_BUFFER = MPI_ERR_BUFFER;
   static const int ERR_COUNT = MPI_ERR_COUNT;
   static const int ERR_TYPE = MPI_ERR_TYPE;
   static const int ERR_TAG  = MPI_ERR_TAG ;
   static const int ERR_COMM = MPI_ERR_COMM;
   static const int ERR_RANK = MPI_ERR_RANK;
   static const int ERR_REQUEST = MPI_ERR_REQUEST;
   static const int ERR_ROOT = MPI_ERR_ROOT;
   static const int ERR_GROUP = MPI_ERR_GROUP;
   static const int ERR_OP = MPI_ERR_OP;
   static const int ERR_TOPOLOGY = MPI_ERR_TOPOLOGY;
   static const int ERR_DIMS = MPI_ERR_DIMS;
   static const int ERR_ARG = MPI_ERR_ARG;
   static const int ERR_UNKNOWN = MPI_ERR_UNKNOWN;
   static const int ERR_TRUNCATE = MPI_ERR_TRUNCATE;
   static const int ERR_OTHER = MPI_ERR_OTHER;
   static const int ERR_INTERN = MPI_ERR_INTERN;
   static const int ERR_PENDING = MPI_ERR_PENDING;
   static const int ERR_IN_STATUS = MPI_ERR_IN_STATUS;
   static const int ERR_ACCESS = MPI_ERR_ACCESS;
   static const int ERR_AMODE = MPI_ERR_AMODE;
   static const int ERR_ASSERT = MPI_ERR_ASSERT;
   static const int ERR_BAD_FILE = MPI_ERR_BAD_FILE;
   static const int ERR_BASE = MPI_ERR_BASE;
   static const int ERR_CONVERSION = MPI_ERR_CONVERSION;
   static const int ERR_DISP = MPI_ERR_DISP;
   static const int ERR_DUP_DATAREP = MPI_ERR_DUP_DATAREP;
   static const int ERR_FILE_EXISTS = MPI_ERR_FILE_EXISTS;
   static const int ERR_FILE_IN_USE = MPI_ERR_FILE_IN_USE;
   static const int ERR_FILE = MPI_ERR_FILE;
   static const int ERR_INFO_KEY = MPI_ERR_INFO_KEY;
   static const int ERR_INFO_NOKEY = MPI_ERR_INFO_NOKEY;
   static const int ERR_INFO_VALUE = MPI_ERR_INFO_VALUE;
   static const int ERR_INFO = MPI_ERR_INFO;
   static const int ERR_IO = MPI_ERR_IO;
   static const int ERR_KEYVAL = MPI_ERR_KEYVAL;
   static const int ERR_LOCKTYPE = MPI_ERR_LOCKTYPE;
   static const int ERR_NAME = MPI_ERR_NAME;
   static const int ERR_NO_MEM = MPI_ERR_NO_MEM;
   static const int ERR_NOT_SAME = MPI_ERR_NOT_SAME;
   static const int ERR_NO_SPACE = MPI_ERR_NO_SPACE;
   static const int ERR_NO_SUCH_FILE = MPI_ERR_NO_SUCH_FILE;
   static const int ERR_PORT = MPI_ERR_PORT;
   static const int ERR_QUOTA = MPI_ERR_QUOTA;
   static const int ERR_READ_ONLY = MPI_ERR_READ_ONLY;
   static const int ERR_RMA_CONFLICT = MPI_ERR_RMA_CONFLICT;
   static const int ERR_RMA_SYNC = MPI_ERR_RMA_SYNC;
   static const int ERR_SERVICE = MPI_ERR_SERVICE;
   static const int ERR_SIZE = MPI_ERR_SIZE;
   static const int ERR_SPAWN = MPI_ERR_SPAWN;
   static const int ERR_UNSUPPORTED_DATAREP = MPI_ERR_UNSUPPORTED_DATAREP;
   static const int ERR_UNSUPPORTED_OPERATION = MPI_ERR_UNSUPPORTED_OPERATION;
   static const int ERR_WIN = MPI_ERR_WIN;
   static const int ERR_LASTCODE = MPI_ERR_LASTCODE;
   
   // assorted constants
   static const int PROC_NULL = MPI_PROC_NULL;
   static const int ANY_SOURCE = MPI_ANY_SOURCE;
   static const int ROOT = MPI_ROOT;
   static const int ANY_TAG = MPI_ANY_TAG;
   static const int UNDEFINED = MPI_UNDEFINED;
   static const int BSEND_OVERHEAD = MPI_BSEND_OVERHEAD;
   static const int KEYVAL_INVALID = MPI_KEYVAL_INVALID;
   static const int ORDER_C = MPI_ORDER_C;
   static const int ORDER_FORTRAN = MPI_ORDER_FORTRAN;
   static const int DISTRIBUTE_BLOCK = MPI_DISTRIBUTE_BLOCK;
   static const int DISTRIBUTE_CYCLIC = MPI_DISTRIBUTE_CYCLIC;
   static const int DISTRIBUTE_NONE = MPI_DISTRIBUTE_NONE;
   static const int DISTRIBUTE_DFLT_DARG = MPI_DISTRIBUTE_DFLT_DARG;
   
   // typeclass definitions for MPI_Type_match_size
   static const int TYPECLASS_INTEGER = MPI_TYPECLASS_INTEGER;
   static const int TYPECLASS_REAL = MPI_TYPECLASS_REAL;
   static const int TYPECLASS_COMPLEX = MPI_TYPECLASS_COMPLEX;
   
   // maximum sizes for strings
   static const int MAX_PROCESSOR_NAME = MPI_MAX_PROCESSOR_NAME;
   static const int MAX_ERROR_STRING = MPI_MAX_ERROR_STRING;
   static const int MAX_INFO_KEY = MPI_MAX_INFO_KEY;
   static const int MAX_INFO_VAL = MPI_MAX_INFO_VAL;
   static const int MAX_PORT_NAME = MPI_MAX_PORT_NAME;
   static const int MAX_OBJECT_NAME = MPI_MAX_OBJECT_NAME;
  
   #if 0 
   // Error-handling specifiers
   extern const Errhandler  ERRORS_ARE_FATAL;
   extern const Errhandler  ERRORS_RETURN;
   extern const Errhandler  ERRORS_THROW_EXCEPTIONS;
   #endif
   
   // Elementary datatypes (C / C++)
   extern const Datatype CHAR;
   extern const Datatype SHORT;
   extern const Datatype INT;
   extern const Datatype LONG;
   extern const Datatype SIGNED_CHAR;
   extern const Datatype UNSIGNED_CHAR;
   extern const Datatype UNSIGNED_SHORT;
   extern const Datatype UNSIGNED;
   extern const Datatype UNSIGNED_LONG;
   extern const Datatype FLOAT;
   extern const Datatype DOUBLE;
   extern const Datatype LONG_DOUBLE;
   extern const Datatype BYTE;
   extern const Datatype PACKED;
   extern const Datatype WCHAR;
   
   // Datatypes for reductions functions (C / C++)
   extern const Datatype FLOAT_INT;
   extern const Datatype DOUBLE_INT;
   extern const Datatype LONG_INT;
   extern const Datatype TWOINT;
   extern const Datatype SHORT_INT;
   extern const Datatype LONG_DOUBLE_INT;
   
   // Optional datatype (C / C++)
   extern const Datatype LONG_LONG;
   extern const Datatype LONG_LONG_INT;
   extern const Datatype UNSIGNED_LONG_LONG;
   
   // c++ datatypes
   extern const Datatype BOOL;
   extern const Datatype COMPLEX;
   extern const Datatype DOUBLE_COMPLEX;
   extern const Datatype F_DOUBLE_COMPLEX;
   extern const Datatype LONG_DOUBLE_COMPLEX;
   
   // special datatypes for contstruction of derived datatypes
   extern const Datatype UB;
   extern const Datatype LB;
   
   // datatype decoding constants
   static const int COMBINER_NAMED = MPI_COMBINER_NAMED;
   static const int COMBINER_DUP = MPI_COMBINER_DUP;
   static const int COMBINER_CONTIGUOUS = MPI_COMBINER_CONTIGUOUS;
   static const int COMBINER_VECTOR = MPI_COMBINER_VECTOR;
   static const int COMBINER_HVECTOR_INTEGER = MPI_COMBINER_HVECTOR_INTEGER;
   static const int COMBINER_HVECTOR = MPI_COMBINER_HVECTOR;
   static const int COMBINER_INDEXED = MPI_COMBINER_INDEXED;
   static const int COMBINER_HINDEXED_INTEGER = MPI_COMBINER_HINDEXED_INTEGER;
   static const int COMBINER_HINDEXED = MPI_COMBINER_HINDEXED;
   static const int COMBINER_INDEXED_BLOCK = MPI_COMBINER_INDEXED_BLOCK;
   static const int COMBINER_STRUCT_INTEGER = MPI_COMBINER_STRUCT_INTEGER;
   static const int COMBINER_STRUCT = MPI_COMBINER_STRUCT;
   static const int COMBINER_SUBARRAY = MPI_COMBINER_SUBARRAY;
   static const int COMBINER_DARRAY = MPI_COMBINER_DARRAY;
   static const int COMBINER_F90_REAL = MPI_COMBINER_F90_REAL;
   static const int COMBINER_F90_COMPLEX = MPI_COMBINER_F90_COMPLEX;
   static const int COMBINER_F90_INTEGER = MPI_COMBINER_F90_INTEGER;
   static const int COMBINER_RESIZED = MPI_COMBINER_RESIZED;
   
   // Thread constants
   static const int THREAD_SINGLE = MPI_THREAD_SINGLE;
   static const int THREAD_FUNNELED = MPI_THREAD_FUNNELED;
   static const int THREAD_SERIALIZED = MPI_THREAD_SERIALIZED;
   static const int THREAD_MULTIPLE = MPI_THREAD_MULTIPLE;
   
   // Reserved communicators
   extern Intracomm COMM_WORLD;
   extern Intracomm COMM_SELF;
   
   // results of communicator and group comparisons
   static const int IDENT = MPI_IDENT;
   static const int CONGRUENT = MPI_CONGRUENT;
   static const int SIMILAR = MPI_SIMILAR;
   static const int UNEQUAL = MPI_UNEQUAL;
   
   // Environmental inquiry keys
   static const int TAG_UB = MPI_TAG_UB;
   static const int HOST = MPI_HOST;
   static const int IO = MPI_IO;
   static const int WTIME_IS_GLOBAL = MPI_WTIME_IS_GLOBAL;
   static const int APPNUM = MPI_APPNUM;
   static const int LASTUSEDCODE = MPI_LASTUSEDCODE;
   static const int UNIVERSE_SIZE = MPI_UNIVERSE_SIZE;
   static const int WIN_BASE = MPI_WIN_BASE;
   static const int WIN_SIZE = MPI_WIN_SIZE;
   static const int WIN_DISP_UNIT = MPI_WIN_DISP_UNIT;
   
   // collective operations
   extern const Op MAX;
   extern const Op MIN;
   extern const Op SUM;
   extern const Op PROD;
   extern const Op MAXLOC;
   extern const Op MINLOC;
   extern const Op BAND;
   extern const Op BOR;
   extern const Op BXOR;
   extern const Op LAND;
   extern const Op LOR;
   extern const Op LXOR;
   extern const Op REPLACE;
  
   // null handles
   extern const Datatype     DATATYPE_NULL;
   extern const Group        GROUP_NULL;
   extern Comm               COMM_NULL;
   extern Request            REQUEST_NULL;
   extern const Op           OP_NULL;
   //extern const Errhandler   ERRHANDLER_NULL;
   //extern const File         FILE_NULL;
   //extern const Win          WIN_NULL;
   //extern const Info         INFO_NULL;
   
   // Constants specifying empty or ignored input
   extern const char**       ARGV_NULL;
   extern const char***      ARGVS_NULL;
   
   // Empty group
   extern const Group        GROUP_EMPTY;
   
   // Topologies
   static const int GRAPH = MPI_GRAPH;
   static const int CART = MPI_CART;

}
}
#endif
#endif
   
