#ifdef UTIL_MPI

#define TEST_MPI
#include <util/global.h>
#include "MpiParamTestComposite.h"

#include <util/space/Vector.h>
#include <util/space/IntVector.h>

int main(int argc, char** argv)
{
   MPI_Init(&argc, &argv);
   Vector::commitMpiType();
   IntVector::commitMpiType();

   MpiParamTestComposite runner;
   runner.run();

   MPI_Finalize();
}
#endif
