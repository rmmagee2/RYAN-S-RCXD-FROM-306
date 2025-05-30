#ifndef TIMERS_H_
#define TIMERS_H_
#include <stdint.h>

extern volatile uint8_t timer_done;
extern volatile uint8_t timer_event_flag; // in header

void Start_Delay(uint16_t ms);  // millisecond timer trigger

void Init_Clocks(void);
void Init_Timer_B0(void);
void Init_Timer_B3(void);

#endif // TIMERS_H_

