#ifndef WATERPI_ADC_H_
#define WATERPI_ADC_H_

#include <cstring>
#include <map>

#include "gpio.h"

typedef std::map<std::string, int> GPIO_Map;

class Adc {
public:
  Adc(const int cs_gpio_id, const int clk_gpio_id, const int din_gpio_id,
      const int dout_gpio_id) {
    pins["cs"] = cs_gpio_id;
    pins["clk"] = clk_gpio_id;
    pins["din"] = din_gpio_id;
    pins["dout"] = dout_gpio_id;
    pinMode(pins["dout"], OUTPUT);
    if (pins["din"] != pins["dout"]) {
      pinMode(pins["din"], INPUT);
    }
  }
  ~Adc();

  unsigned char Read();
private:
  void WriteGPIO_Wait(const int gpio_id, const int value);
  void WriteGPIO(const int gpio_id, const int value);

  GPIO_Map pins;
};


#endif // end WATERPI_ADC_H_