#include "RandomTest.h"
int main()
{
   TEST_RUNNER(RandomTest) runner;
   int failures = runner.run();
   return (failures != 0) ? 1 : 0;
}

