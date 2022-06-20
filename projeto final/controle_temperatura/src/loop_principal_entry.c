#include <Controle_saida.h>
#include <Controle_valvula.h>
#include <lcd_thread.h>
#include <stdio.h>
#include "loop_principal.h"

#define SAIDA_PES_FECHA 1
#define SAIDA_PES_ABRE 2
#define SAIDA_PAINEL_FECHA 3
#define SAIDA_PAINEL_ABRE 4
#define SAIDA_VIDRO_FECHA 5
#define SAIDA_VIDRO_ABRE 6
#define VENTILACAO_INC 7
#define VENTILACAO_DEC 8
#define TEMPERATURA_INC 9
#define TEMPERATURA_DEC 10
#define UPDATE_INFO 11
#define RUN 12
#define STOP 13


extern void initialise_monitor_handles(void);
void tratamento_mensagem_lcd_out(ULONG msg);


float temp_desejada_buffer = 20;
ULONG saidas_buffer[3];
ULONG vent_buffer;

float temp_desejada = 20;
float temp_atual = 20;
float temp_alvo = 20;
int running = 0;
int timerOver;
int v_fria = 0, v_quente = 0;

void timer1Callback(timer_callback_args_t *p_args) {
    (void) p_args;
    timerOver = 1;
}

/* Loop principal entry function */
void loop_principal_entry(void)
{
    initialise_monitor_handles();
    UINT status = 0;
    ULONG msg = 0;
    ULONG msg_out[2];
    uint16_t adc_val;

    saidas_buffer[0] = 1;
    saidas_buffer[1] = 3;
    saidas_buffer[2] = 5;
    vent_buffer = 1;
    timerOver = 0;

    status = g_adc0.p_api->open(g_adc0.p_ctrl, g_adc0.p_cfg);
    //status = g_adc0.p_api->scanStatusGet(g_adc0.p_ctrl);
    status = g_adc0.p_api->scanCfg(g_adc0.p_ctrl, g_adc0.p_channel_cfg);
    status = g_adc0.p_api->scanStart(g_adc0.p_ctrl);

    g_timer1.p_api->open(g_timer1.p_ctrl, g_timer1.p_cfg);
    g_timer1.p_api->reset(g_timer1.p_ctrl);


    while (1)
    {
        status = g_adc0.p_api->read(g_adc0.p_ctrl, ADC_REG_CHANNEL_0, &adc_val);
        temp_atual = (float)((int)((0.02*adc_val+9.5)*10))/10;

        if((temp_atual < (temp_desejada+0.5))&&(temp_atual > (temp_desejada-0.5)))
            temp_alvo = temp_desejada;
        else if(temp_atual < temp_desejada)
            temp_alvo = temp_desejada + 2;
        else if(temp_atual > temp_desejada)
            temp_alvo = temp_desejada - 2;

        //temp_alvo = 16*msg_out[1]/100+30*msg_out[2]/100;
        v_fria = round(-6*(double)temp_alvo+293);         //valvula fria
        v_quente = round(6*(double)temp_alvo-90);         //valvula quente

        if(v_fria < 0)
            v_fria = 0;
        else if (v_fria > 100)
            v_fria = 100;

        if(v_quente < 0)
            v_quente = 0;
        else if (v_quente > 100)
            v_quente = 100;

        status = tx_queue_receive(&lcd_out_queue, &msg, 10);
        while(status == 0){
            tratamento_mensagem_lcd_out(msg);
            status = tx_queue_receive(&lcd_out_queue, &msg, 10);
        }

        if(timerOver){
            timerOver = 0;
            temp_desejada = temp_desejada_buffer;
            ULONG msg = saidas_buffer[0];
            status = tx_queue_send(&saida_queue, &msg, TX_WAIT_FOREVER);
            //printf("%d ->%d\n", status, saidas_buffer[0]);
            msg = saidas_buffer[1];
            status = tx_queue_send(&saida_queue, &msg, TX_WAIT_FOREVER);
            //printf("%d ->%d\n", status, saidas_buffer[1]);
            msg = saidas_buffer[2];
            status = tx_queue_send(&saida_queue, &msg, TX_WAIT_FOREVER);
            //printf("%d ->%d\n", status, saidas_buffer[2]);
            //printf("-------\n");
            msg = vent_buffer+30;
            status = tx_queue_send(&saida_queue, &msg, TX_WAIT_FOREVER);
        }

        if(running){
            msg_out[0] = (ULONG)v_fria;
            msg_out[1] = (ULONG)v_quente;
            tx_queue_send(&valvula_queue, msg_out, TX_WAIT_FOREVER);
        }
        else{
            msg_out[0] = (ULONG)0;
            msg_out[1] = (ULONG)0;
            tx_queue_send(&valvula_queue, msg_out, TX_WAIT_FOREVER);
        }
    }
    status = g_adc0.p_api->scanStop(g_adc0.p_ctrl);
}

void tratamento_mensagem_lcd_out(ULONG msg){
    ULONG msg_out[2];
    if(msg <= 2){
        g_timer1.p_api->reset(g_timer1.p_ctrl);
        saidas_buffer[0] = msg;
    }
    else if(msg <= 4){
        g_timer1.p_api->reset(g_timer1.p_ctrl);
        saidas_buffer[1] = msg;
    }
    else if(msg <= 6){
        g_timer1.p_api->reset(g_timer1.p_ctrl);
        saidas_buffer[2] = msg;
    }
    else if(msg == VENTILACAO_INC){
        vent_buffer++;
        if(vent_buffer==6)
            vent_buffer = 5;
        g_timer1.p_api->reset(g_timer1.p_ctrl);
    }
    else if(msg == VENTILACAO_DEC){
        vent_buffer--;
        if(vent_buffer==0)
            vent_buffer = 1;
        g_timer1.p_api->reset(g_timer1.p_ctrl);
    }
    else if(msg == TEMPERATURA_INC){
        g_timer1.p_api->reset(g_timer1.p_ctrl);
        temp_desejada_buffer += (float)0.5;
        if(temp_desejada_buffer > 30)
            temp_desejada_buffer=30;
    }
    else if(msg == TEMPERATURA_DEC){
        g_timer1.p_api->reset(g_timer1.p_ctrl);
        temp_desejada_buffer -= (float)0.5;
        if(temp_desejada_buffer < 16)
            temp_desejada_buffer =16;
    }
    else if(msg == UPDATE_INFO){
        msg_out[0] = 5;
        msg_out[1] = (ULONG)(temp_atual*10);
        tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
        msg_out[0] = 9;
        msg_out[1] = (ULONG)(temp_alvo*10);
        tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
        msg_out[0] = 4;
        msg_out[1] = (ULONG)(temp_desejada*10);
        tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
    }
    else if(msg == RUN){
        tx_queue_send(&saida_queue, &msg, TX_WAIT_FOREVER);
        running = 1;
        msg_out[0] = 8;
        msg_out[1] = 1;
        tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
    }
    else if(msg == STOP){
        tx_queue_send(&saida_queue, &msg, TX_WAIT_FOREVER);
        running = 0;
        msg_out[0] = 8;
        msg_out[1] = 0;
        tx_queue_send(&lcd_in_queue, msg_out, TX_WAIT_FOREVER);
    }
}
