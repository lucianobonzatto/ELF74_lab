#include "thread_3.h"
#include "globals.h"

/* Thread 3 entry function */
void thread_3_entry(void)
{
    //tempo da funcao: 0,09983s, 100ms
    //executa em 800ms
    //a cada 4s -> 4000ms-800ms = 700ms -> 3200ticks
    while(1){
        setLeds(8, 2);
        tx_thread_sleep (320);
    }
}
