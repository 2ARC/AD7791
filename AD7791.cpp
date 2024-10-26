/*
  AD7791.cpp - 
*/
#include <Arduino.h>
#include <SPI.h>
#include <SoftSPIB.h>
SoftSPIB mySPI(4 /* MOSI */, 5 /* MISO */, 2 /* SCK */);
#include "AD7791.h"
AD7791class AD7791;

void AD7791class::AD7791_SPI_Configuration(void) {
  mySPI.begin();
  mySPI.setBitOrder(MSBFIRST);
  mySPI.setDataMode(SPI_MODE3);
  mySPI.setClockDivider(128);
  delay(100);
}

uint32_t AD7791class::readAd7791(uint8_t ui8address) {
  uint8_t ui8AdcUpperCodes = 0;
  uint8_t ui8AdcMiddleCodes = 0;
  uint8_t ui8AdcLowerCodes = 0;
  uint32_t ui32AdcCodes = 0;
  if (ui8address == DATA_READ) {
    digitalWrite(AD7791_SS, LOW);
    mySPI.transfer(ui8address);
    ui8AdcUpperCodes = mySPI.transfer(0x00);
    ui8AdcMiddleCodes = mySPI.transfer(0x00);
    ui8AdcLowerCodes = mySPI.transfer(0x00);
    digitalWrite(AD7791_SS, HIGH);
    ui32AdcCodes = ((long)ui8AdcUpperCodes << 16) | ((long)ui8AdcMiddleCodes << 8) | ui8AdcLowerCodes;
  } else {
    digitalWrite(AD7791_SS, LOW);
    mySPI.transfer(ui8address);
    ui8AdcLowerCodes = mySPI.transfer(0x00);
    digitalWrite(AD7791_SS, HIGH);
    ui32AdcCodes = ((long)ui8AdcUpperCodes << 16) | ((long)ui8AdcMiddleCodes << 8) | ui8AdcLowerCodes;
  }
  return ui32AdcCodes;
}

void AD7791class::writeAd7791(uint8_t ui8address, uint8_t ui8value) {
  if (ui8address != RESET) {
    digitalWrite(AD7791_SS, LOW);
    mySPI.transfer(ui8address);
    mySPI.transfer(ui8value);
    digitalWrite(AD7791_SS, HIGH);
  } else {
    digitalWrite(AD7791_SS, LOW);
    mySPI.transfer(ui8value);
    mySPI.transfer(ui8value);
    mySPI.transfer(ui8value);
    mySPI.transfer(ui8value);
    digitalWrite(AD7791_SS, HIGH);
  }
}