#include "thread_2.h"

#include "globals.h"

/* thread_2 entry function */
void thread_2_entry(void)
{
    /* TODO: add your own code here */
    ULONG   received_message;
    UINT    status;

    /* This thread retrieves messages placed on the queue by thread 1.  */
    while(1)
    {
        /* Increment the thread counter.  */
        thread_2_counter++;

        /* Retrieve a message from the queue.  */
        status = tx_queue_receive(&queue_0, &received_message, TX_WAIT_FOREVER);

        /* Check completion status and make sure the message is what we expected.  */
        if ((status != TX_SUCCESS) || (received_message != thread_2_messages_received))
            break;

        /* Otherwise, all is okay.  Increment the received message count.  */
        thread_2_messages_received++;
    }
}
