
#ifdef UTIL_MPI
#define TEST_MPI
#endif

#include "ArchiveTestComposite.h"

int main(int argc, char** argv) 
{
   #ifdef UTIL_MPI
   MPI_Init(&argc, &argv);
   #endif
   
   ArchiveTestComposite runner;
   runner.run();

   #ifdef UTIL_MPI
   MPI_Finalize();
   #endif
}
