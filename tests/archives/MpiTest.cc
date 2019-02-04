#ifdef UTIL_MPI
#define TEST_MPI
#include "MpiMemoryArchiveTest.h"

int main() 
{
   MPI_Init();
   
   TEST_RUNNER(MpiMemoryArchiveTest) test;
   test.run();

   MPI_Finalize();
}
#endif
