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
- Aggiungere questi pacchetti (Alcuni sono superflui)
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
    #!/usr/bin/env python3
    import sys
    import wave
    import getopt
    import signal
    import alsaaudio

    def play(device, f):
        periodsize = f.getframerate() // 8
        device = alsaaudio.PCM()	
        #Aspetta per farlo partire
        data = f.readframes(periodsize)			#Prebuffering
        c = input("Press ANY Key to start:")	#Un interrupt o qualcosa
        #Leggi e Suona
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
        #Cerco un se è specificato un altro device NON CI SERVE
        for o, a in opts:
            if o == '-d':
                device = a
        #Come usare
        if not args:
            usage()

        #Read only mode
        with wave.open(args[0], 'rb') as f:
            play(device, f)
    ```
- La spiegazione del funzionamento è qui:
    - [Funzionamento della libreria](https://github.com/GiovanniRaseraF/Tirocinio/blob/master/2021_03_22/funzionamentoPyalsaaudio.md)



