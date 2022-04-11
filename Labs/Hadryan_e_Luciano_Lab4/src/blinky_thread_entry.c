/**
 * @file blinky_thread_entry.c
 * @date 11/04/2022
 * @authors Hadryan Salles and Luciano Bonzatto
 */

#include "blinky_thread.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);

#define SUCCESS_MSG "success"
#define TO_MSG "time out"
#define ERROR_MSG "other error"
#define BUFFER_SIZE 50

const char* error_message(ssp_err_t err) {
    if (err == 0) {
        return SUCCESS_MSG;
    } else if(err == 20) {
        return TO_MSG;
    }
    else {
        return ERROR_MSG;
    }
}

/*******************************************************************************************************************//**
 * @brief  Blinky example application
 *
 * Blinks all leds at a rate of 1 second using the the threadx sleep function.
 * Only references two other modules including the BSP, IOPORT.
 *
 **********************************************************************************************************************/
void blinky_thread_entry(void)
{
    initialise_monitor_handles();
    /* Define the units to be used with the threadx sleep function */
	const uint32_t threadx_tick_rate_Hz = 100;
    /* Set the blink frequency (must be <= threadx_tick_rate_Hz */
    const uint32_t freq_in_hz = 2;
    /* Calculate the delay in terms of the threadx tick rate */
    const uint32_t delay = threadx_tick_rate_Hz/freq_in_hz;
    /* LED type structure */
    bsp_leds_t leds;
    /* LED state variable */
    ioport_level_t level = IOPORT_LEVEL_HIGH;

    /* Get LED information for this board */
    R_BSP_LedsGet(&leds);

    /* If this board has no leds then trap here */
    if (0 == leds.led_count)
    {
        while(1);   // There are no leds on this board
    }

    int32_t i = 0;
    const char* str;
    uint8_t tx_data[BUFFER_SIZE];
    uint8_t* tx_uart_data = (uint8_t*)"Lab5: Serial Comm over RS-232";
    unsigned char in_buffer[BUFFER_SIZE];

    while (1)
    {
        /* Determine the next state of the LEDs */
        if(IOPORT_LEVEL_LOW == level)
        {
            level = IOPORT_LEVEL_HIGH;
        }
        else
        {
            level = IOPORT_LEVEL_LOW;
        }

        /* Update all board LEDs */
        for(uint32_t ii = 0; ii < leds.led_count; ii++)
        {
            g_ioport.p_api->pinWrite(leds.p_leds[ii], level);
        }

        sprintf((char*)tx_data, "%s %4ld\r\n", tx_uart_data, i++);
        ssp_err_t err = g_sf_comms0.p_api->write(g_sf_comms0.p_ctrl, tx_data, strlen((char*)tx_data)+1, TX_WAIT_FOREVER);
        str = error_message(err);
        printf("[TX]\n\treturn_code: %d\n\treturn_message: %s\n\tsent_buffer: %s", err, str, tx_data);

        err = g_sf_comms0.p_api->read(g_sf_comms0.p_ctrl, in_buffer, sizeof(in_buffer), 100);
        str = error_message(err);
        printf("[RX]\n\treturn_code: %d\n\treturn_message: %s\n\treceived_buffer: %s", err, str, in_buffer);
        printf("--------\n");

        /* Delay */
        tx_thread_sleep (delay);
    }
}
