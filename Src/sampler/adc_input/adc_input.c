#include "adc_input.h"

static void MX_TIM2_Init(void);
static void MX_ADC2_Init(void);

volatile uint16_t adc_buffer[ADC_BUFFER_SIZE] = {0};

void init_adc_capture(ADC_HandleTypeDef* adc_in, TIM_HandleTypeDef* htim_in){
	sample_in = adc_in;
	sample_tim = htim_in;

	MX_TIM2_Init();
	MX_ADC2_Init();

  
	HAL_ADC_Start_DMA(sample_in, (uint32_t*)&adc_buffer, ADC_BUFFER_SIZE);
  HAL_TIM_Base_Start_IT(sample_tim);
}

void update_capture_freq(uint8_t timescale){
  uint16_t prescaler;
  uint16_t period;
  switch(timescale){

    case 0 : // 5s=>5Hz=5s
      prescaler=5375;period=3124;
    break;
    
    case 1 : // 2s=>12,5Hz=80ms
      prescaler=2687;period=2499;
    break;
    
    case 2 : // 1s=>25Hz=40ms
      prescaler=1343;period=2499;
    break;
    
    case 3 : // 500ms=>50Hz=20ms
      prescaler=671;period=2499;
    break;
    
    case 4 : // 200ms=>125Hz=8ms
      prescaler=335;period=1999;
    break;
    
    case 5 : // 100ms=>250Hz=4ms
      prescaler=167;period=1999;
    break;
    
    case 6 : // 50ms=>500Hz=2ms
      prescaler=83;period=1999;
    break;
    
    case 7 : // 20ms=>1,25kHz=800us
      prescaler=41;period=1599;
    break;
    
    case 8 : // 10ms=>2,5kHz400us
      prescaler=20;period=1599;
    break;
    
    case 9 : // 5ms=>5kHz=200us
      prescaler=20;period=799;
    break;
    
    case 10 : // 2ms=>12,5kHz=80us
      prescaler=20;period=319;
    break;
    
    case 11 : // 1ms=>25kHz=40us
      prescaler=20;period=159;
    break;
    
    case 12 : // 500us=>50kHz=20us
      prescaler=20;period=79;
    break;
    
    case 13 : // 200us=>125kHz=8us
      prescaler=20;period=31;
    break;
    
    case 14 : // 100us=>250kHz=4us
      prescaler=20;period=15;
    break;
    
    case 15 : // 50us=>500kHz=2us
      prescaler=0;period=1;
    break;
    
    case 16 : // 25us=>1MHz=1us
      prescaler=5;period=1;
    break;
  }

  sample_tim->Init.Prescaler = prescaler;
  sample_tim->Init.Period = period;

  if (HAL_TIM_Base_Init(sample_tim) != HAL_OK)
  {
    Error_Handler();
  }
}

void pauseCapture(void){
  HAL_TIM_Base_Stop(sample_tim);
}
void startCapture(void){
  HAL_TIM_Base_Start_IT(sample_tim);
}

static void MX_TIM2_Init(void){

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  
  sample_tim->Instance = TIM2;
  sample_tim->Init.Prescaler = 10;
  sample_tim->Init.CounterMode = TIM_COUNTERMODE_UP;
  sample_tim->Init.Period = 5;
  sample_tim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  sample_tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

  if (HAL_TIM_Base_Init(sample_tim) != HAL_OK)
  {
    Error_Handler();
  }
  
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  
  if (HAL_TIM_ConfigClockSource(sample_tim, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  
  if (HAL_TIM_OC_Init(sample_tim) != HAL_OK)
  {
    Error_Handler();
  }
  
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  
  if (HAL_TIMEx_MasterConfigSynchronization(sample_tim, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  
  if (HAL_TIM_OC_ConfigChannel(sample_tim, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }

}

static void MX_ADC2_Init(void){

  ADC_ChannelConfTypeDef sConfig = {0};

  //Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
  sample_in->Instance = ADC2;
  sample_in->Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  sample_in->Init.Resolution = ADC_RESOLUTION_12B;
  sample_in->Init.ScanConvMode = DISABLE;
  sample_in->Init.ContinuousConvMode = DISABLE;
  sample_in->Init.DiscontinuousConvMode = DISABLE;
  sample_in->Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
  sample_in->Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_TRGO;
  sample_in->Init.DataAlign = ADC_DATAALIGN_RIGHT;
  sample_in->Init.NbrOfConversion = ADC_BUFFER_SIZE;
  sample_in->Init.DMAContinuousRequests = ENABLE;
  sample_in->Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(sample_in) != HAL_OK)
  {
    Error_Handler();
  }
  
  ///Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(sample_in, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}