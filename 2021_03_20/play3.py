import pyaudio
import wave
import sys
import signal

stream = None
p = None
CHUNK = 1024

#Listen to Ctrl+C
def signal_handler(sig, frame):
    print('You pressed Ctrl+C!')
    #Close Audio
    stream.stop_stream()
    stream.close()
    p.terminate()
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

#Main
if len(sys.argv) < 2:
    print("Plays a wave file.\n\nUsage: %s filename.wav" % sys.argv[0])
    sys.exit(-1)

c = input("open file: Press Any Key:")
wf = wave.open(sys.argv[1], 'rb')

c = input("load pyaudio: Press Any Key:")
p = pyaudio.PyAudio()

c = input("load Stream: Press Any Key:")
stream = p.open(format=p.get_format_from_width(wf.getsampwidth()),
                channels=wf.getnchannels(),
                rate=wf.getframerate(),
                output=True)

c = input("load wf data: Press Any Key:")
#Preload
data = wf.readframes(CHUNK)

c = input("Play music: Press Any Key:")
while data != '':
    stream.write(data)
    data = wf.readframes(CHUNK)

#End
stream.stop_stream()
stream.close()

p.terminate()

