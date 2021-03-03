Cosa serve
    - una volta il kernel aveva tutto quello che gli serviva

    - Con il device tree muovo la descrizione dell'hardware in un file che sarebbe il device tree
    - passo poi il file al kernel

    - Devo avere una funzione per fare il boot dell DT
        - bootm <kernel img addr>
        - bootm.image

Cosa è il Device Tree
    - è una data structure che descrive l'hardware
    - Vengono descritte quello che non sono scopribili (i2c)

Basi
    - Nodi : 
        - nome
            - proprietà
            - sottonodi

            - child node 

            - label per i Phandle

From Source to Binary
    - devo compilarlo
    - tramite un makefile

Proprietà
    - compatible : mi dice queli sono i driver che devono guidare il mio device
    - reg : per i memory mapped <phandle >
    - dmas : dma
    - dmas-names : da i nomi ai dmas
    - clock : identificazione del timing
    - status : se disables non viene fatto il probe al device



Driver side:


Bindings:
    - bisogna date tutte le informazioni necessarie ai driver per accedere all'hardware

il DT:
    - E' indipendente dall'os
    - Ma non è veramente così

################

Rimuovere la descrizione dell'hardware dal kernel

Bisogna passare al kernel il giusto dtb

trovo i file in arch/arm/boot/dts

posso compilarlo con il compilatore dtc 

Dobbiamo descirvere i device tramite i bus

Descrizione
 /{} : il primo nodo

node@0 primo nodo

label : node@1 {};

posso dare nelle proprietà ai nodi
ad esempio string-property = "string";
string-list-property = "first string", "second string";
byte-string-property = [0x01 0x21 0x76];

    child-node@

per usare status per disabilitare un device
se metto okay allora è attivo


Le proprietà:
    compatible: identifica la piattaforma hardware ed exegue del codice specifico alla macchina
    cpus: descrive le cpu presenti nel sistema
    memory: descrive la quantità e l'indirizzo iniziale della ram
    chosen: usato per passare la command line del kernel
    aliases: permette di definire degli alias per dei nodi
        - nodes: descrivono dei bus
        - nodes: descrivono hardware devices
    
