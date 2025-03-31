#ifndef MOTORS_H_
#define MOTORS_H_

#define FULL_SPEED   1000
#define HALF_SPEED    500
#define OFF             0

void Init_Motors(void);

void Drive_Forward(unsigned int speed);
void Drive_Reverse(unsigned int speed);
void Turn_Left(unsigned int speed);
void Turn_Right(unsigned int speed);
void Stop_Motors(void);

#endif // MOTORS_H_

