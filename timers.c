#include <msp430.h>
#include "timers.h"

volatile uint8_t timer_done = 0;
volatile uint8_t timer_event_flag = 0;

void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK | MC__CONTINUOUS | TBCLR;
    TB0CCTL0 = CCIE;
}

void Start_Delay(uint16_t ms) {
    timer_done = 0;
    uint16_t offset = (ms * 8000); // 8MHz SMCLK = 8000 ticks/ms
    TB0CCR0 = TB0R + offset;
}


void Init_Timer_B3(void) {
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // SMCLK, Up Mode, clear

    TB3CCR0 = 1000;      // PWM period = 1kHz at 8MHz

    // RIGHT FWD â€“ TB3.1
    TB3CCTL1 = OUTMOD_7; // Reset/Set
    TB3CCR1 = 0;         // Initial duty cycle = 0%

    // RIGHT REV â€“ TB3.2
    TB3CCTL2 = OUTMOD_7;
    TB3CCR2 = 0;

    // LEFT FWD â€“ TB3.3
    TB3CCTL3 = OUTMOD_7;
    TB3CCR3 = 0;

    // LEFT REV â€“ TB3.4
    TB3CCTL4 = OUTMOD_7;
    TB3CCR4 = 0;
}

