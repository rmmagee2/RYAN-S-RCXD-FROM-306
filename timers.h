#ifndef TIMERS_H_
#define TIMERS_H_

void Init_Clocks(void);
void Init_Timer_B0(void);
void Init_Timer_B3(void);
volatile uint8_t timer_event_flag = 0;

#endif // TIMERS_H_

