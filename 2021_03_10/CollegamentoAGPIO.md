# Collegamento a GPIO
- Mi ci posso collegare entrando nella cartella dove si trovano le astrazioni degli 
io in linux.
- La cartella in questione si chiama /sys/class/gpio/
    - la prima cosa che devo fare è quella di esportare la porta che voglio utilizzare
    - nel mio caso voglio usare la 140 
    - quindi farò
    ```bash
    echo 140 > export
    ```
    - A questo punto posso settare la modalità di lettura o scrittura (in, out)
    - nel mio caso
    ```bash
    echo "in" > gpio140/direction
    ```
    - Setto edge (falling, rising)
    ```bash
    echo "rising" > gpio140/edge
    ```
    - A questo punto posso leggerla
    ```bash
    cat gpio140/value
    ```