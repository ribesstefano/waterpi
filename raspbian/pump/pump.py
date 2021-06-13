from gpiozero import OutputDevice
import time

class Pump(OutputDevice):
    """docstring for Pump"""
    def __init__(self, pin):
        super(Pump, self).__init__(pin, active_high=False)

    def run(self, seconds=1):
        self.on()
        time.sleep(1)
        self.off()

def main():
    pin = 'GPIO17'
    pump = Pump(pin)
    pump.run(1)
    time.sleep(1)


if __name__ == '__main__':
    main()