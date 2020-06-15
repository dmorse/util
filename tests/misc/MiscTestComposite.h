#ifndef MISC_TEST_COMPOSITE_H
#define MISC_TEST_COMPOSITE_H

#include <test/CompositeTestRunner.h>

#include "ExceptionTest.h"
#include "SetableTest.h"
#include "BitTest.h"
#include "FlagSetTest.h"
#include "ioUtilTest.h"
#include "XmlTest.h"
#include "MemoryTest.h"
#include "TimerTest.h"

TEST_COMPOSITE_BEGIN(MiscTestComposite)
#ifndef UTIL_MPI
TEST_COMPOSITE_ADD_UNIT(ExceptionTest);
TEST_COMPOSITE_ADD_UNIT(FlagSetTest);
#endif
TEST_COMPOSITE_ADD_UNIT(SetableTest);
TEST_COMPOSITE_ADD_UNIT(BitTest);
TEST_COMPOSITE_ADD_UNIT(ioUtilTest);
TEST_COMPOSITE_ADD_UNIT(XmlTest);
TEST_COMPOSITE_ADD_UNIT(MemoryTest);
TEST_COMPOSITE_ADD_UNIT(TimerTest);
TEST_COMPOSITE_END

#endif
