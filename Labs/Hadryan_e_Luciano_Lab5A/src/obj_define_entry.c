#include "obj_define.h"
#include <stdio.h>

/* obj_define entry function */
void obj_define_entry(void)
{
    /* TODO: add your own code here */

    /*bsp_leds_t leds;
    ioport_level_t level = IOPORT_LEVEL_HIGH;
    R_BSP_LedsGet(&leds);

    for(uint32_t i = 0; i < leds.led_count; i++) {
        g_ioport.p_api->pinWrite(leds.p_leds[i], IOPORT_LEVEL_HIGH);
    }*/

    while (1)
    {
        /* Determine the next state of the LEDs */
        /*if(IOPORT_LEVEL_LOW == level)
            level = IOPORT_LEVEL_HIGH;
        else
            level = IOPORT_LEVEL_LOW;

        //g_ioport.p_api->pinWrite(leds.p_leds[0], level);
        tx_thread_sleep (50);

        //g_ioport.p_api->pinWrite(leds.p_leds[1], level);
        tx_thread_sleep (50);

        //g_ioport.p_api->pinWrite(leds.p_leds[2], level);*/
        tx_thread_sleep (50);
    }
}
