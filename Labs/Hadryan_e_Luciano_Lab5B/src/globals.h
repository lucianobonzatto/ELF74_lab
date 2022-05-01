#ifndef GLOBALS_H_
#define GLOBALS_H_

#include "tx_api.h"
#include "thread_0.h"

ULONG thread_0_counter;

ULONG thread_1_counter;
ULONG thread_1_messages_sent;

ULONG thread_2_counter;
ULONG thread_2_messages_received;

ULONG thread_3_counter;

ULONG thread_4_counter;

ULONG thread_5_counter;

ULONG thread_6_counter;

ULONG thread_7_counter;

void thread_3_and_4_entry(ULONG thread_input);
void thread_6_and_7_entry(ULONG thread_input);

#endif