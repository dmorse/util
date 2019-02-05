#ifdef UTIL_MPI
#define TEST_MPI
#include "MpiMemoryArchiveTest.h"

int main(int argc, char** argv) 
{
   MPI_Init(&argc, &argv);
   
   TEST_RUNNER(MpiMemoryArchiveTest) test;
   test.run();

   MPI_Finalize();
}
#endif
