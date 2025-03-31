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

Update_Sensors();  // Call once per loop

uint8_t lineStatus = Detect_Line_Center();
switch(lineStatus) {
  case 3: LCD_Print("LINE", "CENTERED", "", ""); break;
  case 1: LCD_Print("LINE", "LEFT ONLY", "", ""); break;
  case 2: LCD_Print("LINE", "RIGHT ONLY", "", ""); break;
  case 0: LCD_Print("LINE", "LOST!", "", ""); break;
}

unsigned int speed = Get_Thumbwheel_PWM();
Drive_Forward(speed);

if(Is_Black_Left() && Is_Black_Right()) {
    LCD_Print("BLACK", "LINE", "", "");
    Stop_Motors();
    // do turn or adjust
}

UART_Process();

if(UART_CheckForCommand(UART_IOT)) {
    char* cmd = UART_GetCommand(UART_IOT);
    if(strcmp(cmd, "start") == 0) {
        // Start car
    }
}

if(UART_CheckForCommand(UART_PC)) {
    char* cmd = UART_GetCommand(UART_PC);
    if(strcmp(cmd, "debug") == 0) {
        UART_SendString(UART_PC, "Debug info here\n");
    }
}

Start_ADC(ADC_IR_LEFT);
// wait or flag in ISR sets "ready" flag
unsigned int leftIR = adc_values[ADC_IR_LEFT];

Drive_Forward(FULL_SPEED);
__delay_cycles(800000); // delay 0.1s
Turn_Left(HALF_SPEED);
Stop_Motors();
