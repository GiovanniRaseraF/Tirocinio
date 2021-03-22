# Funzionamento della libreria pyalsasound
- Una spiegazione più dettagliata si trova qui: [Documentazione](https://larsimmisch.github.io/pyalsaaudio/libalsaaudio.html)
## Il codice di esempio
- Include  
    ```python
    from __future__ import print_function
    import sys
    import wave
    import getopt
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
- Setting del formato del file
    ```python
    format = None
    # 8bit is unsigned in wav files
    if f.getsampwidth() == 1:
        format = alsaaudio.PCM_FORMAT_U8
    # Otherwise we assume signed data, little endian
    elif f.getsampwidth() == 2:
        format = alsaaudio.PCM_FORMAT_S16_LE
    elif f.getsampwidth() == 3:
        format = alsaaudio.PCM_FORMAT_S24_3LE
    elif f.getsampwidth() == 4:
        format = alsaaudio.PCM_FORMAT_S32_LE
    else:
        raise ValueError('Unsupported format')
    
    periodsize = f.getframerate() // 8
    ```
- Caricamento dei dati e del device
    ```python
    device = alsaaudio.PCM()
    data = f.readframes(periodsize)
    c = input("Press ANY Key to start:")
    ```
- Leggo e riproduco il file
    ```python
    while data:
        # Read data from stdin
        device.write(data)
        data = f.readframes(periodsize)
    ```