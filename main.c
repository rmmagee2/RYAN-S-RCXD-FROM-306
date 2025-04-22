#include "init.h"
#include "fsm.h"
#include "uart_comm.h"
#include "sensors.h"
#include "lcd.h"

int main(void) {
    Init_All();

    LCD_Print("Boot OK");

    Set_Next_State(STATE_THUMBWHEEL_MENU);  // Force a state for debug

    while (1) {
        UART_Process();      // Handle IOT commands
        Update_Sensors();    // Poll line sensors
        FSM_Process();       // Run main FSM
    }
}
