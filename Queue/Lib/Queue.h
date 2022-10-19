
#ifndef QUEUE_H
#define QUEUE_H

#include  "GenericTypes.h"

typedef struct QueueStruct {
	uint16_t Tail;
	uint16_t Head;
	uint16_t Count;
	uint8_t SizeOfData;
    void *Buffer;
    uint16_t BufferLength;
} Queue;

uint8_t QueueInit (Queue *This, void *Buffer, uint16_t BufferLentgh, uint8_t SizeOfData);
uint8_t QueueEnqueue (Queue *This, void *Data);
uint8_t QueueDequeue (Queue *This, void *Data);
uint8_t QueueRead (Queue *This, void *Data);
uint8_t QueueFull (Queue *This);
uint8_t QueueEmpty (Queue *This);
uint16_t QueueCount (Queue *This);
void QueueInfo (Queue *This);
void QueueFlush (Queue *This);

#endif
