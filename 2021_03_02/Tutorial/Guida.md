# Compilazione con gcc-arm
Il tutorial spiega come compilare del codice scritto in C per 
Toradex Colibri iMX7.
!!Tutto il codice bash è testato su Ubuntu.

## Prerequisiti
```bash
#Installazione dei pacchetti necessari

sudo apt update 
sudo apt install git
sudo dpkg --add-architecture i386
sudo apt-get install libc6:i386 libncurses5:i386
sudo apt-get install make cmake
```

- A questo punto è necessario scaricare l'ultima versione di gcc-arm 
come pacchetto *tar.bz2
- Sarà necessario scaricare la versione adatta al sistema operativo utilizzato per compilare il codice (SOLITAMENTE X86_64).
- [Sito di ARM per scaricare gcc-arm](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)

## Installazione del gcc-arm
- Dopo aver scaricato il file *tar.bz2 sarà necessario installarlo
```bash
# Lo installeremo nella cartella home

cd ~
sudo apt install tar && tar xjf ~/Downloads/gcc-arm-none-eabi-10-2020-q4-major-x86_64-linux.tar.bz2

```