#!/usr/bin/python3
#
#Author:    Giovanni Rasera Per Cynexo
#Date:      2021 03 16
#
import os
import serial
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

#Main
if __name__ == "__main__":
    signal.signal(signal.SIGINT, signal_handler)
    #Loading driver
    if os.system("modprobe imx_rpmsg_tty"):
        print("Problems Loading: imx_rpmsg_tty")
    else:
        print("Success Loaded: imx_rpmsg_tty")

    #Logging file
    fileLog = open("fileLog.csv","a")

    #Listening to the driver
    ser = serial.Serial('/dev/ttyRPMSG0')
    while(True):
        line = (ser.readline()).decode('UTF-8')
        #Estract delta time
        delta_time = int(line.split(':')[1])
        current_time = datetime.datetime.now()
        #Write to file
        fileLog.write("%s,%s,%d\n" % (current_time, line.strip(), delta_time))
        fileLog.flush()

    #Close file
    fileLog.close()


