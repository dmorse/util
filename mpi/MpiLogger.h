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
   *    int rank;
   *    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   *    std::cout << "Print from processor " << rank << std::endl;
   *    logger.endl();
   * \endcode
   */
   class MpiLogger
   {

   public:

      /**
      * Default constructor.
      * 
      * Sets communicator to MPI_COMM_WORLD.
      */
      MpiLogger();

      /**
      * Constructor.
      *  
      * \param comm MPI communicator to use.
      */
      MpiLogger(MPI_Comm comm);

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
      MPI_Comm communicator_;

      /// Mpi processor rank.
      int rank_;

      /// Mpi communicator size.
      int size_;

   };

}

#endif
#endif
