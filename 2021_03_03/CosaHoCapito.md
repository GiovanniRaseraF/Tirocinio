## Device Tree di iMX7
# Pin di comunicazione con il kernel
```json
chosen {
   stdout-path = &uart1;
};
```
- Da questa riga che si trova nel file imax_colibri_imx7.dts
mi permette di capire che per leggere delle informazioni che arrivano dal kernel posso usare la uart1
- La uart1 mi diche che:
```json
&uart1 {
	pinctrl-names = "default";
	pinctrl-0 = <&pinctrl_uart1 &pinctrl_uart1_ctrl1>;
	uart-has-rtscts;
	fsl,dte-mode;
	status = "okay";
};
```
questo mi fa capire che per capire da dove leggere devo collecarmi ai pinctrl_uart1_ctrl1
- questi pin sono:
```json
pinctrl_uart1_ctrl1: uart1-ctrl1-grp {
    fsl,pins = <
        MX7D_PAD_SD2_DATA1__GPIO5_IO15		0x14 /* DCD */
        MX7D_PAD_SD2_DATA0__GPIO5_IO14		0x14 /* DTR */
    >;
};
```
