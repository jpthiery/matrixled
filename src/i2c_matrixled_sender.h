#ifndef I2C_MATRIXLED_SENDER
#define I2C_MATRIXLED_SENDER

#include "matrixled_sender.h"

class I2CMatrixLedSender: public MatrixledSender {

public:
  I2CMatrixLedSender(int dataPin, int clockPin, int loadPin);
  ~I2CMatrixLedSender();
  
  void sendToDevice(int device, uint8_t address, uint8_t data); 
 private:
  int _dataPin;
  int _clockPin;
  int _loadPin;
};

#endif