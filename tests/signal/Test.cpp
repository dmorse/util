#include "MethodFunctorTest.h"
#include "SignalTest.h"

int main() 
{

   #ifdef UTIL_MPI
   MPI::Init();
   #endif

   TEST_RUNNER(MethodFunctorTest) test1;
   int failures = test1.run();

   TEST_RUNNER(SignalTest) test2;
   failures += test2.run();

   #ifdef UTIL_MPI
   MPI::Finalize();
   #endif

   return (failures != 0) ? 1 : 0;
}
