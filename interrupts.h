#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

__interrupt void Timer0_B0_ISR(void);
__interrupt void TIMER0_B1_ISR(void);
__interrupt void USCI_A0_ISR(void);
__interrupt void USCI_A1_ISR(void);

#endif /* INTERRUPTS_H_ */
