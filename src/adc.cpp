#include "adc.h"

namespace waterpi {

Adc::Adc(const int cs_gpio_id, const int clk_gpio_id, const int din_gpio_id,
    const int dout_gpio_id) {
  pins_["cs"] = cs_gpio_id;
  pins_["clk"] = clk_gpio_id;
  pins_["din"] = din_gpio_id;
  pins_["dout"] = dout_gpio_id;
  pinMode(pins_["dout"], OUTPUT);
  if (pins_["din"] != pins_["dout"]) {
    pinMode(pins_["din"], INPUT);
  }
}

Adc::~Adc() {}

unsigned char Adc::Read() {
  unsigned char i;
  unsigned char read_dat_1 = 0, read_dat_2 = 0;
  WriteGPIO(pins_["cs"], 0);
  WriteGPIO(pins_["clk"], 0);
  WriteGPIO_Wait(pins_["dout"], 1); // start bit
  WriteGPIO_Wait(pins_["clk"], 1);
  WriteGPIO(pins_["clk"], 0);
  WriteGPIO_Wait(pins_["dout"], 1);
  WriteGPIO_Wait(pins_["clk"], 1); // sgl/not dif
  WriteGPIO(pins_["clk"], 0);
  WriteGPIO_Wait(pins_["dout"], 0); // odd/sign
  WriteGPIO(pins_["clk"], 1);  
  WriteGPIO_Wait(pins_["dout"], 1); // select bit1
  WriteGPIO(pins_["clk"], 0);  
  WriteGPIO_Wait(pins_["dout"], 1); // select bit0
  if (pins_["din"] == pins_["dout"]) {
    pinMode(pins_["din"], INPUT);
  }
  for (int i = 0; i < 8; ++i) {
    WriteGPIO_Wait(pins_["clk"], 1);
    WriteGPIO_Wait(pins_["clk"], 0);
    read_dat_1 = (read_dat_1 << 1) | digitalRead(pins_["din"]);
  }
  for (i = 0; i < 8; ++i) {
    read_dat_2 = read_dat_2 | ((unsigned char)(digitalRead(pins_["din"])) << i);
    WriteGPIO_Wait(pins_["clk"], 1);
    WriteGPIO_Wait(pins_["clk"], 0);
  }
  WriteGPIO(pins_["cs"], 1);
  if (pins_["din"] == pins_["dout"]) {
    pinMode(pins_["din"], OUTPUT);
  }
  // printf("0x%x | 0x%x\n", read_dat_1, read_dat_2);
  // printf("b"BYTE_TO_BINARY_PATTERN" | ", BYTE_TO_BINARY(read_dat_1));
  // printf("b"BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(read_dat_2));
  // NOTE: We return a value stable for two readings.
  return (read_dat_1 == read_dat_2) ? read_dat_1 : 0;
}

void Adc::WriteGPIO_Wait(const int gpio_id, const int value) {
  digitalWrite(gpio_id, value);
  delayMicroseconds(2);
}

void Adc::WriteGPIO(const int gpio_id, const int value) {
  digitalWrite(gpio_id, value);
}

} // waterpi