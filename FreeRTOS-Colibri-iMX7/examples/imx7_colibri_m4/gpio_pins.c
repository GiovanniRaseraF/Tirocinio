#include <assert.h>
#include "gpio_pins.h"
#include "board.h"
#include "gpio_imx.h"

gpio_config_t gpioLed = {
    "EXT_IO0 LED",                      /* name */
    &IOMUXC_LPSR_SW_MUX_CTL_PAD_GPIO1_IO02,  /* muxReg */
    0,                                  /* muxConfig */
    &IOMUXC_LPSR_SW_PAD_CTL_PAD_GPIO1_IO02,  /* padReg */
    0,                                  /* padConfig */
    GPIO1,                              /* base */
    2                                   /* pin */
};

gpio_config_t gpioKeyFunc1 = {
    "EXT_IO1",                                      /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL,               /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL_PS(2) |        /* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL_HYS_MASK,
    GPIO2,                                          /* base */
    26                                              /* pin */
};

gpio_config_t gpioKeyFunc2 = {
    "EXT_IO2",                                       /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2,                  /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2_PS(2) |        /* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2_HYS_MASK,
    GPIO2,                                          /* base */
    22                                              /* pin */
};


/* Switch 1
 * SODIMM                BALL NAME                GPIO                ALT
 *    133                EPDC_GDRL           GPIO02_26                  5
 */
gpio_config_t gpioSwitch1 = {
    "SODIMM 133",                                      /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_GDRL,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL,               /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL_PS(2)  |        /* padConfig */
    	IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL_PE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_EPDC_GDRL_HYS_MASK,
    GPIO2,                                          /* base */
    26                                              /* pin */
};
gpio_init_config_t Switch1 = {
    .pin           = 26, //pin number
    .direction     = gpioDigitalInput,
    .interruptMode = gpioNoIntmode
};

/* LED 1
 * SODIMM                BALL NAME                GPIO                ALT
 *    127               EPDC_SDCE2           GPIO02_22                  5
 */
gpio_config_t gpioLed1 = {
    "SODIMM 127",                                       /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_SDCE2,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2,                  /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2_PS(2) |        /* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_EPDC_SDCE2_HYS_MASK,
    GPIO2,                                          /* base */
    22                                              /* pin */
};
gpio_init_config_t Led1 = {
    .pin           = 22, //pin number
    .direction     = gpioDigitalOutput,
    .interruptMode = gpioNoIntmode
};


/* Switch 2
 * SODIMM                BALL NAME                GPIO                ALT
 *    107                 EPDC_DATA15           GPIO02_15                  5
 */
gpio_config_t gpioSwitch2 = {
    "SODIMM 107",                                      /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA15,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA15,               /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA15_PS(2)  |        /* padConfig */
    	IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA15_PE_MASK |
    IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA15_HYS_MASK,
    GPIO2,                                          /* base */
    15                                              /* pin */
};
gpio_init_config_t Switch2 = {
    .pin           = 15, //pin number
    .direction     = gpioDigitalInput,
    .interruptMode = gpioNoIntmode
};

/* LED 2
 * SODIMM                BALL NAME                GPIO                ALT
 *    105                 EPDC_DATA10           GPIO02_10                  5
 */
gpio_config_t gpioLed2 = {
    "SODIMM 105",                                       /* name */
    &IOMUXC_SW_MUX_CTL_PAD_EPDC_DATA10,               /* muxReg */
    5,                                              /* muxConfig */
    &IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA10,                  /* padReg */
    IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA10_PS(2) |        /* padConfig */
        IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA10_PE_MASK |
	IOMUXC_SW_PAD_CTL_PAD_EPDC_DATA10_HYS_MASK,
    GPIO2,                                          /* base */
    10                                              /* pin */
};

gpio_init_config_t Led2 = {
    .pin           = 10, //pin number
    .direction     = gpioDigitalOutput,
    .interruptMode = gpioNoIntmode
};

void configure_gpio_pin(gpio_config_t *config)
{
    assert(config);

    *(config->muxReg) = config->muxConfig;
    *(config->padReg) = config->padConfig;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
