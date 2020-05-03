#include "sampler.h"

static uint16_t trigger_level = 2045;
static uint8_t scaler = 19;

void request_new_sample(s_sample* outbuffer){
	o_container = outbuffer;
	o_container->ready = 0;
}

void rescale_samples(uint8_t voltbydiv){
	scaler = voltbydiv;
}

void update_samples(void){
	uint16_t offstart;
	uint8_t trigged;

	if(o_container != NULL && o_container->ready == 0){
	
		for(int i=0; i<300; i++){
			o_container->voltage[i]=adc_buffer[i]/scaler;
		/*	
			if(adc_buffer[i-1] < trigger_level && adc_buffer[i] >= trigger_level && trigged == 0){
				offstart=i;
				trigged = 1;
			}
			
			if(trigged == 1){
				o_container->voltage[i-offstart]=adc_buffer[i]/scaler;
			}
			*/
		}
		/*
		for(int i=0;i<300-offstart;i++){
			o_container->voltage[offstart+i]=adc_buffer[i]/scaler;
		}*/
		o_container->ready = 1;
	}
}