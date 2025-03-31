#include "msp430.h"
#include "macros.h"
#include "interrupts.h"

// TimerB0 CCR0 ISR
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void) {
  TB0CCR0 += 25000; // Placeholder interval logic
  // TODO: add logic later when we need it
}

// TimerB0 CCR1–CCR2 + overflow ISR
#pragma vector = TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void) {
  switch(__even_in_range(TB0IV,14)) {
    case 0: break;
    case 2: TB0CCR1 += 25000; break; // placeholder
    case 4: TB0CCR2 += 25000; break; // placeholder
    case 14: break; // overflow, use later if needed
    default: break;
  }
}

#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void) {
  if(UCA0IFG & UCRXIFG) {
    ringBuffer_PC[wr_PC++] = UCA0RXBUF;
    wr_PC %= UART_BUFFER_SIZE;
  }
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void) {
  if(UCA1IFG & UCRXIFG) {
    ringBuffer_IOT[wr_IOT++] = UCA1RXBUF;
    wr_IOT %= UART_BUFFER_SIZE;
  }
}
