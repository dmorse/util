#ifdef UTIL_MPI
#define TEST_MPI
#endif

#include "AccumulatorTestComposite.h"

int main(int argc, char** argv)
{
   #ifdef UTIL_MPI
   MPI_Init(&argc, &argv);
   #endif 

   AccumulatorTestComposite runner;
   runner.run();

   #ifdef UTIL_MPI
   MPI_Finalize();
   #endif
}

