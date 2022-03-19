/******************************
 * @file   hal_entry.cpp
 * @brief  lab2 embarcados
 * @date   03/10/2022
 * @author Hadryan Salles
 *         Luciano Bonzatto
 ******************************/

#include "hal_data.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);

void setLeds(bsp_leds_t leds, ioport_level_t level);

volatile int timerSet = 0;
volatile int switchSet = 0;

void timerCallback(timer_callback_args_t *p_args) {
    (void) p_args;
    timerSet = 1;
}

void switchCallback(external_irq_callback_args_t *p_args) {
    (void) p_args;
    switchSet = 1;
}

void setLeds(bsp_leds_t leds, ioport_level_t level) {
    for(uint32_t i = 0; i < leds.led_count; i++) {
        g_ioport.p_api->pinWrite(leds.p_leds[i], level);
    }
}

void hal_entry(void) {
    initialise_monitor_handles();

    bsp_leds_t leds;
	R_BSP_LedsGet(&leds);

    // setup timer interruption
    g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);
    g_timer0.p_api->reset(g_timer0.p_ctrl);
    // setup switch button interruption
    g_external_irq0.p_api->open(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);

    while(1) {
        // set leds off
        setLeds(leds, IOPORT_LEVEL_HIGH);

        // wait initial second
        timerSet = 0;
        g_timer0.p_api->periodSet(g_timer0.p_ctrl, 1, TIMER_UNIT_PERIOD_SEC);
        g_timer0.p_api->start(g_timer0.p_ctrl);
        while(!timerSet)
        {}

        // set leds on
        setLeds(leds, IOPORT_LEVEL_LOW);

        // start 3 seconds second
        timerSet = 0;
        switchSet = 0;
        g_timer0.p_api->periodSet(g_timer0.p_ctrl, 3, TIMER_UNIT_PERIOD_SEC);
        g_timer0.p_api->start(g_timer0.p_ctrl);

        printf("GO!\n");
        while(!switchSet)
        {}

        if(timerSet) {
            printf("You lose\n");
        } else {
            unsigned long int timeCount;
            g_timer0.p_api->counterGet(g_timer0.p_ctrl, &timeCount);
            printf("You won! Your reaction time: %lf s\n", (float)timeCount/120000000.0f);
            break;
        }
    }
}
