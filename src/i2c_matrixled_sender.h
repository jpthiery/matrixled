#ifndef I2C_MATRIXLED_SENDER
#define I2C_MATRIXLED_SENDER

#include <stdint.h>

class I2CMatrixledSender {
  public:
    virtual void sendToDevice(int device, uint8_t address, uint8_t data) = 0; 
};

#endif