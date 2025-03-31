#include <msp430.h>
#include "adc.h"

volatile unsigned int adc_values[3] = {0, 0, 0};  // L, R, Thumb

void Init_ADC(void) {
  // Turn on ADC12_B, set sampling time, and use SMCLK
  ADC12CTL0 = ADC12SHT0_2 | ADC12ON;
  ADC12CTL1 = ADC12SHP;             // Use sampling timer
  ADC12CTL2 = ADC12RES_2;           // 12-bit resolution
  ADC12IER0 = ADC12IE0;             // Enable interrupt for MEM0
  ADC12CTL0 &= ~ADC12ENC;           // Disable ADC while configuring

  // Input pins were configured in ports.c (SEL0/SEL1 for A2/A3/A5)
  // A2 = P1.2 (IR Left), A3 = P1.3 (IR Right), A5 = P1.5 (Thumb)
}

// Start ADC conversion for specific channel
void Start_ADC(uint8_t channel) {
  ADC12CTL0 &= ~ADC12ENC;  // Disable before changing settings

  switch(channel) {
    case ADC_IR_LEFT:
      ADC12MCTL0 = ADC12INCH_2; // A2
      break;
    case ADC_IR_RIGHT:
      ADC12MCTL0 = ADC12INCH_3; // A3
      break;
    case ADC_THUMB:
      ADC12MCTL0 = ADC12INCH_5; // A5
      break;
    default:
      return;
  }

  ADC12CTL0 |= ADC12ENC | ADC12SC; // Enable and start conversion
}

// ISR to read ADC result
#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void) {
  switch(__even_in_range(ADC12IV, ADC12IV_ADC12RDYIFG)) {
    case ADC12IV_ADC12IFG0:
      // Figure out which input was last used based on MCTL0
      switch(ADC12MCTL0 & ADC12INCH_15) {
        case ADC12INCH_2:
          adc_values[ADC_IR_LEFT] = ADC12MEM0;
          break;
        case ADC12INCH_3:
          adc_values[ADC_IR_RIGHT] = ADC12MEM0;
          break;
        case ADC12INCH_5:
          adc_values[ADC_THUMB] = ADC12MEM0;
          break;
      }
      break;
    default:
      break;
  }
}

Menu_Mode Thumbwheel_GetMode(void) {
    unsigned int val = ADC_Thumb; // global updated in ADC ISR
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
            // maybe toggle LED or update LCD
            break;
        case MODE_AUTO:
            // enable autonomous line following
            break;
        default:
            break;
    }
}

