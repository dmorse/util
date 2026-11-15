#include "ArchiveTestComposite.h"

int main() 
{
   ArchiveTestComposite runner;
   int failures = runner.run();
   return (failures != 0) ? 1 : 0;
}
