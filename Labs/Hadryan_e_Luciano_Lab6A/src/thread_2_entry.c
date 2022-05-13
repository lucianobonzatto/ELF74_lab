#include "thread_2.h"
#include "globals.h"

/* Thread 2 entry function */
void thread_2_entry(void)
{
    //tempo da funcao: 0,09983s, 100ms
    //executa em 500ms
    //a cada 1,5s -> 1500ms-500ms = 1000ms -> 100ticks
    while(1){
        setLeds(5, 1);
        tx_thread_sleep (100);
    }
}
