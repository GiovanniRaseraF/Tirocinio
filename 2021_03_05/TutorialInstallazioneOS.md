# Installazione del SO compilato con Yocto in Colibri iMX7
Questo tutorial permette di installare il SO creato con Yocto project nel Colibri iMX7

## Prerequisiti
- Immagine del SO in formato .tar
- VMWare (VirtualBox NON FUNZIONA)
- Una VM con Linux
- SDCard formattata in FAT32 (Chiavetta USB NON FUNZIONA)

### All'interno di Linux
- vnc, minicom, git, connessione internet
```bash
cd ~
sudo apt install git wget minicom 

# Installazione di vnc
wget https://www.realvnc.com/download/file/viewer.files/VNC-Viewer-6.20.529-Linux-x64.deb
sudo dpkg -i VNC-Viewer-6.20.529-Linux-x64.deb
```

### Scaricare Toradex Easy Installer
```bash
cd ~
wget https://docs.toradex.com/104570-colibri-imx7-toradexeasyinstaller.zip
sudo apt install unzip 
unzip 104570-colibri-imx7-toradexeasyinstaller.zip
```

### Connettere la board
- Connettere il cavo USB  (Computer(USB)----(microUSB)Colibri_iMX7)
- Nella finestra dei dispositivi di VMWare accedere al dispositivo (Texas Instruments)
    - Attenzione: Verranno visualizzati altri dispositivi USB che dovranno essere collegati alla VM in modo che la scheda posso comunicare.
    - <img src="CatturaDispositiviUSB_VM.PNG" width="200">
- A qusto punto la scheda sarà propriamente collegata alla VM
    - Attenzione: Come vedremo in seguito potrebbe essere necessario accendere la scheda per vedere alcuni dei dispositivi

## Preparazione dei tool all'interno di Linux
- Questo è un punto fondamentale per capire se l'installazione sta procedendo
### Workspace
- Aprire tre terminali (per comodità), posizionarli in modo da vederli tutti e tre
    - Terminale 1:
    - ```bash
        #Toradex Easy Installer
        cd ~
        cd Colibri-iMX7_ToradexEasyInstaller_1.8-20181019/
        #NON PREMERE INVIO NEL PROSSIMO COMANDO
        chmod +x recovery-linux.sh && ./recovery-linux.sh
      ```
    - Terminale 2:
    - Terminale 3:

## Esecuzione della procedura
### Accensione (Recovery Mode)
- FARE ATTENZIONE IN QUESTO PASSAGGIO:
    - NON FLETTERE TROPPO LA BOARD
    - TOCCARE SOLO I PIN CHE VERRANNO INDICATI
    - ESSERE SICURI CHE LA SCHEDA NON TOCCI IL PCB SOTTOSTANTE IN ALCUN MODO

- Attaccare alimentatore, e accenderlo
- Fare **corto** tra questi due pin
- <img src="imx7.jpg" width="200">
- Tenere in corto i pin e accendere la scheda. (Tenere in corto 10 secondi)

