#include "thread_0.h"
#include "thread_3.h"
#include "define_var.c"

/* thread_3 entry function */
void thread_3_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
