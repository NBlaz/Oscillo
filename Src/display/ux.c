/**
  ******************************************************************************
  * File Name          : ux.c
  * Description        : user interface impl
  ******************************************************************************
  ******************************************************************************
  */
#include "ux.h"

void refresh_screen(void){
	PosXY pos;
	pos = getTouch();
    if(pos.active_touch == 1){
      TM_ILI9341_DrawPixel(pos.x, pos.y, ILI9341_COLOR_BLUE);
      TM_ILI9341_Puts(100,100,"on",&TM_Font_7x10,ILI9341_COLOR_GREEN,ILI9341_COLOR_BLACK);
    }
    else{
      TM_ILI9341_Puts(100,100,"off",&TM_Font_7x10,ILI9341_COLOR_RED,ILI9341_COLOR_BLACK);
    }
}