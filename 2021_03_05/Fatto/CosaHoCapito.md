- Devo usare il cross compiler per compilare per architettura arm
- Se compilo per architettura x86 non va bene
    - un modo veloce per capire se ho compilato per larchitettura giusta è usare
    - file ciao.o 
    - se mi dice arm allora va bene
    - Seguito il tutorial che spiega come fare un cross compile di yocto
    - https://www.yoctoproject.org/docs/2.1/sdk-manual/sdk-manual.html


- Compilare per freeRTOS
    - entrare in armgcc
    - export ARMGCC_DIR=~/opt/gcc-arm-none-eabi-10-2020-q4-major

- Come funziona la comunicazione tra i due processori
    - Ogli volta che voglio fare qualcosa nel main devo fare hardware_init();
        - permettetà di inizializzare quello che gli viene specificato in hardware_init.c
    - Configuro quello che mi serve
        - ad esempio  GPIO_Ctrl_Init();
    - Inizializzo MU interrupt
        ```cpp
            MU_Init(BOARD_MU_BASE_ADDR);
            NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
            NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);
        ```
