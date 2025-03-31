#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdint.h>

#define BLACK_THRESHOLD    500  // Tune this based on surface testing

void Init_Sensors(void);

uint8_t Is_Black_Left(void);
uint8_t Is_Black_Right(void);
uint16_t Get_Thumbwheel_PWM(void);

#endif // SENSORS_H_

