#ifndef MANAGER_TEST_H
#define MANAGER_TEST_H

#include <util/param/ParamComposite.h>
#include <util/param/Manager.h>
#include <util/param/Factory.h>

#include <test/UnitTest.h>
#include <test/UnitTestRunner.h>

using namespace Util;

#include "../ParamTestClasses.h"

class ManagerTest : public UnitTest 
{

public:

   void testFactory() 
   {
      printMethod(TEST_FUNC);

      AFactory    factory;
      A*          ptr;
      std::string name("B");

      ptr = factory.factory(name);
      TEST_ASSERT(ptr->className() == name);
 
      printEndl();
      std::cout <<  "Classname = " << ptr->className() << std::endl;

   }

   void testCustomFactory() 
   {
      printMethod(TEST_FUNC);

      CustomAFactory factory;
      A*             ptr;
      std::string name("D");

      ptr = factory.factory(name);
      TEST_ASSERT(ptr != 0);
      TEST_ASSERT(ptr->className() == name);
 
      printEndl();
      std::cout <<  "Classname = " << ptr->className() << std::endl;

   }

   void testManager() 
   {
      printMethod(TEST_FUNC);
      AManager manager;
      std::ifstream in;
      openInputFile("in/Manager", in);
      manager.readParam(in);

      printEndl();
      manager.writeParam(std::cout);

   }

   void testFindFirst() 
   {
      printMethod(TEST_FUNC);
      AManager manager;
      std::ifstream in;
      openInputFile("in/Manager", in);
      manager.readParam(in);

      A* ptr = 0;
      ptr = manager.findFirst("C");
      TEST_ASSERT(ptr != 0);
      TEST_ASSERT(ptr->className() == "C");
      printEndl();
      ptr->writeParam(std::cout);

      ptr = manager.findFirst("B");
      TEST_ASSERT(ptr != 0);
      TEST_ASSERT(ptr->className() == "B");
      ptr->writeParam(std::cout);
   }

   void testManagerSubfactory() 
   {
      printMethod(TEST_FUNC);
      AManager manager;
      std::ifstream in;
      openInputFile("in/CustomManager", in);

      CustomAFactory factory;
      manager.addSubfactory(factory);
      manager.readParam(in);

      printEndl();
      manager.writeParam(std::cout);

   }

   void testManagerUnique1() 
   {
      printMethod(TEST_FUNC);
      printEndl();

      AManagerUnique manager;
      std::ifstream in;
      openInputFile("in/Manager", in);
      bool success = false;
      try {
         manager.readParam(in);
      } catch (Exception) {
         success = true;
         std::cout << "Caught expected Exception" << std::endl;
      }
      TEST_ASSERT(success);
   }

   void testManagerUnique2() 
   {
      printMethod(TEST_FUNC);

      AManagerUnique manager;
      std::ifstream in;
      openInputFile("in/ManagerUnique", in);
      bool success = true;
      try {
         manager.readParam(in);
      } catch (Exception) {
         success = false;
      }
      TEST_ASSERT(success);
   }

};

TEST_BEGIN(ManagerTest)
TEST_ADD(ManagerTest, testFactory)
TEST_ADD(ManagerTest, testCustomFactory)
TEST_ADD(ManagerTest, testManager)
TEST_ADD(ManagerTest, testFindFirst)
TEST_ADD(ManagerTest, testManagerSubfactory)
TEST_ADD(ManagerTest, testManagerUnique1)
TEST_ADD(ManagerTest, testManagerUnique2)
TEST_END(ManagerTest)

#endif
