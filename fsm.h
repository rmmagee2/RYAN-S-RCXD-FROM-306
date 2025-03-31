// fsm.h
#include "defines.h"
#include "timers.h"
#include "defines.h"

#ifndef FSM_H
#define FSM_H

typedef enum {
    STATE_IDLE,
    STATE_THUMBWHEEL_MENU,
    STATE_CONFIGURE_WHEELS,
    STATE_FORWARD_START,
    STATE_FORWARD_ADJUST,
    STATE_REVERSE_START,
    STATE_REVERSE_ADJUST,
    STATE_INITIATE_STOP,
    STATE_STOP,
    STATE_PROCESS_COMMAND
} FSM_State;

void FSM_Init(void);
void FSM_Process(void);
void Set_Next_State(FSM_State new_state);

#endif

