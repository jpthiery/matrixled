#ifndef MATRIXLED_SENDER
#define MATRIXLED_SENDER

#include <stdint.h>

class MatrixledSender {
  public:
    virtual void sendToDevice(int device, uint8_t address, uint8_t data) = 0; 
};

#endif