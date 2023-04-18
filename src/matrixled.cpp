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

void Matrixled::displaySprite(uint8_t* sprite, int device) {
  
  uint8_t address = 0x01;
  uint8_t data = 0x01;
  _sender->sendToDevice(device, address, data);
}