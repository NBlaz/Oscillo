#include "touch.h"

void touchInit(ADC_HandleTypeDef* touchADCin){
	touchADC = touchADCin;
}

void readTouch(void){
	
	//init pins
	GPIO_InitTypeDef GPIOstruct;
	
	//ADC Channel Config
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Rank = 1;
  	sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

  	//A0 PA0 Y+ Vcc(out))
	GPIOstruct.Pin=GPIO_PIN_0;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_SET);

	//A1 PA1 X+ adc (in)
	GPIOstruct.Pin=GPIO_PIN_1;
	GPIOstruct.Mode=GPIO_MODE_ANALOG;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_RESET);

	//D7 PA8 Y- Pull/
	GPIOstruct.Pin=GPIO_PIN_8;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	
	//D8 PA9 X- float 
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
	
	m_touch.x=HAL_ADC_GetValue(touchADC);
	
	if(HAL_ADC_Stop(touchADC) != HAL_OK){
		Error_Handler();
	}

	//A0 PA0 Y+ adc (in)
	GPIOstruct.Pin=GPIO_PIN_0;
	GPIOstruct.Mode=GPIO_MODE_ANALOG;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0,GPIO_PIN_RESET);

	//A1 PA1 X+ Vcc(out)
	GPIOstruct.Pin=GPIO_PIN_1;
	GPIOstruct.Mode=GPIO_MODE_OUTPUT_PP;
	GPIOstruct.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,GPIO_PIN_SET);

	//D7 PA8 Y- float
	GPIOstruct.Pin=GPIO_PIN_8;
	GPIOstruct.Mode=GPIO_MODE_INPUT;;
	HAL_GPIO_Init(GPIOA,&GPIOstruct);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);

	//D8 PA9 X- Pull
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
	
	m_touch.y=HAL_ADC_GetValue(touchADC);
	
	if(HAL_ADC_Stop(touchADC) != HAL_OK){
		Error_Handler();
	}
	
	// Magic rescaling
	m_touch.x=(m_touch.x-500)/10.5;
	m_touch.y=240-(m_touch.y-680)/12.4;
	
	//Avoid wierd values
	if(m_touch.y < 0)
		m_touch.y = 0;
	if(m_touch.y > 240)
		m_touch.y = 240;

	if(m_touch.x > 320)
		m_touch.x = 320;
	if(m_touch.x < 0)
		m_touch.x = 0;

	//Active touch threshold
	if(m_touch.x>5||m_touch.y<240)
		m_touch.active_touch=1;
	else
		m_touch.active_touch=0;
}

PosXY getTouch(void){
	return m_touch;
}

