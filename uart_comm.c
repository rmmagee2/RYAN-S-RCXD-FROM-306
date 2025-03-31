#include <msp430.h>
#include <string.h>
#include "uart.h"

// ==================== RING BUFFERS ====================
volatile char ringBuffer_IOT[UART_BUFFER_SIZE];
volatile uint8_t wr_IOT = 0, rd_IOT = 0;

volatile char ringBuffer_PC[UART_BUFFER_SIZE];
volatile uint8_t wr_PC = 0, rd_PC = 0;

// ==================== PROCESS BUFFERS ====================
char processBuffer_IOT[PROCESS_BUFFER_SIZE];
char processBuffer_PC[PROCESS_BUFFER_SIZE];
uint8_t newCommand_IOT = 0;
uint8_t newCommand_PC = 0;

// ==================== INIT ====================
void Init_UART(void) {
  // ==== UCA0 (PC UART via USB) ====
  UCA0CTLW0 = UCSWRST;
  UCA0CTLW0 |= UCSSEL__SMCLK;
  UCA0BRW = 52;
  UCA0MCTLW = 0x4911;
  UCA0CTLW0 &= ~UCSWRST;
  UCA0IE |= UCRXIE;

  // ==== UCA1 (IOT WiFi UART) ====
  UCA1CTLW0 = UCSWRST;
  UCA1CTLW0 |= UCSSEL__SMCLK;
  UCA1BRW = 52;
  UCA1MCTLW = 0x4911;
  UCA1CTLW0 &= ~UCSWRST;
  UCA1IE |= UCRXIE;
}

// ==================== PROCESS (Main loop) ====================
void UART_Process(void) {
  // ---- PC ----
  while(rd_PC != wr_PC) {
    char c = ringBuffer_PC[rd_PC++];
    rd_PC %= UART_BUFFER_SIZE;

    static uint8_t idx = 0;
    if (c == '\n' || c == '\r') {
      processBuffer_PC[idx] = '\0';
      newCommand_PC = 1;
      idx = 0;
    } else if (idx < PROCESS_BUFFER_SIZE - 1) {
      processBuffer_PC[idx++] = c;
    }
  }

  // ---- IOT ----
  while(rd_IOT != wr_IOT) {
    char c = ringBuffer_IOT[rd_IOT++];
    rd_IOT %= UART_BUFFER_SIZE;

    static uint8_t idx = 0;
    if (c == '\n' || c == '\r') {
      processBuffer_IOT[idx] = '\0';
      newCommand_IOT = 1;
      idx = 0;
    } else if (idx < PROCESS_BUFFER_SIZE - 1) {
      processBuffer_IOT[idx++] = c;
    }
  }
}

// ==================== CHECK FOR COMMAND ====================
uint8_t UART_CheckForCommand(uint8_t channel) {
  if(channel == UART_PC) return newCommand_PC;
  if(channel == UART_IOT) return newCommand_IOT;

