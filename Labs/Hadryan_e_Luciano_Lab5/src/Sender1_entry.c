#include "Sender1.h"
#include "obj_define.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);
extern void setLeds(bsp_leds_t leds, ioport_level_t level, int id);

/* Sender1 entry function */
void Sender1_entry(void)
{
    /* TODO: add your own code here */
    initialise_monitor_handles();

    bsp_leds_t leds;
    R_BSP_LedsGet(&leds);
    g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_LOW);
    UINT status = 0;
    ULONG msg = 0;
    while (1)
    {
        status = tx_queue_send(&queue0, &msg, TX_WAIT_FOREVER);
        printf("%d sender 1 msg -> %ld\n", status, msg);
        tx_thread_sleep (40);
        msg++;
    }
}
