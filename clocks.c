void Init_Clocks(void) {
    // Unlock CS registers
    CSCTL0_H = CSKEY >> 8;

    // Set DCO to 8MHz
    CSCTL1 = DCOFSEL_3 | DCORSEL;

    // Set ACLK = VLO (~10kHz), SMCLK = DCO/1, MCLK = DCO/1
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK;

    // Set dividers to 1
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;

    // Lock CS registers
    CSCTL0_H = 0;
}

