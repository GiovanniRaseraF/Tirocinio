#include <assert.h>
#include "gpio_pins.h"
#include "board.h"
#include "gpio_imx.h"

////Cynexo board Specific////

//Input Buttons
/* Switch CynexoFrontButton
 * SODIMM                BALL NAME                GPIO                ALT
 *    184                SD2_CLK                  GPIO05_12           5
 */
gpio_config_t gpioSwitch_CynexoFrontButton = {
    "SODIMM 184",                                      	/* name */
    &IOMUXC_SW_MUX_CTL_PAD_SD2_CLK,               		/* muxReg */
    5,                                              	/* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_SD2_CLK,               		/* padReg */
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PS(5)  |        		/* padConfig */
    	IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_HYS_MASK,
    GPIO5,                                          	/* base */
    12                                              	/* pin */
};

gpio_config_t gpioKeyFunc_CynexoFrontButton = {
	"EXT_IO1_Cynexo_Front_Button",                      /* name */
    &IOMUXC_SW_MUX_CTL_PAD_SD2_CLK,               		/* muxReg */
    5,                                              	/* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_SD2_CLK,               		/* padReg */
    IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PS(5) |        		/* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_SD2_CLK_HYS_MASK,
    GPIO5,                                          	/* base */
    12                                              	/* pin */
};

gpio_init_config_t Switch_CynexoFrontButton = {
    .pin           = 12, //pin number
    .direction     = gpioDigitalInput,
    .interruptMode = gpioIntRisingEdge
};

//RGB Led
/* LED CynexoRGBLed_Green
 * SODIMM                BALL NAME                GPIO                ALT
 *    132                EPDC_GDCLK               GPI02_24            5
 */
gpio_config_t gpioLed_CynexoRGBLed_Green = {
    "CynexoRGBLed: Green",                              /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_GDCLK,               	/* muxReg */
    5,                                              	/* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_GDCLK,                  /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_GDCLK_PS(2) |        	/* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_EPDC_GDCLK_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_EPDC_GDCLK_HYS_MASK,
    GPIO2,                                          	/* base */
    24                                              	/* pin */
};
gpio_init_config_t Led_CynexoRGBLed_Green = {
    .pin           = 24, //pin number
    .direction     = gpioDigitalOutput,
    .interruptMode = gpioNoIntmode
};

/* LED CynexoRGBLed_Red
 * SODIMM                BALL NAME                GPIO                ALT
 *    134                EPDC_GDOE                GPI02_26            5
 */
gpio_config_t gpioLed_CynexoRGBLed_Red = {
    "CynexoRGBLed: Red",                                /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_GDOE,               	/* muxReg */
    5,                                              	/* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_GDOE,                   /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_GDOE_PS(2) |        	    /* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_EPDC_GDOE_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_EPDC_GDOE_HYS_MASK,
    GPIO2,                                          	/* base */
    26                                              	/* pin */
};
gpio_init_config_t Led_CynexoRGBLed_Red = {
    .pin           = 26, //pin number
    .direction     = gpioDigitalOutput,
    .interruptMode = gpioNoIntmode
};

/* LED CynexoRGBLed_Blue
 * SODIMM                BALL NAME                GPIO                ALT
 *    136                LCD_DAT18                GPI02_28            5
 */
gpio_config_t gpioLed_CynexoRGBLed_Blue = {
    "CynexoRGBLed: Blue",                               /* name */
    &IOMUXC_SW_MUX_CTL_PAD_LCD_DATA18,               	/* muxReg */
    5,                                              	/* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_LCD_DATA18,                   /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_LCD_DATA18_PS(2) |        	    /* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_LCD_DATA18_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_LCD_DATA18_HYS_MASK,
    GPIO2,                                          	/* base */
    28                                              	/* pin */
};
gpio_init_config_t Led_CynexoRGBLed_Blue = {
    .pin           = 28, //pin number
    .direction     = gpioDigitalOutput,
    .interruptMode = gpioNoIntmode
};

////////////////////////////////////////////////////////////

void configure_gpio_pin(gpio_config_t *config){
    assert(config);
    *(config->muxReg) = config->muxConfig;
    *(config->padReg) = config->padConfig;
}
