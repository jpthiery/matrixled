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
    CPPUNIT_TEST(testSendPixelOnTopRightCorner);
    CPPUNIT_TEST(testSendPixelOnTopLeftCorner);
    CPPUNIT_TEST(testSendPixelOnTopLine);
    CPPUNIT_TEST(testSendPixelOnSecondLine);
    CPPUNIT_TEST(testSendPixelOnLeftColumn);
    CPPUNIT_TEST(testSendSpriteInvaders);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp(void);
    void tearDown(void);

protected:
    void testSendPixelOnTopRightCorner(void);
    void testSendPixelOnTopLeftCorner(void);
    void testSendPixelOnTopLine(void);
    void testSendPixelOnSecondLine(void);
    void testSendPixelOnLeftColumn(void);
    void testSendSpriteInvaders(void);

private:
    SenderCaptor *senderCaptor;
    Matrixled *mTestObj;
    void assertSprite(char expectedSprite[8][8]);
};

void TestMatrixled::assertSprite(char expectedSprite[8][8]) {
    uint8_t expectedRow[8];
    for(int row=0; row<8; row++) {
        uint8_t current = expectedRow[row];
        for (int colomn=0; colomn<8; colomn++) { 
            current = current << 1;
            char expectedLedState = expectedSprite[row][colomn];
            if (expectedLedState == 'X') {
              current = current ^ 0x01;
            }
        }
        expectedRow[row] = current;
    }

    list<Request> requests = senderCaptor->requests;
    list<Request>::iterator reqIterator = requests.begin();
    int i = 0;
    for (std::list<Request>::iterator req = requests.begin(); req != requests.end(); ++req){
#ifdef TEST_DEBUG        
        printf("\n");
        printf("Req[%d] address %d, device %d, data %d\n", i, req->address, req->device, req->data);
        printf("actual %d\n" ,req->data);
        printf("expceted %d\n", expectedRow[i]);
#endif
        CPPUNIT_ASSERT(req->address == i+1);
        CPPUNIT_ASSERT(req->data == expectedRow[i]);
        i++;
    }
    CPPUNIT_ASSERT(i==8);
}

void TestMatrixled::testSendPixelOnTopLeftCorner(void) {

    uint8_t sprite[8] = {
        0x80,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    char expectedSprite[8][8] = {
        {'X','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'}
    };

    mTestObj->displaySprite(sprite, 1);
    int nbrequest = senderCaptor->requests.size();
    CPPUNIT_ASSERT(nbrequest == 8);

    assertSprite(expectedSprite);

}

void TestMatrixled::testSendPixelOnTopRightCorner(void) {

    uint8_t sprite[8] = {
        0x01,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    char expectedSprite[8][8] = {
        {'_', '_','_','_','_','_','_','X'},
        {'_', '_','_','_','_','_','_','_'},
        {'_', '_','_','_','_','_','_','_'},
        {'_', '_','_','_','_','_','_','_'},
        {'_', '_','_','_','_','_','_','_'},
        {'_', '_','_','_','_','_','_','_'},
        {'_', '_','_','_','_','_','_','_'},
        {'_', '_','_','_','_','_','_','_'}
    };

    mTestObj->displaySprite(sprite, 1);
    int nbrequest = senderCaptor->requests.size();
    CPPUNIT_ASSERT(nbrequest == 8);

    assertSprite(expectedSprite);

}

void TestMatrixled::testSendPixelOnTopLine(void) {

    uint8_t sprite[8] = {
        0xff,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    char expectedSprite[8][8] = {
        {'X','X','X','X','X','X','X','X'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'}
    };

    mTestObj->displaySprite(sprite, 1);
    int nbrequest = senderCaptor->requests.size();
    CPPUNIT_ASSERT(nbrequest == 8);

    assertSprite(expectedSprite);

}

void TestMatrixled::testSendPixelOnSecondLine(void) {

    uint8_t sprite[8] = {
        0x00,
        0xff,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    char expectedSprite[8][8] = {
        {'_','_','_','_','_','_','_','_'},
        {'X','X','X','X','X','X','X','X'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'},
        {'_','_','_','_','_','_','_','_'}
    };

    mTestObj->displaySprite(sprite, 1);
    int nbrequest = senderCaptor->requests.size();
    CPPUNIT_ASSERT(nbrequest == 8);

    assertSprite(expectedSprite);

}

void TestMatrixled::testSendPixelOnLeftColumn(void) {

    uint8_t sprite[8] = {
        0x80,
        0x80,
        0x80,
        0x80,
        0x80,
        0x80,
        0x80,
        0x80
    };

    char expectedSprite[8][8] = {
        {'X','_','_','_','_','_','_','_'},
        {'X','_','_','_','_','_','_','_'},
        {'X','_','_','_','_','_','_','_'},
        {'X','_','_','_','_','_','_','_'},
        {'X','_','_','_','_','_','_','_'},
        {'X','_','_','_','_','_','_','_'},
        {'X','_','_','_','_','_','_','_'},
        {'X','_','_','_','_','_','_','_'}
    };

    mTestObj->displaySprite(sprite, 1);
    int nbrequest = senderCaptor->requests.size();
    CPPUNIT_ASSERT(nbrequest == 8);

    assertSprite(expectedSprite);

}

void TestMatrixled::testSendSpriteInvaders(void) {

    uint8_t sprite[8] = {
        0x18,
        0x3c,
        0x7e,
        0xdb,
        0xff,
        0x24,
        0x5a,
        0x42
    };

    char expectedSprite[8][8] = {
        {'_','_','_','X','X','_','_','_'},
        {'_','_','X','X','X','X','_','_'},
        {'_','X','X','X','X','X','X','_'},
        {'X','X','_','X','X','_','X','X'},
        {'X','X','X','X','X','X','X','X'},
        {'_','_','X','_','_','X','_','_'},
        {'_','X','_','X','X','_','X','_'},
        {'_','X','_','_','_','_','X','_'}
    };

    mTestObj->displaySprite(sprite, 1);
    int nbrequest = senderCaptor->requests.size();
    CPPUNIT_ASSERT(nbrequest == 8);

    assertSprite(expectedSprite);

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