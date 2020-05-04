#ifndef SAMPLER_H
#define SAMPLER_H

#include "adc_input.h"

typedef struct s_sample {
	uint8_t ready;
	uint8_t voltage[320];
} s_sample;

s_sample* o_container;
 
void request_new_sample(volatile s_sample* outbuffer);
void rescale_samples(uint8_t voltbydiv);
void update_samples(void);

#endif