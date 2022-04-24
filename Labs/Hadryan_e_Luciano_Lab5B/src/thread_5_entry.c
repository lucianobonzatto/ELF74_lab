#include "thread_0.h"
#include "thread_5.h"
#include "define_var.c"

/* thread_5 entry function */
void thread_5_entry(void)
{
    /* TODO: add your own code here */

    UINT    status;
    ULONG   actual_flags;

    /* This thread simply waits for an event in a forever loop.  */
    while(1)
    {

        /* Increment the thread counter.  */
        thread_5_counter++;

        /* Wait for event flag 0.  */
        status =  tx_event_flags_get(&event_flags_0, 0x1, TX_OR_CLEAR,
                                                &actual_flags, TX_WAIT_FOREVER);

        /* Check status.  */
        if ((status != TX_SUCCESS) || (actual_flags != 0x1))
            break;
    }
}
