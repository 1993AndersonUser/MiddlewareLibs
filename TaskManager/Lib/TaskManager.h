
#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "TaskManagerConfig.h"
#include "GenericTypes.h"
#include "TickTimer.h"

#ifndef NULL
#define NULL 0U
#endif

typedef void (*CallbackPtr)(void);

typedef struct Task{
    uint8_t Id;
    TickTimer Timer;
    uint8_t Running;
    CallbackPtr Execute;
    CallbackPtr OnStart;
    CallbackPtr OnStop;
    CallbackPtr OnEnd;
}Task;

void TaskInit(void);
uint8_t TaskCreate(Task *ThisTask, uint32_t Interval, CallbackPtr Execute, CallbackPtr OnStart, CallbackPtr OnStop, CallbackPtr OnEnd);
uint8_t TaskStart(Task *ThisTask);
uint8_t RestartTask(Task *ThisTask);
uint8_t TaskStop(Task *ThisTask);
uint8_t TaskEnd(Task *ThisTask);
uint8_t TaskGetId(Task *ThisTask);
void TaskScheduler(void);

#endif
