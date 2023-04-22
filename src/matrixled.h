#ifndef MATRIXLED_H
#define MATRIXLED_H

#include <stdint.h>

#include "i2c_matrixled_sender.h"

#define MATRIX_WITH 8
#define MATRIX_HEIGHT 8

class Matrixled
{
private:
  I2CMatrixledSender *_sender;
  int _maxDevices;
	
public:
  Matrixled(I2CMatrixledSender *sender, int nbDevice);
  ~Matrixled();

  void displaySprite(uint8_t sprite[], int device);

};

#endif