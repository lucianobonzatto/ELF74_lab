#include "thread_0.h"
#include "thread_6.h"
#include "define_var.c"

/* thread_6 entry function */
void thread_6_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
