#include "ContainersTestComposite.h"
#include <util/misc/initStatic.h>

#ifdef UTIL_MPI
#define TEST_MPI
#endif

int main(int argc, char** argv) 
{
   #ifdef UTIL_MPI
   MPI_Init(&argc, &argv);
   #endif 

   Util::initStatic(); 
   ContainersTestComposite test;
   test.run();

   #ifdef UTIL_MPI
   MPI_Finalize();
   #endif 
}
