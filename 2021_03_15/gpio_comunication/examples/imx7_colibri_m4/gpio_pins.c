#include <assert.h>
#include "gpio_pins.h"
#include "board.h"
#include "gpio_imx.h"

////Cynexo board Specific////

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

/* LED CynexoRGBLed_Green
 * SODIMM                BALL NAME                GPIO                ALT
 *    190                SD1_CMD                  GPI05_04           5
 */
gpio_config_t gpioLed_CynexoRGBLed_Green = {
    "CynexoRGBLed: Green",                                       /* name */
    &IOMUXC_SW_MUX_CTL_PAD_SD1_CMD,               	/* muxReg */
    5,                                              	/* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_SD1_CMD,                  /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_PS(5) |        	/* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_SD1_CMD_HYS_MASK,
    GPIO5,                                          	/* base */
    4                                              	/* pin */
};
gpio_init_config_t Led_CynexoRGBLed_Green = {
    .pin           = 4, //pin number
    .direction     = gpioDigitalOutput,
    .interruptMode = gpioNoIntmode
};


////////////////////////////////////////////////////////////

void configure_gpio_pin(gpio_config_t *config){
    assert(config);
    *(config->muxReg) = config->muxConfig;
    *(config->padReg) = config->padConfig;
}
