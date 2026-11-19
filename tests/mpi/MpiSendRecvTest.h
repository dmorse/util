#ifndef MPI_SEND_RECV_TEST_H
#define MPI_SEND_RECV_TEST_H

#include <util/global.h>
#include <util/mpi/MpiSendRecv.h>
#include <util/misc/Memory.h>
#include <util/space/Vector.h>
#include <util/space/IntVector.h>

#include <util/containers/FArray.h>
#include <util/containers/Pair.h>

#ifndef TEST_MPI
#define TEST_MPI
#endif

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

#include <iostream>

using namespace Util;

class MpiSendRecvTest : public UnitTest
{

public:

   MpiSendRecvTest()
    : UnitTest()
   {}

   void testSendRecvInt() 
   {
      printMethod(TEST_FUNC);
      int value;
      if (mpiRank() == 1) {
         value = 5;
         send<int>(communicator(), value, 0, 37);
      } else
      if (mpiRank() == 0) {
         value = 0;
         recv<int>(communicator(), value, 1, 37);
         TEST_ASSERT(value == 5);
      }
   }

   void testSendRecvDouble() 
   {
      printMethod(TEST_FUNC);
      double value;
      if (mpiRank() == 1) {
         value = 5.0;
         send<double>(communicator(), value, 0, 37);
      } else
      if (mpiRank() == 0) {
         value = 0;
         recv<double>(communicator(), value, 1, 37);
         TEST_ASSERT(eq(value, 5.0));
      }
   }

   void testSendRecvVector() 
   {
      printMethod(TEST_FUNC);
      Vector value;
      if (mpiRank() == 1) {
         value[0] = 1.0;
         value[1] = 2.1;
         value[2] = 3.0;
         send<Vector>(communicator(), value, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<Vector>(communicator(), value, 1, 37);
         TEST_ASSERT(eq(value[0], 1.0));
         TEST_ASSERT(eq(value[1], 2.1));
         TEST_ASSERT(eq(value[2], 3.0));
      }
   }

   void testSendRecvIntVector() 
   {
      printMethod(TEST_FUNC);
      IntVector value;
      if (mpiRank() == 1) {
         value[0] = -5;
         value[1] = 28;
         value[2] = 3;
         send<IntVector>(communicator(), value, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<IntVector>(communicator(), value, 1, 37);
         TEST_ASSERT(value[0] == -5);
         TEST_ASSERT(value[1] == 28);
         TEST_ASSERT(value[2] == 3);
      }
   }

   void testSendRecvCArrayInt() 
   {
      printMethod(TEST_FUNC);
      int value[3];
      if (mpiRank() == 1) {
         value[0] = 1;
         value[1] = 2;
         value[2] = 3;
         send<int>(communicator(), value, 3, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<int>(communicator(), value, 3, 1, 37);
         TEST_ASSERT(value[0] == 1);
         TEST_ASSERT(value[1] == 2);
         TEST_ASSERT(value[2] == 3);
      }
   }

   void testSendRecv2DCArrayInt() 
   {
      printMethod(TEST_FUNC);
      int value[2][2];
      if (mpiRank() == 1) {
         value[0][0] = 4;
         value[0][1] = 3;
         value[1][0] = 2;
         value[1][1] = 1;
         send<int>(communicator(), value[0], 4, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<int>(communicator(), value[0], 4, 1, 37);
         TEST_ASSERT(value[0][0] == 4);
         TEST_ASSERT(value[0][1] == 3);
         TEST_ASSERT(value[1][0] == 2);
         TEST_ASSERT(value[1][1] == 1);
      }
   }

   void testSendRecvDArrayInt() 
   {
      printMethod(TEST_FUNC);
      DArray<int> value;
      value.allocate(3);
      if (mpiRank() == 1) {
         value[0] = 1;
         value[1] = 2;
         value[2] = 3;
         send<int>(communicator(), value, 3, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<int>(communicator(), value, 3, 1, 37);
         TEST_ASSERT(eq(value[0], 1));
         TEST_ASSERT(eq(value[1], 2));
         TEST_ASSERT(eq(value[2], 3));
      }
   }

   void testSendRecvBool() 
   {
      printMethod(TEST_FUNC);
      bool value;

      if (mpiRank() == 1) {
         value = true;
         send<bool>(communicator(), value, 0, 98);
      } else
      if (mpiRank() == 0) {
         recv<bool>(communicator(), value, 1, 98);
         TEST_ASSERT(value);
      }

      if (mpiRank() == 1) {
         value = false;
         send<bool>(communicator(), value, 0, 98);
      } else
      if (mpiRank() == 0) {
         recv<bool>(communicator(), value, 1, 98);
         TEST_ASSERT(!value);
      }

   }

   void testSendRecvString() 
   {
      printMethod(TEST_FUNC);
      std::string value;
      if (mpiRank() == 1) {
         value = "thingy";
         send<std::string>(communicator(), value, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<std::string>(communicator(), value, 1, 37);
         printEndl();
         std::cout << value << std::endl;
         TEST_ASSERT(!value.compare("thingy"));
      }
   }

   void testSendRecvDArrayBool() 
   {
      printMethod(TEST_FUNC);
      DArray<bool> value;
      value.allocate(3);
      if (mpiRank() == 1) {
         value[0] = false;
         value[1] = true;
         value[2] = true;
         send<bool>(communicator(), value, 3, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<bool>(communicator(), value, 3, 1, 37);
         TEST_ASSERT(!value[0]);
         TEST_ASSERT(value[1]);
         TEST_ASSERT(value[2]);
      }
   }

   void testSendRecvCArrayBool() 
   {
      printMethod(TEST_FUNC);
      bool value[3];
      if (mpiRank() == 1) {
         value[0] = false;
         value[1] = true;
         value[2] = true;
         send<bool>(communicator(), value, 3, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<bool>(communicator(), value, 3, 1, 37);
         TEST_ASSERT(!value[0]);
         TEST_ASSERT(value[1]);
         TEST_ASSERT(value[2]);
      }
   }

   void testSendRecvFArray()
   {
      printMethod(TEST_FUNC);
      typedef FArray<int, 3> Array;
      Array::commitMpiType();
      Array value[2];
      if (mpiRank() == 1) {
         for (int j = 0; j < 2; ++j) {
            for (int i = 0; i < 3; ++i) {
               value[j][i] = 10*j + i;
            }
         }
         send<Array>(communicator(), value, 2, 0, 37);
      } else
      if (mpiRank() == 0) {
         recv<Array>(communicator(), value, 2, 1, 37);
         for (int j = 0; j < 2; ++j) {
            for (int i = 0; i < 3; ++i) {
               TEST_ASSERT(value[j][i] == 10*j + i);
            }
         }
      }
   }

   void testSendRecvPair()
   {
      printMethod(TEST_FUNC);
      Pair<int>::commitMpiType();
      Pair<int> value[2];
      if (mpiRank() == 1) {
         for (int j = 0; j < 2; ++j) {
            value[j][0] = 10*j;
            value[j][1] = 10*j + 1;
         }
         send< Pair<int> >(communicator(), value, 2, 0, 38);
      } else
      if (mpiRank() == 0) {
         recv< Pair<int> >(communicator(), value, 2, 1, 38);
         for (int j = 0; j < 2; ++j) {
            TEST_ASSERT(value[j][0] == 10*j);
            TEST_ASSERT(value[j][1] == 10*j + 1);
         }
      }
   }

   void testBcastFArray()
   {
      printMethod(TEST_FUNC);
      // Capacity larger than the maximum number of builder members
      typedef FArray<double, 25> Array;
      Array::commitMpiType();
      Array value;
      for (int i = 0; i < 25; ++i) {
         value[i] = (mpiRank() == 0) ? 0.5*i : -1.0;
      }
      bcast<Array>(communicator(), value, 0);
      for (int i = 0; i < 25; ++i) {
         TEST_ASSERT(eq(value[i], 0.5*i));
      }
   }

   void testBcastInt() 
   {
      printMethod(TEST_FUNC);
      int value;
      if (mpiRank() == 1) {
         value = 5;
         bcast<int>(communicator(), value, 1);
      } else
      if (mpiRank() != 1) {
         value = 0;
         bcast<int>(communicator(), value, 1);
         TEST_ASSERT(eq(value, 5));
      }
   }

   void testBcastVector() 
   {
      printMethod(TEST_FUNC);
      Vector value;
      if (mpiRank() == 1) {
         value[0] = 1.0;
         value[1] = 2.1;
         value[2] = 3.0;
      } 
      bcast<Vector>(communicator(), value, 1);
      if (mpiRank() != 1) {
         TEST_ASSERT(eq(value[0], 1.0));
         TEST_ASSERT(eq(value[1], 2.1));
         TEST_ASSERT(eq(value[2], 3.0));
      }
   }

   void testBcastIntVector() 
   {
      printMethod(TEST_FUNC);
      IntVector value;
      if (mpiRank() == 1) {
         value[0] = 35;
         value[1] = -29;
         value[2] = 3;
      } 
      bcast<IntVector>(communicator(), value, 1);
      if (mpiRank() != 1) {
         TEST_ASSERT(value[0] == 35);
         TEST_ASSERT(value[1] == -29);
         TEST_ASSERT(value[2] == 3);
      }
   }

   void testBcastCArrayInt() 
   {
      printMethod(TEST_FUNC);
      int value[3];
      if (mpiRank() == 1) {
         value[0] = 1;
         value[1] = 7;
         value[2] = 4;
         bcast<int>(communicator(), value, 3, 1);
         TEST_ASSERT(eq(value[0], 1));
         TEST_ASSERT(eq(value[1], 7));
         TEST_ASSERT(eq(value[2], 4));
      } else
      if (mpiRank() != 1) {
         bcast<int>(communicator(), value, 3, 1);
         TEST_ASSERT(eq(value[0], 1));
         TEST_ASSERT(eq(value[1], 7));
         TEST_ASSERT(eq(value[2], 4));
      }
   }


   void testBcast2DCArrayInt() 
   {
      printMethod(TEST_FUNC);
      int value[2][2];
      if (mpiRank() == 1) {
         value[0][0] = 4;
         value[0][1] = 3;
         value[1][0] = 2;
         value[1][1] = 1;
         bcast<int>(communicator(), value[0], 4, 1);
      } else
      if (mpiRank() != 1) {
         bcast<int>(communicator(), value[0], 4, 1);
         TEST_ASSERT(eq(value[0][0], 4));
         TEST_ASSERT(eq(value[0][1], 3));
         TEST_ASSERT(eq(value[1][0], 2));
         TEST_ASSERT(eq(value[1][1], 1));
      }
   }

   void testBcastDArrayInt() 
   {
      printMethod(TEST_FUNC);
      DArray<int> value;
      value.allocate(3);
      if (mpiRank() == 1) {
         value[0] = 1;
         value[1] = 2;
         value[2] = 3;
         bcast<int>(communicator(), value, 3, 1);
         TEST_ASSERT(eq(value[0], 1));
         TEST_ASSERT(eq(value[1], 2));
         TEST_ASSERT(eq(value[2], 3));
      } else
      if (mpiRank() != 1) {
         bcast<int>(communicator(), value, 3, 1);
         TEST_ASSERT(eq(value[0], 1));
         TEST_ASSERT(eq(value[1], 2));
         TEST_ASSERT(eq(value[2], 3));
      }
   }

   void testBcastBool() 
   {
      printMethod(TEST_FUNC);
      bool value;

      if (mpiRank() == 1) {
         value = true;
         bcast<bool>(communicator(), value, 1);
         TEST_ASSERT(value);
      } else
      if (mpiRank() != 1) {
         value = false;
         TEST_ASSERT(!value);
         bcast<bool>(communicator(), value, 1);
         TEST_ASSERT(value);
      }

      if (mpiRank() == 1) {
         value = false;
         bcast<bool>(communicator(), value, 1);
         TEST_ASSERT(!value);
      } else
      if (mpiRank() != 1) {
         value = true;
         TEST_ASSERT(value);
         bcast<bool>(communicator(), value, 1);
         TEST_ASSERT(!value);
      }

   }

   void testBcastString() 
   {
      printMethod(TEST_FUNC);
      std::string value;
      if (mpiRank() == 1) {
         value = "thingy";
         bcast<std::string>(communicator(), value, 1);
         TEST_ASSERT(!value.compare("thingy"));
      } else
      if (mpiRank() != 1) {
         bcast<std::string>(communicator(), value, 1);
         printEndl();
         std::cout << value << std::endl;
         TEST_ASSERT(!value.compare("thingy"));
      }
   }

   void testBcastDArrayBool() 
   {
      printMethod(TEST_FUNC);
      DArray<bool> value;
      value.allocate(3);
      if (mpiRank() == 1) {
         value[0] = false;
         value[1] = true;
         value[2] = true;
         bcast<bool>(communicator(), value, 3, 1);
      } else
      if (mpiRank() != 1) {
         bcast<bool>(communicator(), value, 3, 1);
         TEST_ASSERT(!value[0]);
         TEST_ASSERT(value[1]);
         TEST_ASSERT(value[2]);
      }
   }

   void testMemoryMax()
   {
      printMethod(TEST_FUNC);

      // Allocate more memory on processors of higher rank
      double* ptr = 0;
      int n = 100000*(mpiRank() + 1);
      Memory::allocate(ptr, n);
      long localMax = Memory::max();
      long globalMax = Memory::max(communicator());
      Memory::deallocate(ptr, n);

      // Maximum of the local maxima, from broadcasts
      long expected = 0;
      for (int rank = 0; rank < communicator().Get_size(); ++rank) {
         long value = localMax;
         bcast<long>(communicator(), value, rank);
         if (value > expected) expected = value;
      }
      TEST_ASSERT(globalMax == expected);
      if (mpiRank() == 0 && communicator().Get_size() > 1) {
         TEST_ASSERT(globalMax > localMax);
      }
   }

};

TEST_BEGIN(MpiSendRecvTest)
TEST_ADD(MpiSendRecvTest, testSendRecvInt)
TEST_ADD(MpiSendRecvTest, testSendRecvDouble)
TEST_ADD(MpiSendRecvTest, testSendRecvVector)
TEST_ADD(MpiSendRecvTest, testSendRecvIntVector)
TEST_ADD(MpiSendRecvTest, testSendRecvCArrayInt)
TEST_ADD(MpiSendRecvTest, testSendRecv2DCArrayInt)
TEST_ADD(MpiSendRecvTest, testSendRecvDArrayInt)
TEST_ADD(MpiSendRecvTest, testSendRecvBool)
TEST_ADD(MpiSendRecvTest, testSendRecvString)
TEST_ADD(MpiSendRecvTest, testSendRecvDArrayBool)
TEST_ADD(MpiSendRecvTest, testSendRecvCArrayBool)
TEST_ADD(MpiSendRecvTest, testSendRecvFArray)
TEST_ADD(MpiSendRecvTest, testSendRecvPair)
TEST_ADD(MpiSendRecvTest, testBcastFArray)
TEST_ADD(MpiSendRecvTest, testBcastInt)
TEST_ADD(MpiSendRecvTest, testBcastVector)
TEST_ADD(MpiSendRecvTest, testBcastIntVector)
TEST_ADD(MpiSendRecvTest, testBcastCArrayInt)
TEST_ADD(MpiSendRecvTest, testBcast2DCArrayInt)
TEST_ADD(MpiSendRecvTest, testBcastDArrayInt)
TEST_ADD(MpiSendRecvTest, testBcastBool)
TEST_ADD(MpiSendRecvTest, testBcastString)
TEST_ADD(MpiSendRecvTest, testBcastDArrayBool)
TEST_ADD(MpiSendRecvTest, testMemoryMax)
TEST_END(MpiSendRecvTest)

#endif
