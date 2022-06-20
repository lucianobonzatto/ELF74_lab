

#include <lcd_thread.h>
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"

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

void tratamento_evento(GX_WINDOW *widget, GX_EVENT *event_ptr);
void tratamento_mensagem_lcd_in(GX_WINDOW *widget, ULONG *msg);
static void update_numeric_prompt_value(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT value);
static void update_prompt_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);
static void update_button_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);

int vent = 0;

UINT window1_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);
    tratamento_evento(widget, event_ptr);

//    status = tx_queue_receive(&lcd_in_queue, msg, 5);
//    while(status == 0){
//        tratamento_mensagem_lcd_in(widget, msg);
//        status = tx_queue_receive(&lcd_in_queue, msg, 5);
//    }

    return result;
}

void tratamento_mensagem_lcd_in(GX_WINDOW *widget, ULONG *msg){
    ULONG var_aux;
    switch(msg[0]){
        case(1):
            update_numeric_prompt_value(widget, ID_VENT_DISPLAY, (INT)msg[1]);
            break;
        case(2):
            if(msg[1]==1)
                update_prompt_text_id(widget, ID_PROMPT_PES, GX_STRING_ID_STRING_CLOSE);
            else if(msg[1]==2)
                update_prompt_text_id(widget, ID_PROMPT_PAINEL, GX_STRING_ID_STRING_CLOSE);
            else if(msg[1]==3)
                update_prompt_text_id(widget, ID_PROMPT_VIDRO, GX_STRING_ID_STRING_CLOSE);
            break;
        case(3):
            if(msg[1]==1)
                update_prompt_text_id(widget, ID_PROMPT_PES, GX_STRING_ID_STRING_OPEN);
            else if(msg[1]==2)
                update_prompt_text_id(widget, ID_PROMPT_PAINEL, GX_STRING_ID_STRING_OPEN);
            else if(msg[1]==3)
                update_prompt_text_id(widget, ID_PROMPT_VIDRO, GX_STRING_ID_STRING_OPEN);
            break;
        case(4):
            var_aux = msg[1]/10;
            update_numeric_prompt_value(widget, ID_TEMP_DESEJADA, var_aux);
            var_aux = msg[1]-var_aux*10;
            update_numeric_prompt_value(widget, ID_TEMP_DESEJADA_DECIMAL, var_aux);
            break;
        case(5):
            var_aux = (int)(msg[1]/10);
            update_numeric_prompt_value(widget, ID_TEMP_ATUAL, var_aux);
            var_aux = msg[1]-var_aux*10;
            update_numeric_prompt_value(widget, ID_TEMP_ATUAL_DECIMAL, var_aux);
            break;
        case(6):
            update_numeric_prompt_value(widget, ID_VALVULA_QUENTE, msg[1]);
            break;
        case(7):
            update_numeric_prompt_value(widget, ID_VALVULA_FRIA, msg[1]);
            break;
        case(8):
            if(msg[1]==0)
                update_prompt_text_id(widget, ID_RUNNING, GX_STRING_ID_STRING_OFF);
            else if(msg[1]==1)
                update_prompt_text_id(widget, ID_RUNNING, GX_STRING_ID_STRING_ON);
            break;
        case(9):
            var_aux = msg[1]/10;
            update_numeric_prompt_value(widget, ID_TEMP_ALVO, var_aux);
            var_aux = msg[1]-var_aux*10;
            update_numeric_prompt_value(widget, ID_TEMP_ALVO_DECIMAL, var_aux);
            break;
        default:
            break;
    }
}

void tratamento_evento(GX_WINDOW *widget, GX_EVENT *event_ptr){
    ULONG msg = 0;
    switch (event_ptr->gx_event_type)
    {
        case GX_SIGNAL(ID_TEMP_MAIS, GX_EVENT_CLICKED):
            msg = TEMPERATURA_INC;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_TEMP_MENOS, GX_EVENT_CLICKED):
            msg = TEMPERATURA_DEC;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_VENT_MAIS, GX_EVENT_CLICKED):
            msg = VENTILACAO_INC;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_VENT_MENOS, GX_EVENT_CLICKED):
            msg = VENTILACAO_DEC;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_SAIDA_PES, GX_EVENT_TOGGLE_OFF):
            msg = SAIDA_PES_FECHA;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_SAIDA_PES, GX_EVENT_TOGGLE_ON):
            msg = SAIDA_PES_ABRE;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_SAIDA_PAINEL, GX_EVENT_TOGGLE_OFF):
            msg = SAIDA_PAINEL_FECHA;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_SAIDA_PAINEL, GX_EVENT_TOGGLE_ON):
            msg = SAIDA_PAINEL_ABRE;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_SAIDA_VIDRO, GX_EVENT_TOGGLE_OFF):
            msg = SAIDA_VIDRO_FECHA;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_SAIDA_VIDRO, GX_EVENT_TOGGLE_ON):
            msg = SAIDA_VIDRO_ABRE;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_START, GX_EVENT_TOGGLE_ON):
            msg = RUN;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_START, GX_EVENT_TOGGLE_OFF):
            msg = STOP;
            tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            break;
        default:
            //msg = 11;
            //tx_queue_send(&lcd_out_queue, &msg, TX_WAIT_FOREVER);
            gx_window_event_process(widget, event_ptr);
            break;
    }
}

static void update_prompt_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
    if (TX_SUCCESS == err)
    {
        gx_prompt_text_id_set(p_prompt, string_id);
    }
}

static void update_button_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_TEXT_BUTTON * p_button = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_button);

    if (TX_SUCCESS == err)
    {
        gx_text_button_text_id_set(p_button, string_id);
    }
}

static void update_numeric_prompt_value(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT value)
{
    GX_NUMERIC_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);

    if (TX_SUCCESS == err)
    {
        gx_numeric_prompt_value_set(p_prompt, (INT)value);
    }
}

