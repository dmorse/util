#ifdef UTIL_MPI
#define TEST_MPI
#endif

#include <util/space/Vector.h>
#include <util/space/IntVector.h>
#include "ParamTestComposite.h"

int main() 
{

   #ifdef UTIL_MPI
   MPI::Init();
   Vector::commitMpiType();
   IntVector::commitMpiType();
   #endif

   ParamTestComposite runner;
   runner.run();

   #ifdef UTIL_MPI
   MPI::Finalize();
   #endif


}
