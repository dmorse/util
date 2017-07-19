#ifndef MATH_TEST_COMPOSITE_H
#define MATH_TEST_COMPOSITE_H

#include <test/CompositeTestRunner.h>

#include "GcdTest.h"
#include "RationalTest.h"
#include "BinomialTest.h"
#include "PolynomialTest.h"
#include "BSplineBasisTest.h"

TEST_COMPOSITE_BEGIN(MathTestComposite)
TEST_COMPOSITE_ADD_UNIT(GcdTest);
TEST_COMPOSITE_ADD_UNIT(RationalTest);
TEST_COMPOSITE_ADD_UNIT(BinomialTest);
TEST_COMPOSITE_ADD_UNIT(PolynomialTest);
TEST_COMPOSITE_ADD_UNIT(BSplineBasisTest);
TEST_COMPOSITE_END

#endif
