/***********************************************************************************************************************
* File Name    : hal_entry.c
***********************************************************************************************************************/

#include "hal_data.h"
#include <stdio.h>

#define WIDTH0 4
#define HEIGTH0 3

extern void printMacros();
extern void initialise_monitor_handles();

extern uint16_t EightBitHistogram(uint16_t width, uint16_t height, const uint8_t * p_image, uint16_t * p_hist);

void hal_entry(void) {

    initialise_monitor_handles();

    uint16_t p_hist[256];

    uint8_t image0[HEIGTH0][WIDTH0] = {
          {20,16,16,18},
          {255,255,0,0},
          {32,32,32,32}
    };

    uint16_t err_ret;
    int j=0;
    while(j<256)
    {
        p_hist[j] = (uint16_t)1;
        j++;
    }

    err_ret = EightBitHistogram(WIDTH0, HEIGTH0, (unsigned char*)image0, p_hist);

    j=0;
    while(j<256)
    {
        printf("%i\tmt = %u\n", j, (unsigned int)p_hist[j]);
        j++;
    }
    printf("err_ret = %u\n", err_ret);
}
