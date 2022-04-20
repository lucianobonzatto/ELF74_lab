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
    tx_thread_sleep (50);

    bsp_leds_t leds;
    UINT status = 0;
    ULONG msg = 0;
    R_BSP_LedsGet(&leds);
    g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_HIGH);

    while (1)
    {
        status = tx_mutex_get(&mutex0, 30);                             //Get ownership of mutex
        while(status != 0){
            status = tx_mutex_get(&mutex0, 30);                         //Get ownership of mutex
        }

        g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_LOW);

        status = tx_queue_send(&queue0, &msg, TX_WAIT_FOREVER);         //Send message to message queue
        printf("%d sender 1 msg -> %ld\n", status, msg);
        tx_thread_sleep (40);
        msg++;

        g_ioport.p_api->pinWrite(leds.p_leds[0], IOPORT_LEVEL_HIGH);

        status = tx_mutex_put(&mutex0);                                 //Release ownership of mutex
    }
}
