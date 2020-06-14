#include <cstdio>
#include <iostream>
#include "waterpi.h"

#define ADC_CS 0
#define ADC_CLK 1
#define ADC_DIO 2
#define LedPin 3

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