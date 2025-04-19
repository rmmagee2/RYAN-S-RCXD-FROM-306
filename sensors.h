#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdint.h>

//#define BLACK_THRESHOLD    500  // Tune this value during calibration

void Init_Sensors(void);
void Update_Sensors(void);
void Calibrate_IR_Sensors(void);

uint8_t Is_Black_Left(void);
uint8_t Is_Black_Right(void);
uint8_t Detect_Line_Center(void);

uint16_t Get_Thumbwheel_PWM(void);

#endif // SENSORS_H_

