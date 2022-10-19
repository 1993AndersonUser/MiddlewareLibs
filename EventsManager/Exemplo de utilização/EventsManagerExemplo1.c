
#include "EventsManager.h"

Event Ev_Tcl1;
Event Ev_Tcl2;

void LigaLeds(void)
{

}

void DesligaLeds(void)
{

}

void LigaBuzzer(void)
{
	
}

void DesligaBuzzer(void)
{
	
}

void AppInit(void)
{
   EventInit(&Ev_Tcl1);
   EventInit(&Ev_Tcl2);
}


void App(void)
{
   
   EventStatus Ev;
   
   Ev = EventProcess(&Ev_Tcl1, ENT_1);
   
   if (Ev== EVENT_RISING)
   {
      LigaLeds();
   }
   
   if (EventProcess(&Ev_Tcl2, ENT_2) == EVENT_FALLING)
   {
      DesligaLeds();
   }
   
   if (Ev == EVENT_HIGH)
   {
      LigaBuzzer();
   }
   else if (Ev == EVENT_LOW)
   {
	  DesligaBuzzer();
   }
}
