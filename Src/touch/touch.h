/**
  ******************************************************************************
  * @file           : touch.h
  * @brief          : Header for touchscreen driver.
  *                   
  ******************************************************************************
  ******************************************************************************
  */
#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "stm32f4xx_hal.h"
#include "main.h"

typedef struct {
	int x;
	int y;
	int Touch;
}PosXY;

ADC_HandleTypeDef* touchADC;

void touchInit(ADC_HandleTypeDef* touchADCin);
PosXY readTouch(void);


#endif



