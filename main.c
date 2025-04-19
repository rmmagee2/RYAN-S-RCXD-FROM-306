#include "init.h"
#include "fsm.h"
#include "uart_comm.h"
#include "sensors.h"

int main(void) {
    Init_All();

    while (1) {
        UART_Process();
        Update_Sensors();
        FSM_Process();
    }
}
