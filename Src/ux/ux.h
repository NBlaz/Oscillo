/**
  ******************************************************************************
  * @file           : ux.h
  * @brief          : Header for user interface impl.
  *                   
  ******************************************************************************
  ******************************************************************************
  */
#ifndef _UX_H_
#define _UX_H_

#include "stm32f4xx_hal.h"
#include "tm_stm32f4_ili9341.h"
#include "touch.h"
#include "adc_input.h"

void refresh_screen(void);

void drawUpperMenu(void);

void drawSideMenu(void);

void drawWaveForm(void);

#endif