
#ifndef EVENTS_MANAGER_H
#define EVENTS_MANAGER_H

#include "GenericTypes.h"

typedef enum {
   EVENT_LOW = 0,	//Nivel baixo
   EVENT_HIGH,    	//Nivel alto
   EVENT_FALLING,	//Borda de descida
   EVENT_RISING,	//Borda de subida
}EventStatus;

typedef struct {
   uint8_t State;
   uint8_t Level;
}Event;

void EventInit(Event *ThisEvent);
EventStatus EventProcess(Event *ThisEvent, uint8_t In);

#endif
