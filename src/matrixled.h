#ifndef MATRIXLED_H
#define MATRIXLED_H

#include <stdint.h>

#include "matrixled_sender.h"

#define MATRIX_WITH 8
#define MATRIX_HEIGHT 8

class Matrixled
{
private:
  MatrixledSender *_sender;
  int _maxDevices;
	
public:
  Matrixled(MatrixledSender *sender, int nbDevice);
  ~Matrixled();

  void displaySprite(uint8_t sprite[], int device);

};

#endif