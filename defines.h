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
// defines.h (Add if unifying FSM states)
typedef enum {
  STATE_IDLE,
  STATE_THUMBWHEEL_MENU,
  STATE_CONFIGURE_WHEELS,
  STATE_FORWARD_START,
  STATE_FORWARD_ADJUST,
  STATE_REVERSE_START,
  STATE_REVERSE_ADJUST,
  STATE_INITIATE_STOP,
  STATE_CALIBRATION,
  STATE_STOP,
  STATE_PROCESS_COMMAND,
  STATE_AUTO,
  STATE_MANUAL
} FSM_State;

// ================== EVENT ENUM (for future FSM logic) ==================
typedef enum {
  EVENT_NONE,
  EVENT_IR_LEFT_HIGH,
  EVENT_IR_RIGHT_LOW,
  EVENT_MANUAL_LEFT_TURN,
  EVENT_START_CMD,
  EVENT_STOP_CMD,
  EVENT_LINE_FOUND,
  EVENT_TIMEOUT,
  EVENT_MANUAL_CMD,
  EVENT_AUTO_CMD
} Event;

extern Event current_event;

// ==================== MENU THUMB WHEEL ENUM ANd dEfiNES =================
#define ADC_IR_LEFT  0
#define ADC_IR_RIGHT 1
#define ADC_THUMB    2

#define MODE_THRESHOLD_1 1000
#define MODE_THRESHOLD_2 2000
#define MODE_THRESHOLD_3 3000

typedef enum {
    MODE_START,
    MODE_STOP,
    MODE_MANUAL,
    MODE_AUTO
} Menu_Mode;

extern Menu_Mode Thumbwheel_GetMode(void);
#endif // DEFINES_H_


