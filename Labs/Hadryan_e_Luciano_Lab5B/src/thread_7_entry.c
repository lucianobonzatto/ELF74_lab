#include "thread_0.h"
#include "thread_7.h"
#include "define_var.c"

/* thread_7 entry function */
void thread_7_entry(void)
{
    /* TODO: add your own code here */
    while (1)
    {
        tx_thread_sleep (1);
    }
}
