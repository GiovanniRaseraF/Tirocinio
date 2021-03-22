from __future__ import print_function
import sys
import wave
import getopt
import alsaaudio
from periphery import GPIO

gpio_CynexoFrontButton = GPIO("/dev/gpiochip5", 12, "in")

while True:
    value = gpio_CynexoFrontButton.read()
    print(str(value))
