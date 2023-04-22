#include "matrixled.h"
#include <stdint.h>

Matrixled::Matrixled(I2CMatrixledSender *sender, int nbDevice)
{
  _sender = sender;
  _maxDevices = nbDevice;
}

Matrixled::~Matrixled()
{

}

void Matrixled::displaySprite(uint8_t sprite[], int device) {
  
  for (int row=0; row < MATRIX_HEIGHT; row++) {
    uint8_t line = sprite[row]; 
    _sender->sendToDevice(device, row+1, line);
  }
  
}