#include <msp430fr2355.h>
#include "defines.h"
#include "fsm.h"
#include <stdint.h>

volatile unsigned int adc_values[3] = {0, 0, 0};  // L, R, Thumb

void Init_ADC(void) {
    ADCCTL0 &= ~ADCENC;  // Disable ADC before configuring

    ADCCTL0 = ADCSHT_2 | ADCON;      // Sample & hold time = 16 ADC clocks, turn on ADC
    ADCCTL1 = ADCSHP;                // Sampling timer
    ADCCTL2 = ADCRES_2;              // 12-bit conversion results
    ADCIE = ADCIE0;                  // Enable ADCMEM0 interrupt

    // Inputs A2, A3, A5 selected in ports.c (SEL0/SEL1)

    ADCCTL0 |= ADCENC;              // Enable ADC
}

void Start_ADC(uint8_t channel) {
    ADCCTL0 &= ~ADCENC;  // Disable ADC before reconfig

    switch(channel) {
        case ADC_IR_LEFT:
            ADCMCTL0 = ADCINCH_2;  // A2
            break;
        case ADC_IR_RIGHT:
            ADCMCTL0 = ADCINCH_3;  // A3
            break;
        case ADC_THUMB:
            ADCMCTL0 = ADCINCH_5;  // A5
            break;
        default:
            return;
    }

    ADCCTL0 |= ADCENC | ADCSC;  // Enable and start conversion
}

#pragma vector=ADC_VECTOR
__interrupt void ADC_ISR(void) {
    switch(__even_in_range(ADCIV, ADCIV__ADCIFG0)) {
        case ADCIV__ADCIFG0:
            switch (ADCMCTL0 & 0x0F) {  // Mask to get channel number
                case ADCINCH_2:
                    adc_values[ADC_IR_LEFT] = ADCMEM0;
                    break;
                case ADCINCH_3:
                    adc_values[ADC_IR_RIGHT] = ADCMEM0;
                    break;
                case ADCINCH_5:
                    adc_values[ADC_THUMB] = ADCMEM0;
                    break;
            }
            break;
        default:
            break;
    }
}

Menu_Mode Thumbwheel_GetMode(void) {
    unsigned int val = adc_values[ADC_THUMB];  // Use stored value
    if (val < MODE_THRESHOLD_1)
        return MODE_START;
    else if (val < MODE_THRESHOLD_2)
        return MODE_STOP;
    else if (val < MODE_THRESHOLD_3)
        return MODE_MANUAL;
    else
        return MODE_AUTO;
}

void Thumbwheel_Menu(void) {
    Menu_Mode mode = Thumbwheel_GetMode();
    switch (mode) {
        case MODE_START:
            Set_Next_State(STATE_FORWARD_START);
            break;
        case MODE_STOP:
            Set_Next_State(STATE_INITIATE_STOP);
            break;
        case MODE_MANUAL:
            // Toggle LED or do something manual
            break;
        case MODE_AUTO:
            // Start autonomous mode
            break;
        default:
            break;
    }
}

