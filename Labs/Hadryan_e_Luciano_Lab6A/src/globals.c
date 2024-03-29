#include "globals.h"
#include "hal_data.h"
#include "tx_api.h"

void setLeds(int numIteracoes, int id){
    bsp_leds_t leds;
    R_BSP_LedsGet(&leds);

    for(int i=0; i<numIteracoes; i++){

        g_ioport.p_api->pinWrite(leds.p_leds[id], IOPORT_LEVEL_LOW);
        //tx_thread_sleep (5);


        for(uint32_t i = 0; i < leds.led_count; i++) {
            g_ioport.p_api->pinWrite(leds.p_leds[i], IOPORT_LEVEL_HIGH);
        }
        //tx_thread_sleep (5);
    }

}
