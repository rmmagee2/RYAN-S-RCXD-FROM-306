// === main.c ===
#include <msp430fr2355.h>
#include <stdint.h>
#include <string.h>
#include "lcd.h"
#include "ports.h"

volatile uint16_t ADC_Left_Detect = 0;
char adc_char[4];

#define ADC_BLACK_THRESHOLD 15

void Init_ADC(void);
void HEXtoBCD(int hex_value);

void delay_ms(unsigned int ms) {
    while (ms--) __delay_cycles(8000);
}

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;
  PM5CTL0 &= ~LOCKLPM5;

  Init_LCD();

  LCD_command(0x80);      // Move to line 1
  LCD_data('T');
  LCD_data('E');
  LCD_data('S');
  LCD_data('T');

  while (1) {
    P6OUT ^= BIT6;
    __delay_cycles(800000);
  }
}


void Init_ADC(void) {
    ADCCTL0 = 0;
    ADCCTL0 |= ADCSHT_2 | ADCON;
    ADCCTL1 = ADCSHP;
    ADCCTL2 = ADCRES_2;
    ADCMCTL0 = ADCINCH_2 | ADCSREF_0;
}

void HEXtoBCD(int hex_value) {
    int value = 0;
    adc_char[0] = adc_char[1] = adc_char[2] = '0';

    while (hex_value > 999) { hex_value -= 1000; value++; adc_char[0] = 0x30 + value; }
    value = 0;
    while (hex_value > 99)  { hex_value -= 100;  value++; adc_char[1] = 0x30 + value; }
    value = 0;
    while (hex_value > 9)   { hex_value -= 10;   value++; adc_char[2] = 0x30 + value; }
    adc_char[3] = 0x30 + hex_value;
}
