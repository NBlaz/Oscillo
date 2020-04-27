/**
  ******************************************************************************
  * File Name          : ux.c
  * Description        : user interface impl
  ******************************************************************************
  ******************************************************************************
  */
#include "ux.h"

uint16_t color=0xFB00;
uint8_t oonce = 0;

uint16_t displaybuffer[300]={0};
void refresh_screen(void){
	PosXY pos;
	pos = getTouch();

  if(oonce == 0){
    
    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);

    TM_ILI9341_DrawFilledCircle(10, 10,  10, ILI9341_COLOR_WHITE);
    TM_ILI9341_DrawFilledCircle(310, 10,  10, ILI9341_COLOR_RED);
    TM_ILI9341_DrawFilledCircle(10, 230,  10, ILI9341_COLOR_BLUE);
    TM_ILI9341_DrawFilledCircle(310, 230,  10, ILI9341_COLOR_YELLOW);

    drawUpperMenu();
    drawSideMenu();

    TM_ILI9341_DrawFilledRectangle(0, 21, 279, 240, ILI9341_COLOR_BLACK);
    oonce=1;
  }

  drawWaveForm();

  if(pos.active_touch == 1){
    TM_ILI9341_DrawFilledCircle(10, 10,  10, ILI9341_COLOR_GREEN);
    while(getTouch().active_touch ==1){
     	color ++;
      TM_ILI9341_DrawFilledCircle(getTouch().x, getTouch().y,  10, ILI9341_COLOR_BLACK);
    	//TM_ILI9341_DrawPixel(getTouch().x, getTouch().y, color);
    }  
  }
  else{
    TM_ILI9341_DrawFilledCircle(10, 10,  10, ILI9341_COLOR_RED);
  }
}

void drawUpperMenu(void){
  TM_ILI9341_DrawRectangle(0, 0, 320, 20, ILI9341_COLOR_WHITE);
  TM_ILI9341_DrawFilledRectangle(0, 0, 320, 20, ILI9341_COLOR_BLUE2);
}

void drawSideMenu(void){
  TM_ILI9341_DrawRectangle(280, 20, 320, 240, ILI9341_COLOR_WHITE);
  TM_ILI9341_DrawFilledRectangle(280, 20, 320, 240, ILI9341_COLOR_BLUE2);
}

void drawWaveForm(void){
  
    uint16_t val,val2;
    TM_ILI9341_DrawFilledRectangle(0, 21, 280, 240, ILI9341_COLOR_BLACK);
  for(int i=0; i<299; i+=2){
    
    val = adc_buffer[i]/10;
    val2 = adc_buffer[i+1]/10; 

    //TM_ILI9341_DrawPixel(i, 50  + displaybuffer[i], ILI9341_COLOR_BLACK);
    //TM_ILI9341_DrawPixel(i, 50 + val, ILI9341_COLOR_YELLOW);
    
    displaybuffer[i] = val;
    TM_ILI9341_DrawLine(i, 25 + val, i+1, 25+ val2, ILI9341_COLOR_YELLOW);

  }

}