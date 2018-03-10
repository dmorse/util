/*
* This program runs all unit tests in the util directory.
*/ 

#ifdef  UTIL_MPI
#ifndef TEST_MPI
#define TEST_MPI
#endif
#endif

#include "accumulators/unit/AccumulatorTestComposite.h"
#include "archives/ArchiveTestComposite.h"
#include "containers/ContainersTestComposite.h"
#include "crystal/CrystalTestComposite.h"
#include "format/FormatTest.h"
#include "math/MathTestComposite.h"
#include "param/serial/ParamTestComposite.h"
#include "random/RandomTest.h"
#include "signal/SignalTest.h"
#include "space/SpaceTestComposite.h"
#include "misc/MiscTestComposite.h"

#ifdef  UTIL_MPI
#include "param/mpi/MpiParamTestComposite.h"
#include "mpi/MpiSendRecvTest.h"
#endif

#include <test/CompositeTestRunner.h>

using namespace Util;

TEST_COMPOSITE_BEGIN(UtilNsTestComposite)
addChild(new ParamTestComposite, "param/serial/");
addChild(new TEST_RUNNER(FormatTest), "format/");
addChild(new SpaceTestComposite, "space/");
addChild(new ArchiveTestComposite, "archives/");
addChild(new ContainersTestComposite, "containers/");
addChild(new MathTestComposite, "math/");
addChild(new AccumulatorTestComposite, "accumulators/unit/");
addChild(new CrystalTestComposite, "crystal/");
addChild(new TEST_RUNNER(RandomTest), "random/");
addChild(new TEST_RUNNER(SignalTest), "signal/");
addChild(new MiscTestComposite, "misc/");
#ifdef UTIL_MPI
//addChild(new MpiParamTestComposite, "param/mpi/");
//addChild(new TEST_RUNNER(MpiSendRecvTest), "mpi/");
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
   
      UtilNsTestComposite runner;
   
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

      std::cerr << "Uncaught exception" << std::endl;
      return EXIT_FAILURE;

   }

}
