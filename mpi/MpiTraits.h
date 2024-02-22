#ifdef UTIL_MPI
#ifndef UTIL_MPI_TRAITS_H
#define UTIL_MPI_TRAITS_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>
#include <complex>


namespace Util 
{

   /**
   * Base class for MpiTraits with no type.
   *
   * \ingroup Util_Mpi_Module
   */
   class MpiTraitsNoType
   {
   protected:
      MpiTraitsNoType(){};
      ~MpiTraitsNoType(){}; 
      static const MPI::Datatype type;   ///< MPI Datatype (dummy - unused)
      static const bool hasType;         ///< Is the MPI type initialized?
   };

   /**
   * Default MpiTraits class.
   *
   * Each explicit specialization of MpiTraits has a public
   * static const member named type. This is the MPI data
   * type associated with the C++ template type parameter.
   *
   * \ingroup Util_Mpi_Module
   */
   template <typename T>
   class MpiTraits : public MpiTraitsNoType
   {
   public: 
      using MpiTraitsNoType::hasType;
      using MpiTraitsNoType::type;
   };

   /**
   * MpiTraits<char> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<char>
   {  
   public: 
      static const MPI::Datatype type;   ///< MPI Datatype
      static const bool hasType;         ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<unsigned char> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<unsigned char>
   {  
   public: 
      static const MPI::Datatype type;   ///< MPI Datatype
      static const bool hasType;         ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<short> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<short>
   {  
   public: 
      static const MPI::Datatype type;   ///< MPI Datatype
      static const bool hasType;         ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<int> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<int>
   {  
   public: 
      static const MPI::Datatype type;   ///< MPI Datatype
      static const bool hasType;         ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<long> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<long>
   {  
   public: 
      static const MPI::Datatype type;   ///< MPI Datatype
      static const bool hasType;         ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<unsigned short> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<unsigned short>
   {  
   public: 
      static const MPI::Datatype type;   ///< MPI Datatype
      static const bool hasType;         ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<unsigned int> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<unsigned int>
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype
      static const bool hasType;        ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<unsigned long> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<unsigned long>
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype
      static const bool hasType;        ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<float> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<float>
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype
      static const bool hasType;        ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<double> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<double>
   {  
   public: 
      static const MPI::Datatype type; ///< MPI Datatype
      static const bool hasType;       ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<long double> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<long double>
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype 
      static const bool hasType;        ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits<bool> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<bool>
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype
      static const bool hasType;        ///< Is the MPI type initialized?
   };

   #if 0
   /**
   * MpiTraits< std::complex<float> > explicit specialization.
   */
   template <>
   class MpiTraits< std::complex<float> >
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype
      static const bool hasType;        ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits< std::complex<double> > explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits< std::complex<double> >
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype
      static const bool hasType;        ///< Is the MPI type initialized?
   };

   /**
   * MpiTraits< std::complex<long double> > explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits< std::complex<long double> >
   {  
   public: 
      static const MPI::Datatype type; ///< MPI Datatype
      static const bool hasType;       ///< Is the MPI type initialized?
   };
   #endif

   #if 0
   /**
   * MpiTraits<wchar_t> explicit specialization.
   *
   * \ingroup Util_Mpi_Module
   */
   template <>
   class MpiTraits<wchar_t>
   {  
   public: 
      static const MPI::Datatype type;  ///< MPI Datatype
      static const bool hasType;        ///< Is the MPI type initialized?
   };
   #endif

}
#endif
#endif
