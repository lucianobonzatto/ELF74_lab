/*
 * globals.c
 *
 *  Created on: 2 de mai de 2022
 *      Author: lucia
 */
#include "globals.h"

void setLeds(int numIteracoes, int id) {

    bsp_leds_t leds;

    for(int i = 0; i< numIteracoes; i++){
        for(uint32_t i = 0; i < leds.led_count; i++) {
            g_ioport.p_api->pinWrite(leds.p_leds[i], IOPORT_LEVEL_HIGH);
        }
        tx_thread_sleep (1);

        g_ioport.p_api->pinWrite(leds.p_leds[id], IOPORT_LEVEL_LOW);
        tx_thread_sleep (1);
    }
}
