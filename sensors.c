#include "adc.h"
#include "sensors.h"

static uint8_t adc_cycle_index = 0;
static uint16_t dynamic_threshold = 500; // Default value

void Init_Sensors(void) {
  Start_ADC(ADC_IR_LEFT);
  __delay_cycles(10000);
  Start_ADC(ADC_IR_RIGHT);
  __delay_cycles(10000);
  Start_ADC(ADC_THUMB);
  __delay_cycles(10000);
}

// Call this every loop to rotate ADC sampling
void Update_Sensors(void) {
  switch(adc_cycle_index) {
    case 0:
      Start_ADC(ADC_IR_LEFT);
      break;
    case 1:
      Start_ADC(ADC_IR_RIGHT);
      break;
    case 2:
      Start_ADC(ADC_THUMB);
      break;
  }
  adc_cycle_index = (adc_cycle_index + 1) % 3;
}

uint8_t Is_Black_Left(void) {
  return adc_values[ADC_IR_LEFT] < dynamic_threshold;
}

uint8_t Is_Black_Right(void) {
  return adc_values[ADC_IR_RIGHT] < dynamic_threshold;
}

uint8_t Detect_Line_Center(void) {
  uint8_t left = Is_Black_Left();
  uint8_t right = Is_Black_Right();

  if(left && right) return 3;      // Both = Centered
  if(left)          return 1;      // Just Left
  if(right)         return 2;      // Just Right
  return 0;                        // No Line
}

uint16_t Get_Thumbwheel_PWM(void) {
  uint16_t val = adc_values[ADC_THUMB]; // 12-bit max is 4095
  return (val * 1000) / 4095;           // Scale to 0–1000
}
