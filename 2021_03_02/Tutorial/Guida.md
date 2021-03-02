# Compilazione con gcc-arm (scritto da Toradex)
Il tutorial spiega come compilare del codice scritto in C per 
Toradex Colibri iMX7.
!!Tutto il codice bash è testato su Ubuntu.
## Prerequisiti
```bash
sudo apt update; sudo apt install git;
sudo dpkg --add-architecture i386
sudo apt-get install libc6:i386 libncurses5:i386
sudo apt-get install make cmake
```