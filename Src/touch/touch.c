#include "touch.h"

void touchInit(ADC_HandleTypeDef* touchADCin){
	touchADC = touchADCin;
}

PosXY readTouch(void){
	PosXY this;
	int i;
	this.x=0;
	this.y=0;
	this.active_touch=0;

	//A0 PA0 Y+ Vcc(out)/adc (in)
	//A1 PA1 X+ Vcc(out)/adc (in)
	//A2 PA4 Y- Pull/float (out)
	//D8 PA9 X- Pull/float (out)

	//init pins
	GPIO_InitTypeDef GPIOstruct;

	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Rank = 1;
  	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

	GPIOstruct.Pin=GPIO_PIN_0;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);

	GPIOstruct.Pin=GPIO_PIN_1;
	GPIOstruct.Mode=GPIO_MODE_ANALOG;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);

	GPIOstruct.Pin=GPIO_PIN_8;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);

	GPIOstruct.Pin=GPIO_PIN_9;
	GPIOstruct.Mode=GPIO_MODE_INPUT;;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);

	sConfig.Channel = ADC_CHANNEL_1;

	if (HAL_ADC_ConfigChannel(touchADC, &sConfig) != HAL_OK){
		Error_Handler();
	}
	if(HAL_ADC_Start(touchADC) != HAL_OK){
		Error_Handler();
	}
	if(HAL_ADC_PollForConversion(touchADC, 100) != HAL_OK){
		Error_Handler();
	}
	
	this.x=HAL_ADC_GetValue(touchADC);
	
	if(HAL_ADC_Stop(touchADC) != HAL_OK){
		Error_Handler();
	}

	GPIOstruct.Pin=GPIO_PIN_0;
	GPIOstruct.Mode=GPIO_MODE_ANALOG;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);

	GPIOstruct.Pin=GPIO_PIN_1;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);

	GPIOstruct.Pin=GPIO_PIN_8;
	GPIOstruct.Mode=GPIO_MODE_INPUT;;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);


	GPIOstruct.Pin=GPIO_PIN_9;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);

	sConfig.Channel = ADC_CHANNEL_0;

  	if (HAL_ADC_ConfigChannel(touchADC, &sConfig) != HAL_OK){
		Error_Handler();
	}
	if(HAL_ADC_Start(touchADC) != HAL_OK){
		Error_Handler();
	}
	if(HAL_ADC_PollForConversion(touchADC, 100) != HAL_OK){
		Error_Handler();
	}
	
	this.y=HAL_ADC_GetValue(touchADC);
	
	if(HAL_ADC_Stop(touchADC) != HAL_OK){
		Error_Handler();
	}
	
	this.x=(this.x-500)/10.5;
	this.y=240-(this.y-680)/12.4;
	
	if(this.y<0)
		this.y=0;
	if(this.y >240)
		this.y=240;

	if(this.x>5||this.y<240)
		this.active_touch=1;
	else
		this.active_touch=0;
	
	return this;

}
