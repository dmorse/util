#ifndef REFERENCE_COUNT_TEST_H
#define REFERENCE_COUNT_TEST_H

#include <util/misc/ReferenceCounter.h>
#include <util/misc/CountedReference.h>
#include <util/global.h>

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

using namespace Util;

class ReferenceCountTest : public UnitTest 
{

public:

   void setUp()
   { };

   void tearDown()
   {};

   void testCount() 
   {
      printMethod(TEST_FUNC);

      ReferenceCounter counter;
      CountedReference ref1;
      CountedReference ref2;

      TEST_ASSERT(0 == counter.nRef());
      TEST_ASSERT(!counter.hasRefs());
      TEST_ASSERT(!ref1.isAssociated());
      TEST_ASSERT(!ref2.isAssociated());

      ref1.associate(counter);
      TEST_ASSERT(1 == counter.nRef());
      TEST_ASSERT(counter.hasRefs());
      TEST_ASSERT(ref1.isAssociated());
      TEST_ASSERT(!ref2.isAssociated());

      ref1.dissociate();
      TEST_ASSERT(0 == counter.nRef());
      TEST_ASSERT(!counter.hasRefs());
      TEST_ASSERT(!ref1.isAssociated());
      TEST_ASSERT(!ref2.isAssociated());

      ref2.associate(counter);
      TEST_ASSERT(1 == counter.nRef());
      TEST_ASSERT(counter.hasRefs());
      TEST_ASSERT(!ref1.isAssociated());
      TEST_ASSERT(ref2.isAssociated());

      ref1.associate(counter);
      TEST_ASSERT(2 == counter.nRef());
      TEST_ASSERT(counter.hasRefs());
      TEST_ASSERT(ref1.isAssociated());
      TEST_ASSERT(ref2.isAssociated());

      ref2.dissociate();
      TEST_ASSERT(1 == counter.nRef());
      TEST_ASSERT(counter.hasRefs());
      TEST_ASSERT(ref1.isAssociated());
      TEST_ASSERT(!ref2.isAssociated());

      ref1.dissociate();
      TEST_ASSERT(0 == counter.nRef());
      TEST_ASSERT(!counter.hasRefs());
      TEST_ASSERT(!ref1.isAssociated());
      TEST_ASSERT(!ref2.isAssociated());

      ref2.associate(counter);
      TEST_ASSERT(1 == counter.nRef());
      TEST_ASSERT(counter.hasRefs());
      TEST_ASSERT(!ref1.isAssociated());
      TEST_ASSERT(ref2.isAssociated());

   }

};

TEST_BEGIN(ReferenceCountTest)
TEST_ADD(ReferenceCountTest, testCount)
TEST_END(ReferenceCountTest)

#endif
