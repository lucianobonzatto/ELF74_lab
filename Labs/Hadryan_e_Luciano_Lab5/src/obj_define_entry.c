#include "obj_define.h"

void setLeds(bsp_leds_t leds, ioport_level_t level, int id);

void setLeds(bsp_leds_t leds, ioport_level_t level, int id) {
    if(id == -1){
        for(uint32_t i = 0; i < leds.led_count; i++) {
            g_ioport.p_api->pinWrite(leds.p_leds[i], level);
        }
    }
    else{
        g_ioport.p_api->pinWrite(leds.p_leds[id], level);
    }
}

/* obj_define entry function */
void obj_define_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
