#include "gpio_pins.h"
#include "board.h"

void hardware_init(void){
    /* Board specific RDC settings */
    BOARD_RdcInit();
    /* Board specific clock settings */
    BOARD_ClockInit();
    /* initialize debug uart */
    dbg_uart_init();

    /* In this demo, we need to grasp board GPT exclusively */
    RDC_SetPdapAccess(RDC, BOARD_GPTA_RDC_PDAP, 3 << (BOARD_DOMAIN_ID * 2), false, false);

    /* In this demo, we need to access RDC SEMAPHORE1 on this board */
    RDC_SetPdapAccess(RDC, rdcPdapSemaphore1, 0xFF, false, false);

    /* In this demo, we need to share board GPIO, we can set sreq argument to true
     * when the peer core could also access GPIO with RDC_SEMAPHORE, or the peer
     * core doesn't access the GPIO at all */
    RDC_SetPdapAccess(RDC, BOARD_GPIO_KEY_RDC_PDAP, 0xFF, false/*true*/, false);

    /* Enable PLL PFD0 for GPTA */
    CCM_ControlGate(CCM, ccmPllGateSys, ccmClockNeededRunWait);
    CCM_ControlGate(CCM, ccmPllGatePfd0, ccmClockNeededRunWait);

    /* Select GPTA clock derived from PLL PFD0 */
    CCM_UpdateRoot(CCM, BOARD_GPTA_CCM_ROOT, ccmRootmuxGptSysPllPfd0, 0, 0);
    /* Enable clock used by GPTA */
    CCM_EnableRoot(CCM, BOARD_GPTA_CCM_ROOT);
    CCM_ControlGate(CCM, BOARD_GPTA_CCM_CCGR, ccmClockNeededRunWait);

    /* Enable RDC SEMAPHORE GATE needed in this demo */
    CCM_ControlGate(CCM, ccmCcgrGateSema1, ccmClockNeededRunWait);

    /* Enable gpio clock gate, led and key share same CCGR on this board */
    CCM_ControlGate(CCM, BOARD_GPIO_KEY_CCM_CCGR, ccmClockNeededRunWait);

    /* Configure gpio pin IOMUX */
    configure_gpio_pin(BOARD_GPIO_KEY_CONFIG);
}
