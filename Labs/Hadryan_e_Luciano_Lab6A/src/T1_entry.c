#include <T1.h>
#include "globals.h"

/* thread_0 entry function */
void thread_0_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        setLeds(100, 0);
        tx_thread_sleep (1);
    }
}
