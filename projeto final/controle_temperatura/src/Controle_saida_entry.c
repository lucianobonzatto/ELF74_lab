#include <Controle_saida.h>
#include <lcd_thread.h>

#define SAIDA_PES_FECHA 1
#define SAIDA_PES_ABRE 2
#define SAIDA_PAINEL_FECHA 3
#define SAIDA_PAINEL_ABRE 4
#define SAIDA_VIDRO_FECHA 5
#define SAIDA_VIDRO_ABRE 6
#define VENTILACAO_INC 7
#define VENTILACAO_DEC 8
#define RUN 12
#define STOP 13

extern void initialise_monitor_handles(void);
/* Controle de saida entry function */
void Controle_saida_entry(void)
{
    UINT status = 0, vent = 1;
    ULONG msg = 0;
    ULONG msg_out[2];
    ULONG saidas[3];
    int running = 0;

    saidas[0] = 2;
    saidas[1] = 2;
    saidas[2] = 2;

    while (1)
    {
        status = tx_queue_receive(&saida_queue, &msg, TX_WAIT_FOREVER);
        if(status == 0){
            switch(msg){
                case RUN:
                    running = 1;
                    break;
                case STOP:
                    running = 0;
                    break;
                case SAIDA_PES_FECHA:
                    saidas[0] = 2;
                    break;
                case SAIDA_PES_ABRE:
                    saidas[0] = 3;
                    break;
                case SAIDA_PAINEL_FECHA:
                    saidas[1] = 2;
                    break;
                case SAIDA_PAINEL_ABRE:
                    saidas[1] = 3;
                    break;
                case SAIDA_VIDRO_FECHA:
                    saidas[2] = 2;
                    break;
                case SAIDA_VIDRO_ABRE:
                    saidas[2] = 3;
                    break;
                case VENTILACAO_INC:
                    vent++;
                    if(vent==6)
                        vent = 5;
                    msg_out[0] = 1;
                    msg_out[1] = vent;
                    tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
                    break;
                case VENTILACAO_DEC:
                    vent--;
                    if(vent==0)
                        vent = 1;
                    msg_out[0] = 1;
                    msg_out[1] = vent;
                    tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
                    break;
                case 31:
                case 32:
                case 33:
                case 34:
                case 35:
                    vent = msg-30;
                    msg_out[0] = 1;
                    msg_out[1] = vent;
                    tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
                    break;
                default:
                    break;
            }
        }

        if(running){
            msg_out[0] = saidas[0];
            msg_out[1] = 1;
            tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);

            msg_out[0] = saidas[1];
            msg_out[1] = 2;
            tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);

            msg_out[0] = saidas[2];
            msg_out[1] = 3;
            tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);

        }
        else{
            msg_out[0] = 2;
            msg_out[1] = 1;
            tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);

            msg_out[0] = 2;
            msg_out[1] = 2;
            tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);

            msg_out[0] = 2;
            msg_out[1] = 3;
            tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
        }

        //tx_thread_sleep (5);
    }
}
