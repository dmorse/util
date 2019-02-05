/*
* This program runs all unit tests in the util/param directory.
*/ 

#ifdef  UTIL_MPI
#ifndef TEST_MPI
#define TEST_MPI
#endif
#endif

#include "serial/ParamTestComposite.h"
#ifdef  UTIL_MPI
#include "mpi/MpiParamTestComposite.h"
#endif

#include <test/CompositeTestRunner.h>

using namespace Util;

TEST_COMPOSITE_BEGIN(ParamAllTestComposite)
addChild(new ParamTestComposite, "serial/");
#ifdef UTIL_MPI
addChild(new MpiParamTestComposite, "mpi/");
#endif 
TEST_COMPOSITE_END

int main(int argc, char* argv[])
{
   try {

      #ifdef UTIL_MPI
      MPI::Init();
      Vector::commitMpiType();
      IntVector::commitMpiType();
      #endif 
   
      ParamAllTestComposite runner;
   
      if (argc > 2) {
         UTIL_THROW("Too many arguments");
      }
      if (argc == 2) {
         runner.addFilePrefix(argv[1]);
      }

      // Run the composite unit test runner
      int failures = runner.run();

      #ifdef UTIL_MPI
      MPI::Finalize();
      #endif 

      return (failures != 0);

   } catch (...) {

      //std::cerr << "Uncaught exception" << std::endl;
      //return EXIT_FAILURE;

      UTIL_THROW("Uncaught exception");

   }

}
