#ifndef _OS_H
#define _OS_H

#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"
#include "touch.h"
#include "sampler.h"
#include "ux.h"

typedef StaticTask_t osStaticThreadDef_t;

osThreadId_t defaultTaskHandle;
uint32_t defaultTaskBuffer[ 128 ];
osStaticThreadDef_t defaultTaskControlBlock;

osThreadId_t myTask02Handle;
uint32_t myTask02Buffer[ 128 ];
osStaticThreadDef_t myTask02ControlBlock;

osThreadId_t myTask03Handle;
uint32_t myTask03Buffer[ 128 ];
osStaticThreadDef_t myTask03ControlBlock;

void os_create_tasks(void);

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

#endif