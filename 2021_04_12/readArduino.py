#!/usr/bin/python
import serial
import syslog
import time

#The following line is for serial over GPIO
port = '/dev/ttyACM0'


ard = serial.Serial(port, 9600)

while(True):
    msg = ard.readline()
    print(msg)