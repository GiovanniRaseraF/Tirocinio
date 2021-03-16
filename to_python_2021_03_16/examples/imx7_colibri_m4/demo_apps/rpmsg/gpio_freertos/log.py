import os
import serial
import datetime

#Loading driver
if os.system("modprobe imx_rpmsg_tty"):
    print("Problems Loading: imx_rpmsg_tty")
else:
    print("Success Loaded: imx_rpmsg_tty")

#Logging file
fileLog = open("fileLog.csv","w+")

#Listening to the driver
ser = serial.Serial('/dev/ttyRPMSG0')
while(True):
    fileLog = open("fileLog.csv","w+")
    line = ser.readline()
    current_time = datetime.datetime.now()
    fileLog.write("%s,%s,%d\n" % (current_time, line.strip(), 0))
    fileLog.close()