#ifndef UART_H_
#define UART_H_

#define UART_BUFFER_SIZE     64
#define PROCESS_BUFFER_SIZE  32

// UART Channels
#define UART_PC     0
#define UART_IOT    1

void Init_UART(void);
void UART_Process(void);

uint8_t UART_CheckForCommand(uint8_t channel);
char* UART_GetCommand(uint8_t channel);
void UART_SendString(uint8_t channel, const char* str);
void Process_IOT_Command(void);

#endif // UART_H_
