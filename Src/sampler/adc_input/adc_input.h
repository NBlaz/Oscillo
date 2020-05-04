#ifndef ADC_INPUT_H
#define ADC_INPUT_H

#include "stm32f4xx_hal.h"
#include "main.h"

#define ADC_BUFFER_SIZE 320

extern volatile uint16_t adc_buffer[ADC_BUFFER_SIZE];

ADC_HandleTypeDef* sample_in;
TIM_HandleTypeDef* sample_tim;

void init_adc_capture(ADC_HandleTypeDef* adc_in, TIM_HandleTypeDef* htim_in);
void update_capture_freq(uint8_t timescale);
void pauseCapture(void);
void startCapture(void);

#endif