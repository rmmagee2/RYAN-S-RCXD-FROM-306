#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

#define ADC_IR_LEFT     0
#define ADC_IR_RIGHT    1
#define ADC_THUMB       2

extern volatile unsigned int adc_values[3];

void Init_ADC(void);
void Start_ADC(uint8_t channel);


void Thumbwheel_Menu(void);

#endif /* ADC_H_ */
