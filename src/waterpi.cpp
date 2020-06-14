#include <cstdio>
#include <iostream>
#include <cmath>
#include "waterpi.h"

#define ADC_CS 0
#define ADC_CLK 1
#define ADC_DIO 2
#define LedPin 3

float getTemp(int adcVal) {
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

int main(int argc, char const *argv[]) {
  int kUseBCM_GPIO = 1;

  if (kUseBCM_GPIO) {
    if (wiringPiSetupGpio() == -1) {
      printf("setup wiringPi failed !");
      return 1; 
    }
  } else {
    if (wiringPiSetup() == -1) {
      printf("setup wiringPi failed !");
      return 1; 
    }
  }
  piHiPri(99);

  pinMode(LedPin, OUTPUT);
  pinMode(ADC_CS,  OUTPUT);
  pinMode(ADC_CLK, OUTPUT);

  Adc adc(ADC_CS, ADC_CLK, ADC_DIO, ADC_DIO);

  while (1) {
    auto adcVal = adc.Read();

    float temperature = getTemp(adcVal);
    std::cout << "Temperature = " << temperature << "^C\n";
    delay(500 * 2);
  }

  return 0;
}