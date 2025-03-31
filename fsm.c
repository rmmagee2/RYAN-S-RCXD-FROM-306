// fsm.c
#include "fsm.h"
#include "motors.h"
#include "adc.h"
#include "lcd.h"
#include "sensors.h"
#include "iot_uart.h"
#include "defines.h"

static FSM_State current_state = STATE_IDLE;
static FSM_State next_state = STATE_IDLE;

void FSM_Init(void) {
    current_state = STATE_IDLE;
    next_state = STATE_IDLE;
}

void Set_Next_State(FSM_State new_state) {
    next_state = new_state;
}

void FSM_Process(void) {
    if (current_state != next_state) {
        current_state = next_state;
    }

    switch (current_state) {
        case STATE_IDLE:
            break;

        case STATE_THUMBWHEEL_MENU:
            // process potentiometer values for menu selection
            Thumbwheel_Menu();
            break;

        case STATE_CONFIGURE_WHEELS:
            Configure_Wheels();
            break;

        case STATE_FORWARD_START:
            Move_Forward_Start();
            break;

        case STATE_FORWARD_ADJUST:
            Adjust_Forward();
            break;

        case STATE_REVERSE_START:
            Move_Reverse_Start();
            break;

        case STATE_REVERSE_ADJUST:
            Adjust_Reverse();
            break;

        case STATE_INITIATE_STOP:
            Stop_Movement_Init();
            break;

        case STATE_STOP:
            Stop_Movement_Final();
            break;

        case STATE_PROCESS_COMMAND:
            Process_IOT_Command();
            break;

        default:
            break;
    }
}

