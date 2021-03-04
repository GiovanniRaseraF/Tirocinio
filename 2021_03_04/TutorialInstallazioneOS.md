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
