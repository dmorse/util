#ifdef  UTIL_MPI
#ifndef UTIL_MPI_LOGGER_H
#define UTIL_MPI_LOGGER_H

/*
* Util Package - C++ Utilities for Scientific Computation
*
* Copyright 2010 - 2017, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <util/global.h>

#include <iostream>
#include <string>

namespace Util
{

   /**
   * Allows information from every processor in a communicator,
   * to be output in rank sequence.
   *
   * The begin() method for processor of rank > 0 waits for receipt 
   * of a message from processor rank - 1. The end() method sends a
   * message to processor rank + 1.
   *
   * Usage:
   *
   * \code
   *    MpiLogger logger;
   *    logger.begin();
   *    std::cout << "Print from processor " << MPI::COMM_WORLD.Get_rank() << std::endl;
   *    logger.endl();
   * \endcode
   *
   * \ingroup Util_Mpi_Module
   */
   class MpiLogger
   {

   public:

      /**
      * Constructor.
      */
      MpiLogger(MPI::Intracomm& comm = MPI::COMM_WORLD);

      /**
      * Begin logging block.
      */
      void begin();

      /**
      * End logging block.
      */
      void end();


   private:

      /// Pointer to the  communicator.
      MPI::Intracomm* communicatorPtr_;

      /// Mpi processor rank.
      int rank_;

      /// Mpi communicator size.
      int size_;

   };

}

#endif
#endif
