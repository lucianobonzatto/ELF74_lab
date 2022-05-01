#include "thread_0.h"

#include "globals.h"

/* thread_0 entry function */
void thread_0_entry(void)
{
    /* TODO: add your own code here */
    UINT status;

    while (1)
    {
        thread_0_counter++;

        tx_thread_sleep (10);

        status =  tx_event_flags_set(&event_flags_0, 0x1, TX_OR);

        if (status != TX_SUCCESS)
            break;
    }
}
