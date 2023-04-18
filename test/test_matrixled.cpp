#include "matrixled.h"
#include "i2c_matrixled_sender.h"

#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>


using namespace CppUnit;
using namespace std;


class Request {
    public:
    int device;
    unsigned char address;
    unsigned char data;
};

class SenderCaptor: public I2CMatrixledSender {
public:

  list<Request> requests; 

  SenderCaptor() {
  }

  ~SenderCaptor() {

  }

  void sendToDevice(int device, uint8_t address, uint8_t data) {
    Request req;
    req.device = device;
    req.address = address;
    req.data = data;
    requests.push_back(
        req
    );
  } 

};

class TestMatrixled : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestMatrixled);
    CPPUNIT_TEST(testSendCommandWhenSubmit);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testSendCommandWhenSubmit(void);

private:
    SenderCaptor *senderCaptor;
    Matrixled *mTestObj;
};

void
TestMatrixled::testSendCommandWhenSubmit(void)
{   
    uint8_t sprite[] = {0x11};

    mTestObj->displaySprite(sprite, 1);
    
    int nbrequest = senderCaptor->requests.size();
    
    CPPUNIT_ASSERT_MESSAGE(message_to_string("Expected 1 but obtain " + nbrequest) ,nbrequest == 1);
}



void TestMatrixled::setUp(void)
{
    senderCaptor = new SenderCaptor();
    mTestObj = new Matrixled(senderCaptor, 1);
}

void TestMatrixled::tearDown(void)
{
    delete senderCaptor;
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestMatrixled );

int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("cppTestBasicMathResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}