import time
from picamera import PiCamera


def main():
    camera = PiCamera()
    camera.resolution = (1024, 768)
    # camera.awb_mode = 'off'
    # camera.exposure_mode = 'off'
    camera.start_preview()
    # Camera warm-up time
    time.sleep(5)
    camera.capture('foo.jpg')
    camera.stop_preview()

if __name__ == '__main__':
    main()