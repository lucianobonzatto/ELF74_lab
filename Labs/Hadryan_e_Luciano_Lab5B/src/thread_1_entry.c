#include "thread_1.h"

/* thread_1 entry function */
void thread_1_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
