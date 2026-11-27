#include "FormatTest.h"

int main() 
{
   TEST_RUNNER(FormatTest) test;
   int failures = test.run();
   return (failures != 0) ? 1 : 0;
}
