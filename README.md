# WaterPi


## TODO

* The ADC returns a value of zero if there was an error in reading. This might cause problems with sensors calibrated to have zero output!

## Compiler flags

```C++
g++ thermistor.c -lwiringPi -lpthread -lm -lcrypt -lrt -o thermistor.exe ; ./thermistor.exe
```

## Milestones

What follows is a list of achievements and future steps:
* ~~Create a CMake project~~
* ~~Installed WiringPi and made it work~~
* ~~Read an external ADC output through I2C~~
* ~~Able to read serial output from the Arduino (the Arduino needs external power supply)~~
