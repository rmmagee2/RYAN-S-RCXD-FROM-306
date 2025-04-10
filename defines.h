#ifndef DEFINES_H_
#define DEFINES_H_

// ================== CLOCK SPEEDS ==================
#define SMCLK_FREQ     8000000     // SMCLK = 8MHz assumed from DCO config in clocks.c
#define ACLK_FREQ       10000      // ACLK = ~10kHz from VLO (or 32768 Hz if LFXT is used)

// ================== PWM ==================
#define PWM_PERIOD      1000       // TimerB3 CCR0  8 kHz PWM if SMCLK is 8MHz (Frequency = 8MHz / 1000 = 8kHz PWM, not 1kHz as commented)
#define FULL_SPEED      1000
#define HALF_SPEED       500
#define OFF                0

// ================== ADC ==================
#define ADC_MAX_VALUE   4095
#define BLACK_THRESHOLD  500        // Calibrate this
//#define BLACK_THRESHOLD ((white_avg + black_avg) / 2)

// ================== UART ==================
#define UART_BUFFER_SIZE     64
#define PROCESS_BUFFER_SIZE  32

#define UART_PC        0
#define UART_IOT       1

// ================== STATE MACHINE ENUM (for later) ==================
typedef enum {
  STATE_IDLE,
  STATE_WAIT_START,
  STATE_FORWARD,
  STATE_TURN,
  STATE_LINE_DETECTED,
  STATE_STOPPED,
  STATE_MANUAL,
  STATE_AUTO
} State;

extern State current_state;

// ================== EVENT ENUM (for future FSM logic) ==================
typedef enum {
  EVENT_NONE,
  EVENT_START_CMD,
  EVENT_STOP_CMD,
  EVENT_LINE_FOUND,
  EVENT_TIMEOUT,
  EVENT_MANUAL_CMD,
  EVENT_AUTO_CMD
} Event;

extern Event current_event;

#endif // DEFINES_H_

