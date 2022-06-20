#include <Controle_valvula.h>
#include <lcd_thread.h>

/* Controle de valvula entry function */
void Controle_valvula_entry(void)
{
    ULONG msg[2], msg_out[2];

    while (1)
    {
        tx_queue_receive(&valvula_queue, msg, TX_WAIT_FOREVER);
        //tx_queue_send(&lcd_in_queue, msg, TX_WAIT_FOREVER);


        msg_out[0] = 7;
        msg_out[1] = (ULONG)(msg[0]);   //fria
        tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
        msg_out[0] = 6;
        msg_out[1] = (ULONG)(msg[1]);    //quente
        tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);

        tx_thread_sleep (1);
    }
}
