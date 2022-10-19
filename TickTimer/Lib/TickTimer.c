
#include "TickTimer.h"

/**
 * @file  TickTimer.c
 * @brief Controle de timer genérico.
 *
 * @warning V1.0
 * @todo
 * @bug
 * @copyright Tonederm - Anderson Fortes
*/

volatile uint32_t Ticks = 0;
volatile uint32_t TicksAtomic = 0;
static uint8_t AtomicAcces = 0;
volatile BOOL enableTicks = FALSE;

/**  @fn void TickTimerReset(TickTimer *T)
 *   @Required execution rate: Evento.
 *   @brief Reset o contador do timer.
 *   @param *T: Estrutura TickTimer.
 *   @return void
**/
void TickTimerReset(TickTimer *T)
{
   T->Start = T->Start + T->Interval;      
}

/**  @fn void TickTimerRestart(TickTimer *T)
 *   @Required execution rate: Evento.
 *   @brief Restart (zera variável) do contador do timer.
 *   @param *T: Estrutura TickTimer.
 *   @return void
**/
void TickTimerRestart(TickTimer *T)
{
   T->Start = TickTimerGet();      
}

/**  @fn void TickTimerSet(TickTimer *T, uint32_t Interval)
 *   @Required execution rate: Quando for setar um novo valor de tempo ao contador.
 *   @brief Adiciona um valor de tempo, em ms, na estrutura do contador.
 *   @param *T: Estrutura TickTimer.
 *   @param Interval: Intervalo do contador em ms.
 *   @return void
**/
void TickTimerSet(TickTimer *T, uint32_t Interval)
{
   T->Start = TickTimerGet();
   T->Interval = Interval;
}

/**  @fn char TickTimerExpired(TickTimer *T)
 *   @Required execution rate: Quando for verificar se o timer setado estourou.
 *   @brief Verifica se o timer setado estourou.
 *   @param *T: Estrutura TickTimer.
 *   @return 1: Timer estourou 0: Timer não estourou.
**/
char TickTimerExpired(TickTimer *T)
{
   if (TickTimerGet() - T->Start >= T->Interval)
   {
      return 1;
   }
   return 0;
}

/**  @fn uint32_t TickTimerGet(void)
 *   @Required execution rate: Evento.
 *   @brief Verifica o valor do contador que da a base de tempo.
 *   @param void
 *   @return Contador da base de tempo.
**/
uint32_t TickTimerGet(void)
{
	 uint32_t _Ticks;
	 
	 AtomicAcces = 1;
	 _Ticks = TicksAtomic;
	 AtomicAcces = 0;
	 
   return _Ticks;
}

/**  @fn void TickTimerCounter(void)
 *   @Required execution rate: 1ms
 *   @brief Gera a base de tempo, incrementando o contador.
 *   @param void
 *   @return void
**/
void TickTimerCounter(void)
{
	if(enableTicks == TRUE)
	{
		Ticks ++;

		if (!AtomicAcces)
		{
			TicksAtomic = Ticks;
		}
	}
}

/**  @fn void TickEnableCounter(BOOL value)
 *   @Required execution rate: Evento
 *   @brief Ativa ou desativa o contador
 *   @param TRUE ou FALSE
 *   @return void
**/
void TickEnableCounter(BOOL value)
{
   enableTicks = value;
}







