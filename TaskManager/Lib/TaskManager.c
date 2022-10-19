
#include "TaskManager.h"

Task Tasks[MAX_TASKS];
Task *TaskQueue[MAX_TASKS];
uint8_t NumRegisteredTasks = 0;
uint8_t NextId = 0;

/**
 * @file  TaskManager.c
 * @copyright TONEDERM
 * @Author: Anderson Fortes
*/

/**  @fn void TaskInit(void)
 *   @Required execution rate: Apenas inicialização
 *   @brief Inicializa variáveis auxiliares
 *   @param  void
 *   @return void
**/
void TaskInit(void)
{
   uint8_t i;
   
   for (i = 0; i < MAX_TASKS; i ++)
   {
      TaskQueue[i] = NULL;
   }

   NumRegisteredTasks = 0;
}

uint8_t GetId(void)
{
   uint8_t i;
   uint8_t Id = 0;

   for (i = 0; i < NumRegisteredTasks - 1; i ++)
   {
      if (TaskQueue[i] != NULL && TaskQueue[i]->Id == Id)
      {
         Id ++;
      }
   }

   return Id;
}

/**  @fn uint8_t TaskEnqueue(Task *ThisTask)
 *   @Required execution rate: Evento
 *   @brief Adiciona na fila a task.
 *   @param  *ThisTask: Ponteiro para estrutura da task.
 *   @return OK ou NOK.
**/
uint8_t TaskEnqueue(Task *ThisTask)
{
   if (NumRegisteredTasks < (MAX_TASKS))
   {
      TaskQueue[NumRegisteredTasks] = ThisTask;
      NumRegisteredTasks ++;

      return OK;
   }
   return NOK;
}

/**  @fn uint8_t TaskCreate(Task *ThisTask, uint32_t Interval, CallbackPtr Execute, CallbackPtr OnStart, CallbackPtr OnStop, CallbackPtr OnEnd)
 *   @Required execution rate: Evento
 *   @brief Cria uma nova task.
 *   @param  *ThisTask: Ponteiro para estrutura da task.
 *   @param  Interval: Tempo em ms que a task será executada
 *   @param  Execute: Ponteiro de função para o Callback de estouro de tempo.
 *   @param  OnStart: Ponteiro de função para o Callback de task Start.
 *   @param  OnStop:  Ponteiro de função para o Callback de task Stop.
 *   @param  OnEnd:   Ponteiro de função para o Callback de task onEnd.
 *   @return OK ou NOK.
**/
uint8_t TaskCreate(Task *ThisTask, uint32_t Interval, CallbackPtr Execute, CallbackPtr OnStart, CallbackPtr OnStop, CallbackPtr OnEnd)
{
   if (TaskEnqueue(ThisTask) == OK)
   {
      ThisTask->Id = GetId();
   	  ThisTask->Timer.Interval = Interval;
      ThisTask->Execute = Execute;
      ThisTask->OnStart = OnStart;
      ThisTask->OnStop = OnStop;
      ThisTask->OnEnd = OnEnd;
      ThisTask->Running = 0;
      return OK;
   }

   return NOK;
}

/**  @fn uint8_t TaskStart(Task *ThisTask)
 *   @Required execution rate: Evento
 *   @brief Inicializa a execução da task.
 *   @param  *ThisTask: Ponteiro para estrutura da task.
 *   @return OK ou NOK.
**/
uint8_t TaskStart(Task *ThisTask)
{
   if (ThisTask == NULL)
   {
      return NOK;
   }

   ThisTask->Running = 1;
   TickTimerRestart(&ThisTask->Timer);
   if (ThisTask->OnStart != NULL)
   {
     ThisTask->OnStart();
   }

   return OK;
}

uint8_t TaskRestart(Task *ThisTask)
{
   if (ThisTask == NULL)
   {
      return NOK;
   }

   ThisTask->Running = 1;
   TickTimerRestart(&ThisTask->Timer);

   return OK;
}

/**  @fn uint8_t TaskStop(Task *ThisTask)
 *   @Required execution rate: Evento
 *   @brief Pausa a execução da task.
 *   @param  *ThisTask: Ponteiro para estrutura da task.
 *   @return OK ou NOK.
**/
uint8_t TaskStop(Task *ThisTask)
{
    ThisTask->Running = 0;
    if (ThisTask->OnStop != NULL)
    {
        ThisTask->OnStop();
    }
    return OK;
}

/**  @fn uint8_t TaskEnd(Task *ThisTask)
 *   @Required execution rate: Evento
 *   @brief Retira a task da lista.
 *   @param  *ThisTask: Ponteiro para estrutura da task.
 *   @return OK ou NOK.
**/
uint8_t TaskEnd(Task *ThisTask)
{
    uint8_t Index;
    
    if (ThisTask == NULL)
    {
       return NOK;
    }
    
    ThisTask->Running = 0;
    if (ThisTask->OnEnd != NULL)
    {
        ThisTask->OnEnd();
    }
       
    for (Index = 0; Index < NumRegisteredTasks; Index ++)
    {
       if (TaskQueue[Index] == ThisTask)
       {
          break;
       }
    }
    
    TaskQueue[Index] = NULL;
    
    for (; Index < NumRegisteredTasks - 1; Index ++) //Reorganiza o vetor
    {
       TaskQueue[Index] = TaskQueue[Index + 1];
    }
    
    if (NumRegisteredTasks > 0)
    {
       NumRegisteredTasks --;
    }
    
    return OK;
}

uint8_t TaskGetId(Task *ThisTask)
{
   return ThisTask->Id;
}

/**  @fn void TaskScheduler(void)
 *   @Required execution rate: while(1)
 *   @brief Função que executa as chamadas das tasks registradas.
 *   @param  *ThisTask: Ponteiro para estrutura da task.
 *   @return OK ou NOK.
**/
void TaskScheduler(void)
{
    static int i;

    for (i = 0; i < MAX_TASKS; i ++)
    {
        if (TaskQueue[i] != NULL && TaskQueue[i]->Running)
        {
      	   if (TickTimerExpired(&TaskQueue[i]->Timer) || TaskQueue[i]->Timer.Interval == 0)
            {
      	   	 TickTimerRestart(&TaskQueue[i]->Timer);
                TaskQueue[i]->Execute();
            }
        }
    }
}







