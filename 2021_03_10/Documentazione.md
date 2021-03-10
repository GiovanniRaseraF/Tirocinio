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
- Prima di tutto c'è bisogno di fare queste operazioni
- Avremo due terminali aperti
    - Terminale 1:  mi permette di compilare il codice e di inviarlo all'A7
    - Terminale 2:  mi permette di collegarmi all'A7 e di usare 

