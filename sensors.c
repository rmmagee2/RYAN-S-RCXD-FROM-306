#include "adc.h"
#include "sensors.h"

void Init_Sensors(void) {
  // Could start all ADCs once to pre-fill values
  Start_ADC(ADC_IR_LEFT);
  __delay_cycles(10000);
  Start_ADC(ADC_IR_RIGHT);
  __delay_cycles(10000);
  Start_ADC(ADC_THUMB);
  __delay_cycles(10000);
}

uint8_t Is_Black_Left(void) {
  return adc_values[ADC_IR_LEFT] < BLACK_THRESHOLD;
}

uint8_t Is_Black_Right(void) {
  return adc_values[ADC_IR_RIGHT] < BLACK_THRESHOLD;
}

uint16_t Get_Thumbwheel_PWM(void) {
  uint16_t val = adc_values[ADC_THUMB]; // 12-bit max is 4095
  return (val * 1000) / 4095;           // Scale to 0–1000 (same as PWM period)
}

