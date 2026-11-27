#include "ContainersTestComposite.h"
#include <util/misc/initStatic.h>

int main() 
{
   Util::initStatic(); 
   ContainersTestComposite test;
   int failures = test.run();
   return (failures != 0) ? 1 : 0;
}
