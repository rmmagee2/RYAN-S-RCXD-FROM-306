#include <msp430.h>
#include "motors.h"

void Init_Motors(void) {
  // Setup Timer B3 for PWM
  TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR; // SMCLK, Up Mode, clear
  TB3CCR0 = 1000;  // PWM period (1kHz for smooth drive)

  // OUTMOD_7 = Reset/Set (PWM output mode)
  TB3CCTL1 = OUTMOD_7; // RIGHT FORWARD  → P6.1
  TB3CCTL2 = OUTMOD_7; // RIGHT REVERSE  → P6.2
  TB3CCTL3 = OUTMOD_7; // LEFT  FORWARD  → P6.3
  TB3CCTL4 = OUTMOD_7; // LEFT  REVERSE  → P6.4

  // Start with everything OFF
  TB3CCR1 = OFF;
  TB3CCR2 = OFF;
  TB3CCR3 = OFF;
  TB3CCR4 = OFF;
}

void Drive_Forward(unsigned int speed) {
  // Forward only, kill reverse
  TB3CCR1 = speed;    // Right Forward
  TB3CCR2 = OFF;      // Right Reverse
  TB3CCR3 = speed;    // Left Forward
  TB3CCR4 = OFF;      // Left Reverse
}

void Drive_Reverse(unsigned int speed) {
  TB3CCR1 = OFF;
  TB3CCR2 = speed;
  TB3CCR3 = OFF;
  TB3CCR4 = speed;
}

void Turn_Left(unsigned int speed) {
  TB3CCR1 = speed;  // Right wheel forward
  TB3CCR2 = OFF;
  TB3CCR3 = OFF;    // Left wheel stopped or slight reverse
  TB3CCR4 = OFF;
}

void Turn_Right(unsigned int speed) {
  TB3CCR1 = OFF;
  TB3CCR2 = OFF;
  TB3CCR3 = speed;  // Left wheel forward
  TB3CCR4 = OFF;
}

void Stop_Motors(void) {
  TB3CCR1 = OFF;
  TB3CCR2 = OFF;
  TB3CCR3 = OFF;
  TB3CCR4 = OFF;
}
