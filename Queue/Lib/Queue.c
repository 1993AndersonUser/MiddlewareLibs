
#include "Queue.h"
#include <string.h>

/**
 * @file  Queue.c
 * @brief Buffer FIFO circular de uma estrutura de dados qualquer.
 *
 * @warning
 * @todo
 * @bug
 * @copyright Tonederm - Anderson Fortes
*/

/**  @fn uint8_t QueueInit(Queue *This, void *Buffer, uint16_t BufferLentgh, uint8_t SizeOfData)
 *   @Required execution rate: Apenas inicialização
 *   @brief Rotina de inicialização do buffer circular.
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @param *Buffer: Ponteiro para a estrutura de dados.
 *   @param BufferLentgh: Tamanho total do buffer de dados.
 *   @param SizeOfData: Tamanho da estrutura do buffer de dados.
 *   @Ex: Init:
 *   j1939_Msg_t CANTxBuffer[CAN_TX_BUFFER_MAX];
 *   Queue CANTxQueue;
 *   QueueInit(&CANTxQueue, &CANTxBuffer, sizeof(CANTxBuffer), sizeof(j1939_Msg_t));
 *   @return OK
**/
uint8_t QueueInit(Queue *This, void *Buffer, uint16_t BufferLentgh, uint8_t SizeOfData)
{
   This->SizeOfData = SizeOfData;
   This->Tail = 0xFFFF - (SizeOfData - 1);
   This->Head = 0;
   This->Count = 0;
   This->Buffer = Buffer;
   This->BufferLength = BufferLentgh;
   return OK;
}

/**  @fn uint8_t QueueEnqueue (Queue *This, void *Data)
 *   @Required execution rate: Evento
 *   @brief Adiciona dado ao buffer circuilar FIFO
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @param *Data: Ponteiro para o dado (estrutura).
 *   @return OK ou NOK
**/
uint8_t QueueEnqueue (Queue *This, void *Data)
{
	uint16_t Size = This->SizeOfData;
   //void *Position; //= (U8 *)This->Buffer + This->Tail;

   if (This->Count < This->BufferLength) //Queue full
   {
	   This->Count = This->Count + Size;
	   This->Tail = (This->Tail + Size);
	   if (This->Tail >= This->BufferLength)
	   {
		   This->Tail = 0;
	   }
	   void *Position = (uint8_t *)This->Buffer + This->Tail;
	   memcpy (Position, Data, Size);
   }
   else
   {
	   return NOK;
   }

   return OK;
}

/**  @fn uint8_t QueueDequeue (Queue *This, void *Data)
 *   @Required execution rate: Evento.
 *   @brief Retira o dado mais antigo do buffer circular FIFO
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @param *Data: Ponteiro para a estrutura que será armazenado o dado retirado do buffer.
 *   @return OK ou NOK
**/
uint8_t QueueDequeue (Queue *This, void *Data)
{
	uint16_t Size;

   if (This->Count == 0)
   {
	   return NOK;
   }
   else
   {
	   Size = This->SizeOfData;
	   void *Position = (uint8_t *)This->Buffer + This->Head;
	   memcpy(Data, Position, Size);
	   This->Head = (This->Head + Size);
	   if (This->Head >=This->BufferLength)
	   {
		   This->Head  = 0;
	   }
	   This->Count = This->Count - Size;
   }
   return OK;
}

/**  @fn uint8_t QueueRead (Queue *This, void *Data)
 *   @Required execution rate: Evento
 *   @brief Lê dado mais antigo do buffer FIFO, sem retirá-lo da fila
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @param *Data: Ponteiro para a estrutura que será armazenado o dado lido do buffer.
 *   @return OK ou NOK
**/
uint8_t QueueRead (Queue *This, void *Data)
{
	uint16_t Size = This->SizeOfData;
   void *Position = (uint8_t *)This->Buffer + This->Head;
   
   if (!This->Count) //Queue empty
   {
      return NOK;
   }
   
   memcpy (Data, Position, Size);
   
   return OK;
}

/**  @fn uint8_t QueueFull (Queue *This)
 *   @Required execution rate: Evento
 *   @brief Verifica se o buffer está cheio
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @return 1: TRUE 0:FALSE
**/
uint8_t QueueFull (Queue *This)
{
	return (This->Count >= This->BufferLength) ? 1 : 0;
}

/**  @fn uint8_t QueueEmpty (Queue *This)
 *   @Required execution rate: Evento
 *   @brief Verifica se o buffer está vazio
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @return 1: TRUE 0:FALSE
**/
uint8_t QueueEmpty (Queue *This)
{
	return (This->Count == 0) ? 1: 0;
}

/**  @fn uint16_t QueueCount (Queue *This)
 *   @Required execution rate: Evento
 *   @brief Verifica quantos dados estão armazenados no buffer
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @return Número de dados no buffer
**/
uint16_t QueueCount (Queue *This)
{
	return This->Count;
}

/**  @fn void QueueInfo(Queue *This)
 *   @Required execution rate: Evento
 *   @brief Printf das variáveis de controle do buffer
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @return void
**/
void QueueInfo(Queue *This)
{
   /*
   printf("DataCount: %u\n",This->DataCount);
   printf("SizeOfData: %u\n",This->SizeOfData);
   printf("Tail: %u\n",This->Tail);
   printf("Head: %u\n",This->Head);
   printf("Buffer: %u\n",This->Buffer);
   printf("BufferLength: %u\n",This->BufferLength);
   */
}

/**  @fn void QueueFlush (Queue *This)
 *   @Required execution rate: Evento
 *   @brief Limpa buffer FIFO
 *   @param *This: Ponteiro para a estrutura Queue.
 *   @return void
**/
void QueueFlush (Queue *This)
{
	This->Head = 0;
	This->Tail = 0xFFFF - (This->SizeOfData - 1);
	This->Count = 0;
}






