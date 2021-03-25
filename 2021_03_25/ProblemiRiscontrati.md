# Problemi riscontrati nella creazione dell'immagine
Immagine BSP 5 con usb gadget support, scipy, alsaaudio

## Non viene riconosciuta la usb gadget
- **SOLUZIONE**
    - Entrare nella cartella: $(CARTELLA_DEL_BPS5_DI_YOCTO)/layers/meta-toradex-demos/recipes-images/images
    - Aprire il file tdx-reference-minimal-image.bb
    - ```sh
        cd ./layers/meta-toradex-demos/recipes-images/images
        gedit  tdx-reference-minimal-image.bb
      ```