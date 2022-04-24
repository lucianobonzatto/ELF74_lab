#include "thread_0.h"
#include "thread_4.h"
#include "define_var.c"

/* thread_4 entry function */
void thread_4_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
