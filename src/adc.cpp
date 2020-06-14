#include "adc.h"

unsigned char Adc::Read() {
  unsigned char i;
  unsigned char read_dat_1 = 0, read_dat_2 = 0;
  WriteGPIO(pins["cs"], 0);
  WriteGPIO(pins["clk"], 0);
  WriteGPIO_Wait(pins["dout"], 1); // start bit
  WriteGPIO_Wait(pins["clk"], 1);
  WriteGPIO(pins["clk"], 0);
  WriteGPIO_Wait(pins["dout"], 1);
  WriteGPIO_Wait(pins["clk"], 1); // sgl/not dif
  WriteGPIO(pins["clk"], 0);
  WriteGPIO_Wait(pins["dout"], 0); // odd/sign
  WriteGPIO(pins["clk"], 1);  
  WriteGPIO_Wait(pins["dout"], 1); // select bit1
  WriteGPIO(pins["clk"], 0);  
  WriteGPIO_Wait(pins["dout"], 1); // select bit0
  if (pins["din"] == pins["dout"]) {
    pinMode(pins["din"], INPUT);
  }
  for (int i = 0; i < 8; ++i) {
    WriteGPIO_Wait(pins["clk"], 1);
    WriteGPIO_Wait(pins["clk"], 0);
    read_dat_1 = (read_dat_1 << 1) | digitalRead(pins["din"]);
  }
  for (i = 0; i < 8; ++i) {
    read_dat_2 = read_dat_2 | ((unsigned char)(digitalRead(pins["din"])) << i);
    WriteGPIO_Wait(pins["clk"], 1);
    WriteGPIO_Wait(pins["clk"], 0);
  }
  WriteGPIO(pins["cs"], 1);
  if (pins["din"] == pins["dout"]) {
    pinMode(pins["din"], OUTPUT);
  }
  // printf("0x%x | 0x%x\n", read_dat_1, read_dat_2);
  // printf("b"BYTE_TO_BINARY_PATTERN" | ", BYTE_TO_BINARY(read_dat_1));
  // printf("b"BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(read_dat_2));
  return (read_dat_1 == read_dat_2) ? read_dat_1 : 0; // we return a value stable for two readings
}

void Adc::WriteGPIO_Wait(const int gpio_id, const int value) {
  digitalWrite(gpio_id, value);
  delayMicroseconds(2);
}

void Adc::WriteGPIO(const int gpio_id, const int value) {
  digitalWrite(gpio_id, value);
}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}