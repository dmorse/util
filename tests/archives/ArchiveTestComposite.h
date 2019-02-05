#ifndef ARCHIVE_TEST_COMPOSITE_H
#define ARCHIVE_TEST_COMPOSITE_H

#ifdef UTIL_MPI
#ifndef TEST_MPI
#define TEST_MPI
#endif
#endif

#include "MemoryArchiveTest.h"
#include "BinaryFileArchiveTest.h"
#include "TextFileArchiveTest.h"
#include "XdrFileArchiveTest.h"
#ifdef UTIL_MPI
#include "MpiMemoryArchiveTest.h"
#endif

#include <test/CompositeTestRunner.h>

TEST_COMPOSITE_BEGIN(ArchiveTestComposite)
TEST_COMPOSITE_ADD_UNIT(MemoryArchiveTest);
TEST_COMPOSITE_ADD_UNIT(BinaryFileArchiveTest);
TEST_COMPOSITE_ADD_UNIT(TextFileArchiveTest);
TEST_COMPOSITE_ADD_UNIT(XdrFileArchiveTest);
#ifdef UTIL_MPI
TEST_COMPOSITE_ADD_UNIT(MpiMemoryArchiveTest);
#endif
TEST_COMPOSITE_END

#endif
