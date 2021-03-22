#!/usr/bin/env python3
#
#Author:    Giovanni Rasera Per Cynexo
#Date:      2021 03 22
#
import os
import serial
import datetime
import signal
import sys
import wave
import getopt
import alsaaudio
fileLog = None

def play(data):
	#Leggi e suona
	while data:
		device.write(data)
		data = f.readframes(periodsize)

def usage():
	print('usage: playwav.py [-d <device>] <file>', file=sys.stderr)
	sys.exit(2)

#Ctrl+C
def signal_handler(sig, frame):
	print('Stop Ctrl+C!')
	#Chiudi file
	fileLog.close()
	sys.exit(0)

#Main
if __name__ == '__main__':
	signal.signal(signal.SIGINT, signal_handler)

	#Logging file
	fileLog = open("~/fileLog.csv", "a")

	device = 'default'
	opts, args = getopt.getopt(sys.argv[1:], 'd:')
	#Cerco un se è specificato un altro device
	for o, a in opts:
		if o == '-d':
			device = a
	#Come usare
	if not args:
		usage()

	#Listening to the driver
	ser = serial.Serial('~/input.txt')
	f = wave.open(args[0], 'rb')			#Open
	periodsize = f.getframerate() // 8
	device = alsaaudio.PCM()	
	#Prebuffering
	data = f.readframes(periodsize)

	while(True):
		#Messaggi in entrata da m4
		line = (ser.readline()).decode('UTF-8')

		#Play
		play(data)

		#Estract delta time
		delta_time = int(line.split(':')[1])
		current_time = datetime.datetime.now()
		#Write to file
		fileLog.write("%s,%s,%d\n" % (current_time, line.strip(), delta_time))
		fileLog.flush()

	#Close file
	fileLog.close()
