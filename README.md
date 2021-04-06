## Tirocinio
# 2021 04 06
  - **inizio: 9.00,      fine: 17.30**
  - Implementazione dell'interprete
  - Implementazione della sezione di esecuzione dei comandi interpretati
  - Implementazione del gestore degli eventi

# 2021 04 02
  - **inizio: 9.00,      fine: 17.30**
  - Creazione del lettore dei comandi nell'arduino
  - Comunicazioni dei valori dei sensori tramite bluetooth

# 2021 04 01
  - **inizio: 9.00,      fine: 18.07**
  - Creazione progetto lettura co2

# 2021 03 31
  - **inizio: 9.00,      fine: 17.10**
  - Creazione progetto lettura co2

# 2021 03 30
  - **inizio: 9.00,      fine: 17.40**
  - Creazione di un esempio per l'utilizzo di bluetooth ble su arduino nano 33 ble

# 2021 03 29
  - **inizio: 9.00,      fine: 17.30**
  - Studio del protocollo bluetooth BLE

# 2021 03 26
  - **inizio: 9.00,      fine: 17.30**
  - Studio del protocollo bluetooth BLE
# 2021 03 25
  - **inizio: 9.00,      fine: 17.50**
  - Bitbake dell'immagine del BSP 5 con scipy, alsaaudio, usb gadget, flask-socketio

# 2021 03 24
  - **inizio: 9.00,      fine: 17.50**
  - Testing del caricamento di file .elf dal bootloader di imx7
  - Installazione di scipy su Yocto project insieme a pyalsaaudio

# 2021 03 23
  - **inizio: 9.00,      fine: 17.30**
  - Creazione di script per lettura di interrupt da gpio e utilizzo di threading

# 2021 03 22
  - **inizio: 10.00,      fine: 18.40**
  - Creazione tutorial di installazione di pyalsaaudio sul modulo
  - Creazione di uno script di esempio

# 2021 03 20
  - Messo apposto il programma per la lettura di pyalsaaudio

# 2021 03 19
  - **inizio: 9.00,      fine: 17.50**
  - Installazione delle librerie audio sul modulo
  - Creazione di un local.conf per Yocto Project personalizzato
  - Creazione di un immagine di linux con all'interno le librerie necessarie ad usare l'audio
  - Creazione di uno script in python che precaricasse la traccia audio con conseguente assezza di delay tra la rischiesta di far partire la traccia audio 
  e l'effettiva riproduzione della stessas

# 2021 03 18
  - **inizio: 9.00,      fine: 18.00**
  - Installazione delle librerie audio sul modulo

# 2021 03 17
  - **inizio: 9.00,      fine: 17.30**
  - Porting di tensorflow su M4
  - Installazione delle librerie per audio sul modulo

# 2021 03 16
  - **inizio: 9.00,      fine: 17.50**
  - Creazione di un programma in c che permettesse di leggere da gpio
  - fare output su dei led RGB
  - Creazione della comunicazione di log tra m4 e Linux
  - Creazine di un logger in Python
  - Compilazione di tensorflow per cortex m4

# 2021 03 15
  - **inizio: 9.00,      fine: 18.00**
  - Creazione di un programma in c che permettesse di leggere da gpio
    - fare output su dei led RGB
  - Creazione del file di descrizione delle gpio della scheda Cynexo
  - Creazine del sistema operativo con python

# 2021 03 12
  - **inizio: 9.00,      fine: 17.40**
  - Compilazione di un device tree personalizzato
  - Caricamento del device tree nel modulo
  - Flashing del modulo per capire come creare giusto device tree
  - Creazione con successo di un Custom Device tree che permettesse di dare la priorità di acesso
  alla gpio5 solamente all'm4
  - Creazione di un piccolo esempio di accesso alla gpio140
  
# 2021 03 11
  - **inizio: 9.00,      fine:18.10**
  - Creazione in un programma per la lettura del GPIO dal M4

# 2021 03 10
  - **inizio: 9.00,      fine:17.40** 
  - Creaizione della macchina a stati e caricamento del elf nell'M4
  - Testing del codice 
  - Creazione di un file che documenta come fare a caricare un .elf nell'M4
  - Creazione di un file python per creare dati da dare in pasto alla macchina a stati
  - Creazione di uno script per inviare i diti all'M4
  - Studio del funzionamento del GPIO interrupt vector e di come viene implementato in c
  - Studio del funzionamento della lettura di un GPIO da linux
  - Creazione di un programma in c che legge da GPIO140 e scatena un evento

# 2021 03 09
  - **inizio: 9.00,      fine: 17.30** 
  - Installazione del bootloader
  - Caricamento con successo del mio bootloader e del sistema operativo
  - Caricamento di un file compilato da me con armgcc
  - Comunicazione tra Cortex A7 e M4 tramite una pipe
  - Creazione di un test da far girare nel M4

# 2021 03 08
  - **inizio: 9.00,      fine: 18.20**
  - Installazione di un bootloader personalizzato
  - Installazione di linux personalizzato sulla som

# 2021 03 05        
  - **REMOTO inizio: 9.00,      fine: 18.00**
  - Creazione del Turorial Installazione OS su Colibri iMX7 
  - Studio del funzionamento di Yocto e prova di compilazione con il mio PC
  - Compilazione di codice con SDK Yocto
  - Compilazione di codice con freeRTOS os, studio di esempi
    - rpmsg tra i due processori, scambio di messaggi
  - Studio del funzionamento dello scambio di messaggi tra i processori

# 2021 03 04
  - **inizio: 9.00,      fine: 17.40**
  - Installazione del sistema operativo all'interno di imx7
  - Installazione di Toradex Easy Installer 
  - Flash della scheda sd e del sistema operativo

# 2021 03 03
  - **inizio: 9.00,      fine: 17.40**
  - Lettura libro sulla programmaizone di sistemi embedded
  - Capire come funziona il device tree
  - Creazione del device tree di toradex
  - Compilazione del device tree per Toradex colibri iMX7
    
# 2021 03 02
  - **inizio: 9.00,      fine: 17.50**
  - Bitbake del progetto siccome ha dato errore nella compilazione dell'sdk
  - Creazione della repo di git 
  - Obbligatorio accettare eula nel momento in cui si vuole fare un bitbake
  - Finito di fare il bitbake
  - Creazione dell'sdk da bitbake
  - Installazione del sdk tramite il comando sh creato dal comando precedente
  - Compilazione di un esempio di Toradex Colibri iMX7 
  - Creazione tutorial per installazione di gcc-arm per la compilazione di codice toradex

# 2021 03 01
  - **inizio: 14.30,    fine: 17.50**
  - Discussione generale su cosa dovrò fare durante il tirocinio
  - Presentazione dell'Hardware 
  - Creazione di un utente per windows
      - Installazione di programmi generali
      - Creazione di una VM con Virtual Box con Ubuntu 18
      - Installazione degli essentials
      - Installazione di Yocto Project 
          - Creazione dei file necessari a yocto per fare il 
              bitbake del progetto 
          - bitbake di tutto che dovrebbe finire in 3 ore
      
