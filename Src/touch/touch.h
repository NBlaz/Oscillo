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
	uint16_t x;
	uint16_t y;
	uint8_t active_touch;
}PosXY;

ADC_HandleTypeDef* touchADC;

void touchInit(ADC_HandleTypeDef* touchADCin);
PosXY readTouch(void);


#endif



