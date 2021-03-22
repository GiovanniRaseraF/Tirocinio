# Funzionamento della libreria pyalsasound
- Una spiegazione più dettagliata si trova qui: [Documentazione](https://larsimmisch.github.io/pyalsaaudio/libalsaaudio.html)
## Il codice di esempio
- Include  
    ```python
    #!/usr/bin/env python3
    import sys
    import wave
    import getopt
    import signal
    import alsaaudio
    ```
- Indicare il device
    ```python
    device = 'default'
    ```
- Carico il file musicale in formato wav
    ```python
    with wave.open(args[0], 'rb') as f:
        play(device, f)
    ```
## La funzione def play(device, f):
- Velocità di lettura
    ```python
    periodsize = f.getframerate() // 8
    device = alsaaudio.PCM()
    ```
## Caricamento dei dati e ***PREBUFFERING***
    ```python
    #Aspetta per farlo partire
    data = f.readframes(periodsize)			#Prebuffering
    c = input("Press ANY Key to start:")	#Un interrupt o qualcosa
    ```
- Leggo e riproduco il file
    ```python
    #Leggi e Suona
    while data:
        device.write(data)
        data = f.readframes(periodsize)
    ```