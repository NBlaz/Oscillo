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

typedef struct {
	uint16_t x;
	uint16_t y;
	uint8_t active_touch;
}PosXY;

PosXY m_touch;

ADC_HandleTypeDef* touchADC;

void touchInit(ADC_HandleTypeDef* touchADCin);
void readTouch(void);
PosXY getTouch(void);

#endif



