#include "stm32f4xx.h"
#include "defines.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include "tm_stm32f4_adc.h"
#include "Touch.h"
#include "osci.h"
#include "adc.h"


int main(void) {
    //Initialize system
	SystemInit();
	int i;
	int j;
	TM_ILI9341_Init();
	    //Rotate LCD for 90 degrees
	TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
	    //FIll lcd with color
    TM_ILI9341_Fill(ILI9341_COLOR_BLACK);

    /*TM_ILI9341_DrawFilledCircle(10,230,10,ILI9341_COLOR_WHITE);
    TM_ILI9341_DrawFilledCircle(310,230,10,ILI9341_COLOR_GREEN);
    TM_ILI9341_DrawFilledCircle(310,10,10,ILI9341_COLOR_BLUE2);
    TM_ILI9341_DrawFilledCircle(10,10,10,ILI9341_COLOR_RED);*/
    RCC_Configuration();
        	  GPIO_Configuration();
        	  NVIC_Configuration();
        	  TIM2_Configuration();
        	  DMA_Configuration();
        	  ADC_Configuration();
        	  ADC_SoftwareStartConv(ADC1);
    while (1)
    {


    //	CheckUI();
    //DMA_ClearFlag(DMA2_Stream0, DMA_FLAG_TCIF0);
    //while(!DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0));


    }
}
