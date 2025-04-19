#ifndef MOTORS_H_
#define MOTORS_H_

#include <stdint.h>

#define FULL_SPEED   1000
#define HALF_SPEED    500
#define OFF             0

void Init_Motors(void);

// FSM-level state functions
void Configure_Wheels(void);

void Move_Forward_Start(void);
void Adjust_Forward(void);

void Move_Reverse_Start(void);
void Adjust_Reverse(void);

void Stop_Movement_Init(void);
void Stop_Movement_Final(void);

#endif // MOTORS_H_
