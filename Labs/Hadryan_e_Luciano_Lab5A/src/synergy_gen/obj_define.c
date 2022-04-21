/* generated thread source file - do not edit */
#include "obj_define.h"

TX_THREAD obj_define;
void obj_define_create(void);
static void obj_define_func(ULONG thread_input);
static uint8_t obj_define_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.obj_define") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_MUTEX mutex0;
TX_QUEUE queue0;
static uint8_t queue_memory_queue0[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void obj_define_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_mutex0;
    err_mutex0 = tx_mutex_create (&mutex0, (CHAR*) "mutex0", TX_NO_INHERIT);
    if (TX_SUCCESS != err_mutex0)
    {
        tx_startup_err_callback (&mutex0, 0);
    }
    UINT err_queue0;
    err_queue0 = tx_queue_create (&queue0, (CHAR*) "queue0", 1, &queue_memory_queue0, sizeof(queue_memory_queue0));
    if (TX_SUCCESS != err_queue0)
    {
        tx_startup_err_callback (&queue0, 0);
    }

    UINT err;
    err = tx_thread_create (&obj_define, (CHAR*) "obj_define", obj_define_func, (ULONG) NULL, &obj_define_stack, 1024,
                            1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&obj_define, 0);
    }
}

static void obj_define_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    obj_define_entry ();
}
