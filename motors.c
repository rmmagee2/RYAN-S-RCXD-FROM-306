#include <msp430.h>
#include "motors.h"
#include "sensors.h"  // For IR sensors in adjustment
#include "defines.h"  // For PWM values if reused

void Init_Motors(void) {
  // Setup Timer B3 for PWM
  TB3CTL = TBSSEL__SMCLK | MC__UP | TBCLR;
  TB3CCR0 = PWM_PERIOD;  // Standardized in defines.h

  // Set output modes for each channel
  TB3CCTL1 = OUTMOD_7; // Right Forward  (P6.1)
  TB3CCTL2 = OUTMOD_7; // Right Reverse  (P6.2)
  TB3CCTL3 = OUTMOD_7; // Left  Forward  (P6.3)
  TB3CCTL4 = OUTMOD_7; // Left  Reverse  (P6.4)

  Stop_Movement_Final();
}

// FSM: Sets up wheel directions, speed defaults if needed
void Configure_Wheels(void) {
  // Placeholder for future config logic (e.g., spin-up sequence)
}

// FSM: Begin forward movement at FULL speed
void Move_Forward_Start(void) {
  TB3CCR1 = FULL_SPEED;  // Right Forward
  TB3CCR2 = OFF;         // Right Reverse
  TB3CCR3 = FULL_SPEED;  // Left Forward
  TB3CCR4 = OFF;         // Left Reverse
}

// FSM: Adjust forward movement based on IR sensors
void Adjust_Forward(void) {
  uint8_t line = Detect_Line_Center();
  switch (line) {
    case 3:  // Centered
      TB3CCR1 = HALF_SPEED;
      TB3CCR3 = HALF_SPEED;
      break;
    case 1:  // Just Left sensor sees line
      TB3CCR1 = FULL_SPEED;
      TB3CCR3 = HALF_SPEED;
      break;
    case 2:  // Just Right sensor sees line
      TB3CCR1 = HALF_SPEED;
      TB3CCR3 = FULL_SPEED;
      break;
    default: // Line lost
      Stop_Movement_Init();
      break;
  }
  TB3CCR2 = OFF;
  TB3CCR4 = OFF;
}

// FSM: Begin reverse movement
void Move_Reverse_Start(void) {
  TB3CCR1 = OFF;
  TB3CCR2 = FULL_SPEED;  // Right Reverse
  TB3CCR3 = OFF;
  TB3CCR4 = FULL_SPEED;  // Left Reverse
}

// FSM: Adjust reverse based on IR
void Adjust_Reverse(void) {
  uint8_t line = Detect_Line_Center();
  switch (line) {
    case 3:  // Centered
      TB3CCR2 = HALF_SPEED;
      TB3CCR4 = HALF_SPEED;
      break;
    case 1:
      TB3CCR2 = HALF_SPEED;
      TB3CCR4 = FULL_SPEED;
      break;
    case 2:
      TB3CCR2 = FULL_SPEED;
      TB3CCR4 = HALF_SPEED;
      break;
    default:
      Stop_Movement_Init();
      break;
  }
  TB3CCR1 = OFF;
  TB3CCR3 = OFF;
}

// FSM: Begin stop sequence â€” PWM off, delay if needed
void Stop_Movement_Init(void) {
  TB3CCR1 = OFF;
  TB3CCR2 = OFF;
  TB3CCR3 = OFF;
  TB3CCR4 = OFF;

  // Optional: delay or brake hold
  __delay_cycles(800000); // 100ms @ 8MHz
}

// FSM: Ensure complete stop
void Stop_Movement_Final(void) {
  TB3CCR1 = OFF;
  TB3CCR2 = OFF;
  TB3CCR3 = OFF;
  TB3CCR4 = OFF;
}
