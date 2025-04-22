#include <msp430fr2355.h>

// Initializes the system clocks:
// - DCO set to ~8MHz
// - MCLK = DCO
// - SMCLK = DCO
// - ACLK = REFO (default ~32kHz)
// - All dividers set to /1
void Init_Clocks(void) {
    // Clear CS tuning
    CSCTL0 = 0;

    // Set DCO to 8 MHz (DCO range select)
    CSCTL1 = DCORSEL_3;

    // Configure FLL (FLLD divider and multiplier N=243)
    CSCTL2 = FLLD__1 | 243;

    // Set FLL reference source to REFO (default)
    CSCTL3 = FLLREFDIV__1 | SELREF__REFOCLK;

    // Set MCLK and SMCLK to DCOCLKDIV, ACLK to REFO
    CSCTL4 = SELMS__DCOCLKDIV | SELA__REFOCLK;

    // Set all dividers to /1
    CSCTL5 = DIVM__1 | DIVS__1 | DIVA__1;
}
