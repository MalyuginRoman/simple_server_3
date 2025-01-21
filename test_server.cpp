#include <iostream>
#include "math.h"
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

class test_server : public CPPUNIT_NS::TestCase
{
CPPUNIT_TEST_SUITE(test_server);
  CPPUNIT_TEST(test1);
CPPUNIT_TEST_SUITE_END();

public:
void setUp(void) {}
void tearDown(void){}

protected:
  void test1(void)
    {
      int CreateSocket = 0,n = 0;
      char dataReceived[1024];
      struct sockaddr_in ipOfServer;
      memset(dataReceived, '0' ,sizeof(dataReceived));
      if((CreateSocket = socket(AF_INET, SOCK_STREAM, 0))< 0)
      {
          printf("Socket not created \n");
      }
      ipOfServer.sin_family = AF_INET;
      ipOfServer.sin_port = htons(2017);
      ipOfServer.sin_addr.s_addr = inet_addr("127.0.0.1");
      if(connect(CreateSocket, (struct sockaddr *)&ipOfServer, sizeof(ipOfServer))<0)
      {
          printf("Connection failed due to port and ip problems\n");
      }
      while((n = read(CreateSocket, dataReceived, sizeof(dataReceived)-1)) > 0)
      {
          dataReceived[n] = 0;
          if(fputs(dataReceived, stdout) == EOF)
          {
              printf("\nStandard output error");
          }
          printf("\n");
      }
      if( n < 0)
      {
          printf("Standard input error \n");
      }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_server);

int main()
{
CPPUNIT_NS::TestResult controller;

CPPUNIT_NS::TestResultCollector result;
controller.addListener(&result);

CPPUNIT_NS::BriefTestProgressListener progress;
controller.addListener(&progress);

CPPUNIT_NS::TestRunner runner;
runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
runner.run(controller);

return result.wasSuccessful() ? 0 : 1;
}
