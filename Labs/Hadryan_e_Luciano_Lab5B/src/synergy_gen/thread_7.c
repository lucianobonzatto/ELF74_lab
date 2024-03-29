/* generated thread source file - do not edit */
#include "thread_7.h"

TX_THREAD thread_7;
void thread_7_create(void);
static void thread_7_func(ULONG thread_input);
static uint8_t thread_7_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.thread_7") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void thread_7_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */

    UINT err;
    err = tx_thread_create (&thread_7, (CHAR*) "thread 7", thread_7_func, (ULONG) NULL, &thread_7_stack, 1024, 8, 8, 0,
                            TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&thread_7, 0);
    }
}

static void thread_7_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    thread_7_entry ();
}
