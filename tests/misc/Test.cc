#ifdef UTIL_MPI
#define TEST_MPI
#endif

#include "MiscTestComposite.h"
#include "ExceptionTest.h"

int main(int argc, char** argv) 
{

   #ifdef UTIL_MPI
   MPI_Init(&argc, &argv);
   #endif

   MiscTestComposite test;
   test.run();

   #ifdef UTIL_MPI
   MPI_Finalize();
   #endif

}
