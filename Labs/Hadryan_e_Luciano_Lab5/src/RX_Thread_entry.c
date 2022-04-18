#include "RX_Thread.h"
#include "obj_define.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);

/* RX_Thread entry function */
void RX_Thread_entry(void)
{
    /* TODO: add your own code here */
    initialise_monitor_handles();

    bsp_leds_t leds;
    R_BSP_LedsGet(&leds);

    UINT status = 0;
    ULONG msg;

    while (1)
    {
        status = tx_queue_receive(&queue0, &msg, TX_WAIT_FOREVER);
        tx_thread_sleep (40);
        printf("%d receiver msg -> %ld\n", status, msg);
    }
}
