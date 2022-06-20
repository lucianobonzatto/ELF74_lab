/* generated thread header file - do not edit */
#ifndef LOOP_PRINCIPAL_H_
#define LOOP_PRINCIPAL_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void loop_principal_entry(void);
                #else
extern void loop_principal_entry(void);
#endif
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_adc.h"
#include "r_adc_api.h"
#ifdef __cplusplus
extern "C" {
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer1;
#ifndef timer1Callback
void timer1Callback(timer_callback_args_t *p_args);
#endif
/** ADC on ADC Instance. */
extern const adc_instance_t g_adc0;
#ifndef NULL
void NULL(adc_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* LOOP_PRINCIPAL_H_ */
