#include "thread_1.h"

#include "globals.h"

/* thread_1 entry function */
void thread_1_entry(void)
{
    /* TODO: add your own code here */
    UINT status;

    while (1)
    {
        /* Increment the thread counter.  */
        thread_1_counter++;

        /* Send message to queue 0.  */
        status =  tx_queue_send(&queue_0, &thread_1_messages_sent, TX_WAIT_FOREVER);

        /* Check completion status.  */
        if (status != TX_SUCCESS)
            break;

        /* Increment the message sent.  */
        thread_1_messages_sent++;
    }
}
