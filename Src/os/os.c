/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : os.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include "os.h"

void os_create_tasks(void){
  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  const osThreadAttr_t defaultTask_attributes = {
    .name = "defaultTask",
    .stack_mem = &defaultTaskBuffer[0],
    .stack_size = sizeof(defaultTaskBuffer),
    .cb_mem = &defaultTaskControlBlock,
    .cb_size = sizeof(defaultTaskControlBlock),
    .priority = (osPriority_t) osPriorityNormal,
  };
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* definition and creation of myTask02 */
  const osThreadAttr_t myTask02_attributes = {
    .name = "myTask02",
    .stack_mem = &myTask02Buffer[0],
    .stack_size = sizeof(myTask02Buffer),
    .cb_mem = &myTask02ControlBlock,
    .cb_size = sizeof(myTask02ControlBlock),
    .priority = (osPriority_t) osPriorityNormal,
  };
  myTask02Handle = osThreadNew(StartTask02, NULL, &myTask02_attributes);

  /* definition and creation of myTask02 */
  const osThreadAttr_t myTask03_attributes = {
    .name = "myTask03",
    .stack_mem = &myTask03Buffer[0],
    .stack_size = sizeof(myTask03Buffer),
    .cb_mem = &myTask03ControlBlock,
    .cb_size = sizeof(myTask03ControlBlock),
    .priority = (osPriority_t) osPriorityNormal,
  };
  myTask03Handle = osThreadNew(StartTask03, NULL, &myTask03_attributes);

}

void StartDefaultTask(void *argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    //refresh_screen();  
    readTouch();
    osDelay(1);
  }
  /* USER CODE END 5 */ 
}

void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  
  for(;;)
  {    
    refresh_screen();
    //osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
    update_samples();
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}