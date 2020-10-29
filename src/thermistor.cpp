#include "thermistor.h"

namespace waterpi {

float getTemp(const int adcVal) {
  // Converts input from a thermistor voltage divider to a temperature value.
  // The voltage divider consists of thermistor Rt and series resistor R0.
  // Reference: https://www.digikey.com/en/maker/projects/how-to-measure-temperature-with-an-ntc-thermistor/4a4b326095f144029df7f2eca589ca54
  const float Beta = 4090; // beta of the thermistor
  const float invBeta = 1 / Beta;
  const float adcMax = 1023.00;
  const float T0 = 24 + 273.15; // room temperature in Kelvin
  const float invT0 = 1.00 / T0;
  const float R0 = 10e3; // resistance of the voltage divider
  const float Vmax = 256; // maximum value from the 8bit ADC
  const float Vt = adcVal; // measured voltage across thermistor
  const float Rt = - R0 * (Vt / Vmax - 1); // resistance of thermistor at room temperature

  return 1 / (invT0 + invBeta * log(Rt / R0)) - 273.15;
}

} // waterpi