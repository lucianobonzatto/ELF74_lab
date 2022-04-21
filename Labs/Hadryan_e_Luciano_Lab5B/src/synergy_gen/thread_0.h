/* generated thread header file - do not edit */
#ifndef THREAD_0_H_
#define THREAD_0_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void thread_0_entry(void);
                #else
extern void thread_0_entry(void);
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern TX_QUEUE queue_0;
extern TX_SEMAPHORE semaphore_0;
extern TX_EVENT_FLAGS_GROUP event_flags_0;
extern TX_MUTEX mutex_0;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* THREAD_0_H_ */
