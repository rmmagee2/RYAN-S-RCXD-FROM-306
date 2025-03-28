void Init_Timer_B0(void) {
    TB0CTL = TBSSEL__SMCLK | MC__CONTINUOUS | TBCLR; // SMCLK, continuous, reset

    TB0CCTL0 = CCIE;                    // Enable CCR0 interrupt
    TB0CCR0 = 8000;                     // ~1ms interrupt (8000 clocks @ 8MHz)

    TB0CCTL1 = CCIE;
    TB0CCR1 = 16000;                    // Optional 2ms event or ADC timing

    TB0CCTL2 = CCIE;
    TB0CCR2 = 32000;                    // Optional 4ms event

    TB0CTL |= TBIE;                     // Enable overflow interrupt (optional)
}

void Init_Timer_B3(void) {
    TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // SMCLK, Up Mode, clear

    TB3CCR0 = 1000;      // PWM period = 1kHz at 8MHz

    // RIGHT FWD – TB3.1
    TB3CCTL1 = OUTMOD_7; // Reset/Set
    TB3CCR1 = 0;         // Initial duty cycle = 0%

    // RIGHT REV – TB3.2
    TB3CCTL2 = OUTMOD_7;
    TB3CCR2 = 0;

    // LEFT FWD – TB3.3
    TB3CCTL3 = OUTMOD_7;
    TB3CCR3 = 0;

    // LEFT REV – TB3.4
    TB3CCTL4 = OUTMOD_7;
    TB3CCR4 = 0;
}

