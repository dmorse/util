#include "AccumulatorTestComposite.h"

int main()
{
   AccumulatorTestComposite runner;
   int failures = runner.run();
   return (failures != 0) ? 1 : 0;
}

