#ifndef PARAM_TEST_COMPOSITE_H
#define PARAM_TEST_COMPOSITE_H

#include <test/CompositeTestRunner.h>

#include "LabelTest.h"
#include "BeginEndTest.h"
#include "ParameterTest.h"
#include "ParamCompositeTest.h"
#include "ManagerTest.h"
//#include "TextCompositeTest.h"

TEST_COMPOSITE_BEGIN(ParamTestComposite)
TEST_COMPOSITE_ADD_UNIT(LabelTest);
TEST_COMPOSITE_ADD_UNIT(BeginEndTest);
TEST_COMPOSITE_ADD_UNIT(ParameterTest);
TEST_COMPOSITE_ADD_UNIT(ParamCompositeTest);
TEST_COMPOSITE_ADD_UNIT(ManagerTest);
//#ifndef UTIL_MPI
//TEST_COMPOSITE_ADD_UNIT(TextCompositeTest);
//#endif
TEST_COMPOSITE_END

#endif
