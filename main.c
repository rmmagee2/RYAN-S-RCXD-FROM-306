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
