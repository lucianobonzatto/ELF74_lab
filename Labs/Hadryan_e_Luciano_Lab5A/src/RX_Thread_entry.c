#include "RX_Thread.h"
#include "obj_define.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);

/* RX_Thread entry function */
void RX_Thread_entry(void)
{
    /* TODO: add your own code here */
    initialise_monitor_handles();
    tx_thread_sleep (50);

    UINT status = 0;
    ULONG msg = 0;

    while (1)
    {
        status = tx_queue_receive(&queue0, &msg, TX_WAIT_FOREVER);
        tx_thread_sleep (5);
        printf("%d receiver msg -> %ld\n", status, msg);
    }
}
