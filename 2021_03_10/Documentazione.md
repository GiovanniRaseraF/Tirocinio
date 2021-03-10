# Creazione di una macchina a stati nel Cortex M4
## Funzione per leggere dal canale di comunicazione
```c
    /*
    *value:     dove salvare il dato letto, 0 se c'è un fail
    *rx_buf:    buffere rx da dove leggere i dati
    *app_chnl:  canale di comunicazione
    Rerurn:
        0: fail
        1: seccess
    */
    int read_int_from_buffer(int *value, void *rx_buf, struct rpmsg_channel *app_chnl);
```
- Questa funzione legge l'input dal buffer
- Attenzione: 
    - Il buffer di lettura potrebbe essere riempito troppo velocemente
    - Per evitare c'è bisogno di implementare qualche meccanismo di controllo come uno sleep nel codice che invia dati al M4
- C'è anche bisogno di pulire la stringa di input siccome potrebbe contenere dati inutili
- Se tutto va a buon fine la stringa verra trasformata in intero e il risultato verrà salvato all'interno di *value

## Come comunicare con M4
- Avremo due terminali aperti
    - Terminale 1(T1):  mi permette di compilare il codice e di inviarlo all'A7
    - Terminale 2(T2):  mi permette di collegarmi all'A7 e di usare ssh
- Prima di tutto c'è bisogno di fare queste operazioni
    - In T1:
    ```bash
        #Spostarsi nella cartella armgcc del proprio progetto
        #dove è presente il file build_all.sh
        python3 genera.py 500000 > dati.txt 
        scp dati.txt root@192.168.11.1:/home/root
        #Questo basta farlo la prima volta
        scp loadData.sh root@192.168.11.1:/home/root    
    ```
    - In T2:
    ```bash
        ssh root@192.168.11.1
        mount #TODO: Trovare cosa scrivere come mount
    ```
    - In T1:
    ```bash
        ./build_all.sh && scp ./build/*.elf root@192.168.11.1:/media/vf__ #TODO: in che media va caricato ?
    ```
    - In T2:
    ```bash
        unmount #TODO: Il medi da togliere
        reboot
        ssh root@192.168.11.1
        modprobe #TODO: A chi fare il moprobe
    ```
- Se nel bootloader sono stati impostati i parametri giusti vedremo che il modulo si caricherà

## Testare il modulo 
- Dopo che il modulo è partino dobbiamo collegarci alla tty che ha creato
    - In T2:
    ```bash
       #TODO: Collegamento alla tty

        chmod +x loadData.sh
       ./loadData.sh 0.01 < dati.txt
    ```







