#include "ExceptionTest.h"
//#include "MiscTestComposite.h"
//#include "ioUtilTest.h"
//#include "SetableTest.h"
//#include "BitTest.h"

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
