/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "MpiTraits.h"

namespace Util 
{

   const MPI_Datatype MpiTraitsNoType::type = MPI_CHAR; 
   const bool MpiTraitsNoType::hasType = false;

   const MPI_Datatype MpiTraits<char>::type = MPI_CHAR; 
   const bool MpiTraits<char>::hasType = true;

   const MPI_Datatype MpiTraits<unsigned char>::type = MPI_UNSIGNED_CHAR; 
   const bool MpiTraits<unsigned char>::hasType = true;

   const MPI_Datatype MpiTraits<short>::type = MPI_SHORT_INT; 
   const bool MpiTraits<short>::hasType = true;

   const MPI_Datatype MpiTraits<int>::type  = MPI_INT; 
   const bool MpiTraits<int>::hasType = true;

   const MPI_Datatype MpiTraits<long>::type = MPI_LONG; 
   const bool MpiTraits<long>::hasType = true;

   const MPI_Datatype MpiTraits<unsigned short>::type = MPI_UNSIGNED_SHORT; 
   const bool MpiTraits<unsigned short>::hasType = true;

   const MPI_Datatype MpiTraits<unsigned int>::type = MPI_UNSIGNED; 
   const bool MpiTraits<unsigned int>::hasType = true;

   const MPI_Datatype MpiTraits<unsigned long >::type = MPI_UNSIGNED_LONG; 
   const bool MpiTraits<unsigned long>::hasType = true;

   const MPI_Datatype MpiTraits<float>::type = MPI_FLOAT; 
   const bool MpiTraits<float>::hasType = true;

   const MPI_Datatype MpiTraits<double>::type = MPI_DOUBLE; 
   const bool MpiTraits<double>::hasType = true;

   const MPI_Datatype MpiTraits<long double>::type = MPI_LONG_DOUBLE; 
   const bool MpiTraits<long double>::hasType = true;

   const MPI_Datatype MpiTraits<bool>::type = MPI_BYTE; 
   const bool MpiTraits<bool>::hasType = false;

   #if 0
   const MPI_Datatype MpiTraits<std::complex<float> >::type = MPI_FLOAT_COMPLEX; 
   const bool MpiTraits<std::complex<float> >::hasType = true;

   const MPI_Datatype MpiTraits<std::complex<double> >::type = MPI_DOUBLE_COMPLEX; 
   const bool MpiTraits<std::complex<double> >::hasType = true;

   const MPI_Datatype MpiTraits<std::complex<long double> >::type = MPI_LONG_DOUBLE_COMPLEX; 
   const bool MpiTraits<std::complex<long double> >::hasType = true;
   #endif

   #if 0
   const MPI_Datatype MpiTraits<wchar_t>::type = MPI_WCHAR; 
   const bool MpiTraits<wchar_t>::hasType = true;
   #endif
}
