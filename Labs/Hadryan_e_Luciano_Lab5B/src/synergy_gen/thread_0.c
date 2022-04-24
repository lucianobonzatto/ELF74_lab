/* generated thread source file - do not edit */
#include "thread_0.h"

TX_THREAD thread_0;
void thread_0_create(void);
static void thread_0_func(ULONG thread_input);
static uint8_t thread_0_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.thread_0") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE queue_0;
static uint8_t queue_memory_queue_0[100];
TX_SEMAPHORE semaphore_0;
TX_EVENT_FLAGS_GROUP event_flags_0;
TX_MUTEX mutex_0;
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void thread_0_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_queue_0;
    err_queue_0 = tx_queue_create (&queue_0, (CHAR*) "queue 0", 1, &queue_memory_queue_0, sizeof(queue_memory_queue_0));
    if (TX_SUCCESS != err_queue_0)
    {
        tx_startup_err_callback (&queue_0, 0);
    }
    UINT err_semaphore_0;
    err_semaphore_0 = tx_semaphore_create (&semaphore_0, (CHAR*) "semaphore 0", 0);
    if (TX_SUCCESS != err_semaphore_0)
    {
        tx_startup_err_callback (&semaphore_0, 0);
    }
    UINT err_event_flags_0;
    err_event_flags_0 = tx_event_flags_create (&event_flags_0, (CHAR*) "event flags 0");
    if (TX_SUCCESS != err_event_flags_0)
    {
        tx_startup_err_callback (&event_flags_0, 0);
    }
    UINT err_mutex_0;
    err_mutex_0 = tx_mutex_create (&mutex_0, (CHAR*) "mutex 0", TX_NO_INHERIT);
    if (TX_SUCCESS != err_mutex_0)
    {
        tx_startup_err_callback (&mutex_0, 0);
    }

    UINT err;
    err = tx_thread_create (&thread_0, (CHAR*) "thread_0", thread_0_func, (ULONG) NULL, &thread_0_stack, 1024, 1, 1, 1,
                            TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&thread_0, 0);
    }
}

static void thread_0_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    thread_0_entry ();
}
