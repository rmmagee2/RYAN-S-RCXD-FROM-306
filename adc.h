#ifndef ADC_H_
#define ADC_H_

#define ADC_IR_LEFT     0
#define ADC_IR_RIGHT    1
#define ADC_THUMB       2

extern volatile unsigned int adc_values[3];

void Init_ADC(void);
void Start_ADC(uint8_t channel);

#define MODE_THRESHOLD_1 500
#define MODE_THRESHOLD_2 1500
#define MODE_THRESHOLD_3 2500
#define MODE_THRESHOLD_4 3500

typedef enum {
    MODE_NONE,
    MODE_START,
    MODE_STOP,
    MODE_MANUAL,
    MODE_AUTO
} Menu_Mode;

Menu_Mode Thumbwheel_GetMode(void);
void Thumbwheel_Menu(void);

#endif /* ADC_H_ */
