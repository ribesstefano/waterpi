#ifndef WATERPI_ADC_H_
#define WATERPI_ADC_H_

#include "wiringPi.h"
#include "gpio.h"

namespace waterpi {

class Adc {
public:
  Adc(const int cs_gpio_id, const int clk_gpio_id, const int din_gpio_id,
      const int dout_gpio_id);
  ~Adc();

  unsigned char Read();
private:
  void WriteGPIO_Wait(const int gpio_id, const int value);
  void WriteGPIO(const int gpio_id, const int value);

  GPIO_Map pins_;
};

} // waterpi

#endif // end WATERPI_ADC_H_