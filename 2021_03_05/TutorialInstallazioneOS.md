# Installazione del SO compilato con Yocto in Colibri iMX7
Questo tutorial permette di installare il SO creato con Yocto project nel Colibri iMX7

## Prerequisiti
- VMWare (VirtualBox NON FUNZIONA)
- Una VM con Linux
- SDCard (Chiavetta USB NON FUNZIONA)

## All'interno di Linux
- vnc, minicom, git, connessione internet
```bash
cd ~
sudo apt install git wget minicom 

# Installazione di vnc
wget https://www.realvnc.com/download/file/viewer.files/VNC-Viewer-6.20.529-Linux-x64.deb
sudo dpkg -i VNC-Viewer-6.20.529-Linux-x64.deb
```

## Scaricare Toradex Easy Installer
```bash
cd ~
wget https://docs.toradex.com/104570-colibri-imx7-toradexeasyinstaller.zip
sudo apt install unzip 
unzip 104570-colibri-imx7-toradexeasyinstaller.zip
```

## Connettere la board
- Connettere il cavo USB  (Computer(USB)----(microUSB)Colibri_iMX7)
- Nella finestra dei dispositivi di VMWare accedere al dispositivo (Texas Instruments)
    - Attenzione: Verranno visualizzati altri dispositivi USB che dovranno essere collegati alla VM in modo che la scheda posso comunicare.
    - <img src="CatturaDispositiviUSB_VM.PNG" width="200">
- A qusto punto la scheda sarà propriamente collegata alla VM
    - Attenzione: Come vedremo in seguito potrebbe essere necessario accendere la scheda per vedere alcuni dei dispositivi

## Accensione (Recovery Mode)
- FARE ATTENZIONE IN QUESTO PASSAGGIO:
    - NON PLETTERE TROPPO LA BOARD
    - TOCCARE SOLO I PIN CHE VERRANNO INDICATI
    - ESSERE SICURI CHE LA SCHEDA NON TOCCI IL PCB SOTTOSTANTE IN ALCUN MODO

- Attaccare alimentatore, e accenderlo
- Fare **corto** tra questi due pin.
- <img src="imx7.jpg" width="200">
