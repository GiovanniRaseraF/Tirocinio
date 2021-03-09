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
        ```c
            MU_Init(BOARD_MU_BASE_ADDR);
            NVIC_SetPriority(BOARD_MU_IRQ_NUM, APP_MU_IRQ_PRIORITY);
            NVIC_EnableIRQ(BOARD_MU_IRQ_NUM);
        ```
    - A questo punto devo dire a freeRTOS di creare un task
        ```c
            xTaskCreate(StrEchoTask, "String Echo Task", APP_TASK_STACK_SIZE,
                NULL, tskIDLE_PRIORITY+1, NULL);
        ```
        - Questo task deve contenere la funzione che voglio eseguire [freeRTOS doc](https://www.freertos.org/a00125.html)
        - Nel mio caso voglio creare un task per la funzione: StrEchoTask
    - Alla fine faccio partire lo scheduler:
        ```c
            vTaskStartScheduler();
        ```

- La funzione **static void StrEchoTask(void \*pvParameters)**
    - Inisializzo delle variabili
    - Creao due variabili 
        ```c
            struct remote_device *rdev = NULL;          /*Puntatore a cpu remota*/
            struct rpmsg_channel *app_chnl = NULL;      /*Puntatore al canale*/
        ```
    - Inizializzo il canale
        ```c
            result = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
            assert(result == 0);
        ```
    - Posso usare la funzione **GPIO_Ctrl_GetKey(BOARD_GPIO_SWITCH2_CONFIG);**
        - Per leggere uno switch e devo impostarlo all'interno del file: gpio_ctrl.c
    - A questo punto posso leggere dall GPIO se lo switch è premuto o no
        - posso quindi leggere dal rx_buf
        ```c
            result = rpmsg_rtos_recv_nocopy(app_chnl->rp_ept, &rx_buf, &len, &src, 0);    
        ```
        - Da documentazine se voglio che la funzione diventi bloccante posso mettere -1 nella sezione di timeout

    - Mi devo assicurare che il buffer non sia troppo grandee e poi lo posso leggere
        ```c
            /* copio la stringa nel buffer rx */
            assert(len < sizeof(str_buffer));
            memcpy(str_buffer, rx_buf, len);
            str_buffer[len] = 0; /* End string by '\0' */     
        ```



    