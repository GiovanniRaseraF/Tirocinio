# Installazione di **pyalsaaudio** su Toradex Colibri IMX7
- Questa guida mira ad installare pyalsaaudio sul'SO creato con Yocto Project
- Questi sono i punti che vedremo:
    - Installazione dei tools necessari
    - Download delle repo necessarie
    - Modifica dei file **bblayers.conf** e **local.conf**
    - Bitbake del projetto
    - Utilizzo della libreria

## **1** Installazione dei tools necessari
- Ubuntu:
    ```bash
    #Tools
    sudo apt-get install gawk wget git-core diffstat unzip curl
    sudo apt-get install texinfo gcc-multilib build-essential 
    sudo apt-get install chrpath socat cpio python python3 python3-pip 
    sudo apt-get install python3-pexpect xz-utils debianutils iputils-ping
    sudo apt-get install python-git gedit
    #Git
    sudo apt install git
    git config --global user.name "Mario Rossi"
    git config --global user.email mariorossi@example.com
    #Repo Bootstrap
    mkdir ~/bin
    export PATH=~/bin:$PATH
    curl http://commondatastorage.googleapis.com/git-repo-downloads/repo > ~/bin/repo
    chmod a+x ~/bin/repo
    ```

## **2** Download delle repo necessarie
- Repo di Toradex versione 5.x.y
    ```bash
    #NON USARE **ZSH** PER FARE IL PROCEDIMENTO 
    mkdir ${HOME}/oe-core
    cd ${HOME}/oe-core
    repo init -u https://git.toradex.com/toradex-manifest.git -b dunfell-5.x.y -m tdxref/default.xml
    repo sync
    #Cambio shell
    test `echo $0` != "bash" && bash
    ```
- Esporto le variabili
    ```bash
    . export
    ```

## **3** Modifica dei file **bblayers.conf** e **local.conf**
- Sarà necessario modificare i due file in modo da installare tutte le librerie necessarie a comunicare con i driver audio
- **bblayers.conf**
    ```bash
    gedit ./conf/bblayer.conf
    #Modificarlo a piacere, importante specificare i layer da cui prendere le librerie 
    ```
- **local.conf**
    ```bash
    gedit ./conf/local.conf
    ```
- Aggiungere questi pacchetti
    ```bash
    #Licenza per ffmpeg
    LICENSE_FLAGS_WHITELIST="commercial" 
    #Audio
    IMAGE_INSTALL_append = " alsa-utils"
    IMAGE_INSTALL_append = " alsa-tools"
    IMAGE_INSTALL_append = " alsa-lib"
    IMAGE_INSTALL_append = " alsa-topology-conf"
    IMAGE_INSTALL_append = " tinyalsa"
    IMAGE_INSTALL_append = " ffmpeg flac libsamplerate0 libsndfile1 mpg123 pulseaudio"
    #Python
    IMAGE_INSTALL_append = " python3"
    IMAGE_INSTALL_append = " python3-pip"
    IMAGE_INSTALL_append = " python3-numpy"
    IMAGE_INSTALL_append = " python3-pyserial"
    IMAGE_INSTALL_append = " python3-flask"
    IMAGE_INSTALL_append = " python3-pyudev"
    IMAGE_INSTALL_append = " python3-spidev spitools"
    IMAGE_INSTALL_append = " python3-pyalsaaudio python3-pyaudio"
    IMAGE_INSTALL_append = " python3-periphery"
    IMAGE_INSTALL_append = " python3-dbus python3-pygobject"
    IMAGE_INSTALL_append = " python3-pybluez"
    ```
- **SALVARE I DUE FILE !!**

## **4** Bitbake del projetto
- Creazione dell'immagine
    ```bash
    bitbake tdx-reference-minimal-image
    #Ci vorranno delle ore
    #Copiare la cartella Download da progetti vecchi se si vuole velocizzare 
    ```
- Installare il Sistema Operativo nella SOM
    - Tutorial [Installazione del SO compilato con Yocto in Colibri iMX7](https://github.com/GiovanniRaseraF/Tirocinio/blob/master/2021_03_05/TutorialInstallazioneOS.md)

## **5** Utilizzo della libreria
- Test: (La versione di Python deve essere maggiore o uguale a 3.6)
    ```bash
    python3 --version
    #Output: 3.8.2
    ```
- Scrivere nel file questo:
    ```python
    from __future__ import print_function
    import sys
    import wave
    import getopt
    import alsaaudio

    def play(device, f):	
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
        print('%d channels, %d sampling rate, format %d, periodsize %d\n' % (
            f.getnchannels(),
            f.getframerate(),
            format,
            periodsize))
        
        device = alsaaudio.PCM()
        data = f.readframes(periodsize)
        c = input("Press ANY Key to start:")
        while data:
            # Read data from stdin
            device.write(data)
            data = f.readframes(periodsize)

    def usage():
        print('usage: playwav.py [-d <device>] <file>', file=sys.stderr)
        sys.exit(2)

    if __name__ == '__main__':
        device = 'default'
        opts, args = getopt.getopt(sys.argv[1:], 'd:')
        for o, a in opts:
            if o == '-d':
                device = a

        if not args:
            usage()
            
        with wave.open(args[0], 'rb') as f:
            play(device, f)
    ```
- La spiegazione del funzionamento è qui:
    - [Funzionamento della libreria]()



