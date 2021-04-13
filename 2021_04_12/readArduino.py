#!/usr/bin/python
import serial
import syslog
import time
import os
import datetime
import signal
import sys
fileLog = None

#Listen to Ctrl+C
def signal_handler(sig, frame):
    print('You pressed Ctrl+C!')
    #Close file
    fileLog.close()
    sys.exit(0)

#The following line is for serial over GPIO
port = '/dev/ttyACM0'

ard = serial.Serial(port, 9600)

if __name__ == "__main__":
    signal.signal(signal.SIGINT, signal_handler)
    #Logging file
    fileLog = open("fileLog.csv","a")

    while(True):
        line = (ard.readline()).decode('UTF-8')
         #Estract delta time
        co2 = line
        current_time = datetime.datetime.now()
        #Write to file
        fileLog.write("%s,%s\n" % (current_time, co2.strip()))
        fileLog.flush()
        print(line)
