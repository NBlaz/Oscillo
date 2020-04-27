#include "adc_input.h"


volatile uint16_t adc_buffer[300] = {0};

void init_adc_capture(ADC_HandleTypeDef* adc_in, TIM_HandleTypeDef* htim_in){
	sample_in = adc_in;
	sample_tim = htim_in;

	HAL_ADC_Start_DMA(sample_in, (uint32_t*)&adc_buffer, 300);
	HAL_TIM_Base_Start_IT(sample_tim);
}