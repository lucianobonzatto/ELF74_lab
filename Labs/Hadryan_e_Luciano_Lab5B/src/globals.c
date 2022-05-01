#include "globals.h"

ULONG thread_0_counter;

ULONG thread_1_counter;
ULONG thread_1_messages_sent;

ULONG thread_2_counter;
ULONG thread_2_messages_received;

ULONG thread_3_counter;

ULONG thread_4_counter;

ULONG thread_5_counter;

ULONG thread_6_counter;

ULONG thread_7_counter;

void thread_3_and_4_entry(ULONG thread_input) {
  UINT    status;

    /* This function is executed from thread 3 and thread 4.  As the loop
       below shows, these function compete for ownership of semaphore_0.  */
    while(1)
    {

        /* Increment the thread counter.  */
        if (thread_input == 3)
            thread_3_counter++;
        else
            thread_4_counter++;

        /* Get the semaphore with suspension.  */
        status =  tx_semaphore_get(&semaphore_0, TX_WAIT_FOREVER);

        /* Check status.  */
        if (status != TX_SUCCESS)
            break;

        /* Sleep for 2 ticks to hold the semaphore.  */
        tx_thread_sleep(2);

        /* Release the semaphore.  */
        status =  tx_semaphore_put(&semaphore_0);

        /* Check status.  */
        if (status != TX_SUCCESS)
            break;
    }

}

void thread_6_and_7_entry(ULONG thread_input) {
  UINT    status;

  /* This function is executed from thread 6 and thread 7.  As the loop
      below shows, these function compete for ownership of mutex_0.  */
  while(1)
  {

      /* Increment the thread counter.  */
      if (thread_input == 6)
          thread_6_counter++;
      else
          thread_7_counter++;

      /* Get the mutex with suspension.  */
      status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

      /* Check status.  */
      if (status != TX_SUCCESS)
          break;

      /* Get the mutex again with suspension.  This shows
          that an owning thread may retrieve the mutex it
          owns multiple times.  */
      status =  tx_mutex_get(&mutex_0, TX_WAIT_FOREVER);

      /* Check status.  */
      if (status != TX_SUCCESS)
          break;

      /* Sleep for 2 ticks to hold the mutex.  */
      tx_thread_sleep(2);

      /* Release the mutex.  */
      status =  tx_mutex_put(&mutex_0);

      /* Check status.  */
      if (status != TX_SUCCESS)
          break;

      /* Release the mutex again.  This will actually 
          release ownership since it was obtained twice.  */
      status =  tx_mutex_put(&mutex_0);

      /* Check status.  */
      if (status != TX_SUCCESS)
          break;
  }
}