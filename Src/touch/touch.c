#include "touch.h"

void touchInit(ADC_HandleTypeDef* touchADCin){
	touchADC = touchADCin;

	//init pins
	GPIO_InitTypeDef GPIOstruct;
	GPIOstruct.Pin=GPIO_PIN_0;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);


	GPIOstruct.Pin=GPIO_PIN_4;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_OD;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

	GPIOstruct.Pin=GPIO_PIN_9;
	GPIOstruct.Mode=GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);

	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = ADC_CHANNEL_1;
  	sConfig.Rank = 1;
  	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

  	if (HAL_ADC_ConfigChannel(touchADC, &sConfig) != HAL_OK)
  	{
		Error_Handler();
	}
}

PosXY readTouch(void){
	PosXY this;
	int i;
	this.x=0;
	this.y=0;
	this.Touch=0;

	//A0 PA0 Y+ Vcc(out)/adc (in)
	//A1 PA1 X+ Vcc(out)/adc (in)
	//A2 PA4 Y- Pull/float (out)
	//D8 PA9 X- Pull/float (out)

	

	//for(i=0;i<10;i++)
	//	this.x=this.x+HAL_ADC_GetValue(touchADC);
	
	
	this.x=HAL_ADC_GetValue(touchADC);
	/*

	GPIOstruct.GPIO_Pin=GPIO_Pin_9;
	GPIOstruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIOstruct.GPIO_OType=GPIO_OType_PP;
	GPIOstruct.GPIO_Speed=GPIO_Speed_25MHz;
	GPIOstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA,&GPIOstruct);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);

	//GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	if(this.x<0)
		this.x=0;


	GPIOstruct.GPIO_Pin=GPIO_Pin_1;
		GPIOstruct.GPIO_Mode=GPIO_Mode_OUT;
		GPIOstruct.GPIO_OType=GPIO_OType_PP;
		GPIOstruct.GPIO_Speed=GPIO_Speed_25MHz;
		GPIOstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOA,&GPIOstruct);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);


		GPIOstruct.GPIO_Pin=GPIO_Pin_9;
		GPIOstruct.GPIO_OType=GPIO_OType_PP;
		GPIO_Init(GPIOA,&GPIOstruct);
		GPIO_ResetBits(GPIOA,GPIO_Pin_9);

		GPIOstruct.GPIO_Pin=GPIO_Pin_4;
		GPIOstruct.GPIO_Mode=GPIO_Mode_IN;
		GPIOstruct.GPIO_OType=GPIO_OType_PP;
		GPIOstruct.GPIO_Speed=GPIO_Speed_25MHz;
		GPIOstruct.GPIO_PuPd=GPIO_PuPd_UP;
		GPIO_Init(GPIOA,&GPIOstruct);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);

		sConfig.Channel = ADC_CHANNEL_1;
  		sConfig.Rank = 1;
  		sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

  		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  		{
			while(1){}
		}
		for(i=0;i<10;i++)
			this.y=this.y+HAL_ADC_GetValue(&hadc1);

		this.y=this.y/10;

		GPIOstruct.GPIO_Pin=GPIO_Pin_4;
				GPIOstruct.GPIO_Mode=GPIO_Mode_OUT;
				GPIOstruct.GPIO_OType=GPIO_OType_PP;
				GPIOstruct.GPIO_Speed=GPIO_Speed_25MHz;
				GPIOstruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
				GPIO_Init(GPIOA,&GPIOstruct);
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		//GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	*/
	if(this.y<0)
		this.y=0;

	this.x=(this.x-500)/10;
	this.y=240-(this.y-680)/12.4;
	
	if(this.x<320||this.y>5)
		this.Touch=1;
	else
		this.Touch=0;
	
	return this;

}
