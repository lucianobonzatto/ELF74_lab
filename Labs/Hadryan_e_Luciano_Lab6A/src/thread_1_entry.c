#include "thread_1.h"
#include "globals.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);

/* Thread 1 entry function */
void thread_1_entry(void)
{
    initialise_monitor_handles();
    unsigned int err = 8, cont = 6;

    printf("inicio\n");

    //g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);
    //g_timer0.p_api->periodSet(g_timer0.p_ctrl, 1000, TIMER_UNIT_PERIOD_MSEC);

    //g_timer0.p_api->reset(g_timer0.p_ctrl);
    //g_timer0.p_api->start(g_timer0.p_ctrl);

    //tempo da funcao: 0,09983s, 100ms
    //executa em 300ms -> 3 iteracoes
    //a cada 1s -> 1000ms-300ms = 700ms -> 70ticks
    while(1){
        setLeds(3, 0);
        tx_thread_sleep (70);
    }

    //g_timer0.p_api->stop(g_timer0.p_ctrl);
    //err = g_timer0.p_api->counterGet(g_timer0.p_ctrl, &cont);
    //printf("%i -> %i\n", err, cont);
}
