#include "SpaceTestComposite.h"
int main()
{
   SpaceTestComposite runner;
   int failures = runner.run();
   return (failures != 0) ? 1 : 0;
}

