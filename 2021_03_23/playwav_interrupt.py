#!/usr/bin/env python3
#
#Author:    Giovanni Rasera Per Cynexo
#Date:      2021 03 22
#
from periphery import GPIO
import sys
import wave
import getopt
import signal
import alsaaudio
gpio_CynexoFrontButton = GPIO("/dev/gpiochip4", 12, "in")
gpio_CynexoFrontButton.edge = "rising"

def play(device, f):
	periodsize = f.getframerate() // 8
	device = alsaaudio.PCM()	
	#Aspetta per farlo partire
	data = f.readframes(periodsize)		#Prebuffering
	
	#Interrupt
	gpio_CynexoFrontButton.read_event()

	#Leggi e suona
	while data:
		device.write(data)
		data = f.readframes(periodsize)

def usage():
	print('usage: playwav.py [-d <device>] <file>', file=sys.stderr)
	sys.exit(2)

#Ctrl+C
def signal_handler(sig, frame):
    print('Stop: Ctrl+C!')
    sys.exit(0)

#Main
if __name__ == '__main__':
	signal.signal(signal.SIGINT, signal_handler)
	device = 'default'
	opts, args = getopt.getopt(sys.argv[1:], 'd:')
	#Cerco un se è specificato un altro device
	for o, a in opts:
		if o == '-d':
			device = a
	#Come usare
	if not args:
		usage()

	#Read only mode
	with wave.open(args[0], 'rb') as f:
		play(device, f)
