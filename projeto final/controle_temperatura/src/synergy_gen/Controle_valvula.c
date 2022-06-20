/* generated thread source file - do not edit */
#include "Controle_valvula.h"

TX_THREAD Controle_valvula;
void Controle_valvula_create(void);
static void Controle_valvula_func(ULONG thread_input);
static uint8_t Controle_valvula_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.Controle_valvula") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE valvula_queue;
static uint8_t queue_memory_valvula_queue[200];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void Controle_valvula_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_valvula_queue;
    err_valvula_queue = tx_queue_create (&valvula_queue, (CHAR*) "Valvula queue", 2, &queue_memory_valvula_queue,
                                         sizeof(queue_memory_valvula_queue));
    if (TX_SUCCESS != err_valvula_queue)
    {
        tx_startup_err_callback (&valvula_queue, 0);
    }

    UINT err;
    err = tx_thread_create (&Controle_valvula, (CHAR*) "Controle de valvula", Controle_valvula_func, (ULONG) NULL,
                            &Controle_valvula_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&Controle_valvula, 0);
    }
}

static void Controle_valvula_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    Controle_valvula_entry ();
}
