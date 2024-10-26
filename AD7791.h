/*
  AD7791.h - 
*/
#ifndef AD7791_h
#define AD7791_h
#include <Arduino.h>
#define MODE_WRITE 0x10
#define FILTER_WRITE 0x20
#define STATUS_READ 0x08
#define MODE_READ 0x18
#define FILTER_READ 0x28
#define DATA_READ 0x38
#define RESET 0xFF
#ifndef AD7791_SS
#define AD7791_SS 3
#endif

class AD7791class {
public:
  void writeAd7791(uint8_t ui8address, uint8_t ui8value);
  uint32_t readAd7791(uint8_t ui8address);
  void AD7791_SPI_Configuration(void);
private:
};

extern AD7791class AD7791;

#endif
