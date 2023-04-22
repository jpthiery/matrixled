#ifndef I2C_MATRIXLED_SENDER_H
#define I2C_MATRIXLED_SENDER_H

#include "i2c_matrixled_sender.h"

#include <stdint.h>

#include <iostream>

#ifdef __AVR__
#include "Arduino.h"
#else
#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

#define LSBFIRST 0
#define MSBFIRST 1

void pinMode(int id, int mode) {
  printf("pinMode(%d, %d)\n", id, mode);
}
void digitalWrite(int id, int mode) {
  printf("digitalWrite(%d, %d)\n", id, mode);
}
void shiftOut(int loadPin,int clockPin,int mode,uint8_t data){
  printf("shiftOut(%d, %d, %d)\n", loadPin, mode, data);
}
#endif

I2CMatrixLedSender::I2CMatrixLedSender(int dataPin, int clockPin, int loadPin) {
  _dataPin = dataPin;
  _clockPin = clockPin;
  _loadPin = loadPin;

  pinMode(_dataPin,OUTPUT);
  pinMode(_clockPin,OUTPUT);
  pinMode(_loadPin,OUTPUT);
};

I2CMatrixLedSender::~I2CMatrixLedSender() {

};

void I2CMatrixLedSender::sendToDevice(int device, uint8_t address, uint8_t data) {
  printf("Sending on address %d data: %d\n", address, data);
  digitalWrite(_loadPin,LOW);
  shiftOut(_dataPin,_clockPin,MSBFIRST,address);
  shiftOut(_dataPin,_clockPin,MSBFIRST,data);
  digitalWrite(_loadPin,HIGH);
}


#endif
