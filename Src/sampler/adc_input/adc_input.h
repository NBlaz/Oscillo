#ifndef ADC_INPUT_H
#define ADC_INPUT_H

#include "stm32f4xx_hal.h"
#include "main.h"

extern volatile uint16_t adc_buffer[300];

ADC_HandleTypeDef* sample_in;
TIM_HandleTypeDef* sample_tim;

void init_adc_capture(ADC_HandleTypeDef* adc_in, TIM_HandleTypeDef* htim_in);
void pauseCapture(void);
void startCapture(void);

#endif