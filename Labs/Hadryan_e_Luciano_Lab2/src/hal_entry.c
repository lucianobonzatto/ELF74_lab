/***********************************************************************************************************************
 * Copyright [2015-2021] Renesas Electronics Corporation and/or its licensors. All Rights Reserved.
 * 
 * This file is part of Renesas SynergyTM Software Package (SSP)
 *
 * The contents of this file (the "contents") are proprietary and confidential to Renesas Electronics Corporation
 * and/or its licensors ("Renesas") and subject to statutory and contractual protections.
 *
 * This file is subject to a Renesas SSP license agreement. Unless otherwise agreed in an SSP license agreement with
 * Renesas: 1) you may not use, copy, modify, distribute, display, or perform the contents; 2) you may not use any name
 * or mark of Renesas for advertising or publicity purposes or in connection with your use of the contents; 3) RENESAS
 * MAKES NO WARRANTY OR REPRESENTATIONS ABOUT THE SUITABILITY OF THE CONTENTS FOR ANY PURPOSE; THE CONTENTS ARE PROVIDED
 * "AS IS" WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, AND NON-INFRINGEMENT; AND 4) RENESAS SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING DAMAGES RESULTING FROM LOSS OF USE, DATA, OR PROJECTS, WHETHER IN AN ACTION OF
 * CONTRACT OR TORT, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE CONTENTS. Third-party contents
 * included in this file may be subject to different terms.
 **********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : hal_entry.c
* Description  : This is a very simple example application that blinks all LEDs on a board.
***********************************************************************************************************************/

#include "hal_data.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);

void setLeds(bsp_leds_t leds, ioport_level_t level);

volatile int timerSet = 0;
volatile int switchSet = 0;

void timerCallback(timer_callback_args_t *p_args) {
    (void) p_args;
    timerSet = 1;
    printf("Timer Set\n");
}

void switchCallback(external_irq_callback_args_t *p_args) {
    (void) p_args;
    switchSet = 1;
    printf("Switch Set\n");
}

void setLeds(bsp_leds_t leds, ioport_level_t level) {
    for(uint32_t i = 0; i < leds.led_count; i++)
    {
        g_ioport.p_api->pinWrite(leds.p_leds[i], level);
    }
}

/*******************************************************************************************************************//**
 * @brief  Blinky example application
 *
 * Blinks all leds at a rate of 1 second using the software delay function provided by the BSP.
 * Only references two other modules including the BSP, IOPORT.
 *
 **********************************************************************************************************************/
void hal_entry(void) {
    initialise_monitor_handles();

	// const bsp_delay_units_t bsp_delay_units = BSP_DELAY_UNITS_MILLISECONDS;
	// const uint32_t freq_in_hz = 1;
	// const uint32_t delay = bsp_delay_units/freq_in_hz;
    // R_BSP_SoftwareDelay(delay, bsp_delay_units);

    bsp_leds_t leds;
	R_BSP_LedsGet(&leds);

    // setup timer interruption
    g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);
    g_timer0.p_api->reset(g_timer0.p_ctrl);
    // setup switch button interruption
    g_external_irq0.p_api->open(g_external_irq0.p_ctrl, g_external_irq0.p_cfg);

    setLeds(leds, IOPORT_LEVEL_HIGH);

    printf("Starting the game...\n");

    // wait initial second
    while(!timerSet)
    {}

    setLeds(leds, IOPORT_LEVEL_LOW);

    // start timer to 3 seconds
    g_timer0.p_api->periodSet(g_timer0.p_ctrl, 3, TIMER_UNIT_PERIOD_SEC);
    g_timer0.p_api->start(g_timer0.p_ctrl);
    timerSet = 0;

    while(!timerSet) {
        if(switchSet) {
            switchSet = 0;
            unsigned long int timeCount;
            g_timer0.p_api->counterGet(g_timer0.p_ctrl, &timeCount);
            printf("You win! Counter: %lf s\n", timeCount/120000000.0f);
        }
    }

    // R_BSP_SoftwareDelay(delay, bsp_delay_units);
}
