#include <msp430.h>
#include "init.h"
#include "ports.h"
#include "lcd.h"
#include "uart_comm.h"
#include "adc.h"
#include "sensors.h"
#include "timers.h"
#include "motors.h"
#include "fsm.h"

void Init_All(void) {
    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer

    Init_Ports();
    Init_Clocks();
    Init_Timer_B0();
    Init_Timer_B3();
    Init_LCD();
    Init_UART();
    Init_ADC();
    Init_Sensors();
    Init_Motors();
    FSM_Init();

    __enable_interrupt();        // Global interrupt enable
    PM5CTL0 &= ~LOCKLPM5;
}
