#include "MathTestComposite.h"
int main()
{
   MathTestComposite runner;
   int failures = runner.run();
   return (failures != 0) ? 1 : 0;
}

