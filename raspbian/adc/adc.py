import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

import time

class ADC(object):
    """docstring for ADC"""
    def __init__(self):
        i2c = busio.I2C(board.SCL, board.SDA)
        ads = ADS.ADS1115(i2c)
        self.channels = {}
        self.channels[0] = AnalogIn(ads, ADS.P0)
        self.channels[1] = AnalogIn(ads, ADS.P1)
        self.channels[2] = AnalogIn(ads, ADS.P2)
        self.channels[3] = AnalogIn(ads, ADS.P3)
    
    def read_value(self, channel=0):
        return self.channels[channel].value

    def read_voltage(self, channel=0):
        return self.channels[channel].voltage


def main():

    adc = ADC()
    print('sensor - value/voltage: {} / {}'.format(adc.read_value(), adc.read_voltage()))

    # i2c = busio.I2C(board.SCL, board.SDA)
    # ads = ADS.ADS1115(i2c)
    # chan = AnalogIn(ads, ADS.P1)

    # while(1):
    #     print('wet sensor - value/voltage: {} / {}'.format(chan.value, chan.voltage))
    #     time.sleep(3)

    # for _ in range(100):
    #     print('dry sensor - value/voltage: {} / {}'.format(chan.value, chan.voltage))
    #     time.sleep(0.1)


if __name__ == '__main__':
    main()