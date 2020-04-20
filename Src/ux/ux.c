/**
  ******************************************************************************
  * File Name          : ux.c
  * Description        : user interface impl
  ******************************************************************************
  ******************************************************************************
  */
#include "ux.h"

uint16_t color=0xFB00;
void refresh_screen(void){
	PosXY pos;
	pos = getTouch();

    if(pos.active_touch == 1){
      TM_ILI9341_DrawFilledCircle(10, 10,  10, ILI9341_COLOR_GREEN);
      while(getTouch().active_touch ==1){
      	color ++;
      	TM_ILI9341_DrawPixel(getTouch().x, getTouch().y, color);
      }
      
    }
    else{
      TM_ILI9341_DrawFilledCircle(10, 10,  10, ILI9341_COLOR_RED);
    }
}