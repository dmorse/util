#ifdef UTIL_MPI

#define TEST_MPI
#include <util/global.h>
#include "MpiParamTestComposite.h"

#include <util/space/Vector.h>
#include <util/space/IntVector.h>

int main()
{
   MPI_Init();
   Vector::commitMpiType();
   IntVector::commitMpiType();

   MpiParamTestComposite runner;
   runner.run();

   MPI_Finalize();
}
#endif
