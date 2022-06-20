/* generated thread source file - do not edit */
#include "Controle_saida.h"

TX_THREAD Controle_saida;
void Controle_saida_create(void);
static void Controle_saida_func(ULONG thread_input);
static uint8_t Controle_saida_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.Controle_saida") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE saida_queue;
static uint8_t queue_memory_saida_queue[200];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void Controle_saida_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_saida_queue;
    err_saida_queue = tx_queue_create (&saida_queue, (CHAR*) "Saida queue", 1, &queue_memory_saida_queue,
                                       sizeof(queue_memory_saida_queue));
    if (TX_SUCCESS != err_saida_queue)
    {
        tx_startup_err_callback (&saida_queue, 0);
    }

    UINT err;
    err = tx_thread_create (&Controle_saida, (CHAR*) "Controle de saida", Controle_saida_func, (ULONG) NULL,
                            &Controle_saida_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&Controle_saida, 0);
    }
}

static void Controle_saida_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    Controle_saida_entry ();
}
