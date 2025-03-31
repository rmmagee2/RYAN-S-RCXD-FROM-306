#include <msp430.h>
#include "init.h"
#include "ports.h"
#include "timers.h"
#include "adc.h"
#include "motors.h"
#include "sensors.h"
#include "uart.h"
#include "lcd.h"

// ==================== MASTER INIT ====================
void Init_All(void) {
  WDTCTL = WDTPW | WDTHOLD;  // Disable Watchdog

  Init_Ports();              // GPIO directions & defaults
  Init_Clocks();             // 8MHz SMCLK + VLO ACLK
  Init_Timer_B0();           // Continuous mode timer for delays, FSM, ADC timing
  Init_Timer_B3();           // Motor PWM (TB3.1–4)

  Init_UART();               // UART0 for PC, UART1 for IOT
  Init_ADC();                // ADC config only
  Init_Sensors();            // Optional pre-filling ADC readings
  Init_Motors();             // PWM config + motor safety

  Init_LCD();                // SPI + LCD control pins

  __enable_interrupt();      // Global interrupt enable
}

