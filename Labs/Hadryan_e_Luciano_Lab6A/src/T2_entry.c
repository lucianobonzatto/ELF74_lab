#include <T2.h>
#include "globals.h"

/* thread_1 entry function */
void thread_1_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        setLeds(100, 0);
        tx_thread_sleep (1);
    }
}
