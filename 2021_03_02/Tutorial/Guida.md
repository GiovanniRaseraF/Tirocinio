# Compilazione con gcc-arm (scritto da Toradex)
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

