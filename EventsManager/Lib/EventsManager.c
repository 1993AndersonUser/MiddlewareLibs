
#include "EventsManager.h"

/**
 * @file  EventsManager.c
 * @copyright TONEDERM
 * @Author: Anderson Fortes
 * @brief Rotina de controle de eventos (LOW, HIGH, FALLING e RISING)
*/

/**  @fn void EventInit(Event *ThisEvent)
 *   @Required execution rate: Apenas inicialização
 *   @brief Inicializa estrutura de controle do evento
 *   @param  *ThisEvent: Ponteiro para a estrutura de controle do evento
 *   @return void
**/
void EventInit(Event *ThisEvent)
{
	ThisEvent->State = EVENT_LOW;
}

/**  @fn EventStatus EventProcess(Event *ThisEvent, uint8_t In)
 *   @Required execution rate: Eventualmente
 *   @brief Verifica se ocorreram os eventos
 *   @param  *ThisEvent: Ponteiro para a estrutura de controle do evento
 *   @param In: Valor 0-1. Indica o status atual do Input controlado
 *   @return EventStatus: EVENT_LOW, EVENT_RISING, EVENT_FALLING e EVENT_HIGH
**/
EventStatus EventProcess(Event *ThisEvent, uint8_t In)
{
	switch (ThisEvent->State)
	{
		case EVENT_LOW:
			if (In)
			{
				ThisEvent->State = EVENT_RISING;
			}
			break;
			
		case EVENT_HIGH:
			if (!In)
			{
				ThisEvent->State = EVENT_FALLING;
			}
			break;			
			
		case EVENT_FALLING:
			ThisEvent->State = EVENT_LOW;
			break;
			
		case EVENT_RISING:
			ThisEvent->State = EVENT_HIGH;
			break;
	}
	return ThisEvent->State;
}
