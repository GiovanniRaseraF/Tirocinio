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
import threading
import time
sig_control_c = False

#Ctrl+C
def signal_handler(sig, frame):
	print('Stop: Ctrl+C!')
	global sig_control_c 
	sig_control_c = True
	sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

#Interrut per far partire la musica
class InterruptButton(threading.Thread):
	def __init__(self, threadID, name):
		threading.Thread.__init__(self)
		self.gpio_CynexoFrontButton = GPIO("/dev/gpiochip4", 12, "in")
		self.gpio_CynexoFrontButton.edge = "falling"
		self.threadID = threadID
		self.name = name

	def play(self, data, periodsize, device, f):
		#Leggi e suona
		while data:
			device.write(data)
			data = f.readframes(periodsize)

	def run(self):
		f =  wave.open(args[0], 'rb')
		periodsize = f.getframerate() // 8
		device = alsaaudio.PCM()
		while(True):
			#Prebuffering
			data = f.readframes(periodsize)
			#Interrupt
			print("Interrupt Button:")
			self.gpio_CynexoFrontButton.read_event() 	
			#Play
			self.play(data, periodsize, device, f)

			f.close()
			f =  wave.open(args[0], 'rb')

#RGB
class RGBCicle(threading.Thread):
	def __init__(self, threadID, name):
		threading.Thread.__init__(self)
		self.gpio_green = GPIO("/dev/gpiochip1", 24, "out")
		self.gpio_red = GPIO("/dev/gpiochip1", 25, "out")
		self.gpio_blue = GPIO("/dev/gpiochip2", 23, "out")
		self.threadID = threadID
		self.name = name
	
	def run(self):
		while(True):
			self.gpio_green.write(False)
			self.gpio_red.write(True)
			self.gpio_blue.write(False)
			time.sleep(1)
			self.gpio_green.write(False)
			self.gpio_red.write(False)
			self.gpio_blue.write(True)
			time.sleep(1)
			self.gpio_green.write(True)
			self.gpio_red.write(False)
			self.gpio_blue.write(False)
			time.sleep(1)
			

def usage():
	print('usage: playwav.py [-d <device>] <file>', file=sys.stderr)
	sys.exit(2)


#Main
if __name__ == '__main__':
	device = 'default'
	opts, args = getopt.getopt(sys.argv[1:], 'd:')

	#Cerco un se è specificato un altro device
	for o, a in opts:
		if o == '-d':
			device = a
	
	#Come usare
	if not args:
		usage()

	#Threading
	threadButton = InterruptButton(1, "Interrupt Button")
	threadOther = RGBCicle(2, "RGB")

	threadButton.start()
	threadOther.start()