#include "Sender2.h"
#include "obj_define.h"
#include <stdio.h>
//#include "tx_api.h"

extern void initialise_monitor_handles(void);
extern void setLeds(bsp_leds_t leds, ioport_level_t level, int id);

/* Sender2 entry function */
void Sender2_entry(void)
{
    /* TODO: add your own code here */
    initialise_monitor_handles();

    bsp_leds_t leds;
    R_BSP_LedsGet(&leds);
    g_ioport.p_api->pinWrite(leds.p_leds[1], IOPORT_LEVEL_LOW);
    UINT status = 0;
    ULONG msg = 0;
    while (1)
    {
        printf("%d sender 2 msg -> %ld\n", status, msg);
        status = tx_queue_send(&queue0, &msg, TX_WAIT_FOREVER);
        tx_thread_sleep (60);
        msg++;
    }
}
