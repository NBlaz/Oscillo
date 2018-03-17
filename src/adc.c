#include "adc.h"

void ADC_change_Frq(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  uint32_t prescaler, period;

  // Timer anhalten
  TIM_Cmd(TIM2, DISABLE);

  switch(OsciSetup.TimeScale) {
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

  // einstellen der neuen Werte
  TIM_TimeBaseStructure.TIM_Period =  period;
  TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


    // Timer2 enable
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);

}
void RCC_Configuration(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

/***************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  /* ADC Channel 10 -> PC0
     ADC Channel 11 -> PC1
  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/***************************************************************************/
void ADC_Configuration(void)
{
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef ADC_InitStructure;
  /* ADC Common Init */
  ADC_CommonInitStructure.ADC_Mode =ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  // 2 half-words one by one, 1 then 2
  ADC_CommonInitStructure.ADC_TwoSamplingDelay =  ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 1 Channel
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // Conversions Triggered
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T2_TRGO;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel 10 configuration */
  ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_3Cycles);



  // PC1
  /* Enable DMA request after last transfer (Multi-ADC mode)  */
  ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
  /* Enable ADC1 */
  ADC_DMACmd(ADC1, ENABLE);
  ADC_Cmd(ADC1, ENABLE);

}

/**************************************************************************/
void DMA_Configuration(void)
{
  DMA_InitTypeDef DMA_InitStructure;

  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&buffer;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
  // CDR_ADDRESS; Packed ADC1, ADC2
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 300; // Count of 16-bit words
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  /* Enable DMA Stream Half / Transfer Complete interrupt */
  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC | DMA_IT_HT, ENABLE);
  /* DMA2_Stream0 enable */
  DMA_Cmd(DMA2_Stream0, ENABLE);
}
void TIM2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  /* Time base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Period = 1;
   // 200 KHz, from 84 MHz TIM2CLK (ie APB1 = HCLK/4, TIM2CLK = HCLK/2)
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  /* TIM2 TRGO selection */
  TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
  // ADC_ExternalTrigConv_T2_TRGO
 /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

/****************************************************************************/
void NVIC_Configuration(void)
{
 NVIC_InitTypeDef NVIC_InitStructure;
           /* Enable the DMA Stream IRQ Channel */
  NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/***********************************************************************/
void DMA2_Stream0_IRQHandler(void)//Called at 1 KHz for 200 KHz sample rate
{
	int i;
 /* Test on DMA Stream Half Transfer interrupt */
 if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_HTIF0))
 {
  /* Clear DMA Stream Half Transfer interrupt pending bit */
  DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_HTIF0);
  /* Turn LED3 off: Half Transfer */

  // Add code here to process first half of buffer (ping)
 }

 /* Test on DMA Stream Transfer Complete interrupt */
 if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))
 {
  /* Clear DMA Stream Transfer Complete interrupt pending bit */
	 ADC_DMACmd(ADC1,DISABLE);
	 p_oszi_draw_adc();
	 CheckUI();
	 ADC_Configuration();
	 ADC_SoftwareStartConv(ADC1);


  DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);


  /* Turn LED3 on: End of Transfer */

 }
}
