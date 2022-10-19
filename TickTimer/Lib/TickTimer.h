
#ifndef TICK_TIMER_H
#define TICK_TIMER_H

#include "GenericTypes.h" 

typedef struct {
   uint32_t Start;
   uint32_t Interval;
}TickTimer;

void TickTimerReset(TickTimer *T);
void TickTimerRestart(TickTimer *T);
void TickTimerSet(TickTimer *T, uint32_t Interval);
char TickTimerExpired(TickTimer *T);
uint32_t  TickTimerGet(void);
void TickTimerCounter(void);
void TickEnableCounter(BOOL value);

#endif
