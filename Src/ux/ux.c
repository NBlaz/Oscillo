/**
  ******************************************************************************
  * File Name          : ux.c
  * Description        : user interface impl
  ******************************************************************************
  ******************************************************************************
  */
#include "ux.h"

static uint8_t oonce = 0;
static volatile s_sample adcMeasure;

void refresh_screen(void){

	PosXY pos;
	pos = getTouch();

  if(oonce == 0){
  
    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);

    drawUpperMenu();

    TM_ILI9341_DrawFilledRectangle(0, 21, 279, 240, ILI9341_COLOR_BLACK);
    request_new_sample(&adcMeasure);
    oonce=1;
  }

  if(adcMeasure.ready == 1){

    drawWaveForm();
    request_new_sample(&adcMeasure);
  }  

  if(pos.active_touch == 1){

    if(getTouch().x > 0 && getTouch().x < 160 && getTouch().y > 0 && getTouch().y < 20){
    
      amp_scale_scroll();
    }
    
    if(getTouch().x > 160 && getTouch().x < 320 && getTouch().y > 0 && getTouch().y < 20){
    
      time_scale_scroll();
    }
  }
}

void drawUpperMenu(void){
  TM_ILI9341_DrawRectangle(0, 0, 319, 19, ILI9341_COLOR_WHITE);
  TM_ILI9341_DrawFilledRectangle(1, 1, 318, 18, ILI9341_COLOR_BLACK);
}

void time_scale_scroll(void){

  PosXY pos;
  uint8_t scale;

  while(getTouch().active_touch == 1)
  {
    pos = getTouch();
    //2Seconds Button
    if (pos.y>20&&pos.y<40){
      TM_ILI9341_DrawFilledRectangle(160,20,320,40,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,26,"2S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
      scale = 0;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,20,320,40,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,26,"2S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);

    }
    //1Second Button
    if (pos.y>40&&pos.y<60){
      TM_ILI9341_DrawFilledRectangle(160,40,320,60,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,46,"1S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 1;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,40,320,60,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,46,"1S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //500mS Button
    if (pos.y>60&&pos.y<80){
      TM_ILI9341_DrawFilledRectangle(160,60,320,80,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,66,"500mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 2;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,60,320,80,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,66,"500mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //200mS button
    if (pos.y>80&&pos.y<100){
      TM_ILI9341_DrawFilledRectangle(160,80,320,100,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,86,"200mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 3;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,80,320,100,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,86,"200mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //100mS button
    if (pos.y>100&&pos.y<120){
      TM_ILI9341_DrawFilledRectangle(160,100,320,120,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,106,"100mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 4;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,100,320,120,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,106,"100mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //50mS button
    if (pos.y>120&&pos.y<140){
      TM_ILI9341_DrawFilledRectangle(160,120,320,140,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,126,"50mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 5;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,120,320,140,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,126,"50mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //20mS button
    if (pos.y>140&&pos.y<160){
      TM_ILI9341_DrawFilledRectangle(160,140,320,160,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,146,"20mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 6;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,140,320,160,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,146,"20mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //10mS button
    if (pos.y>160&&pos.y<180){
      TM_ILI9341_DrawFilledRectangle(160,160,320,180,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,166,"10mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 7;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,160,320,180,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,166,"10mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //5mS button
    if (pos.y>180&&pos.y<200){
      TM_ILI9341_DrawFilledRectangle(160,180,320,200,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,186,"5mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 8;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,180,320,200,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,186,"5mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //2mS button
    if (pos.y>200&&pos.y<220){
      TM_ILI9341_DrawFilledRectangle(160,200,320,220,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(180,206,"2mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 9;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(160,200,320,220,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(180,206,"2mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
  }
  update_capture_freq(scale);
}

void amp_scale_scroll(void){

  PosXY pos;
  uint8_t scale;

  while(getTouch().active_touch ==1){
  
    pos=getTouch();
     
    //0.1V Button
    if (pos.y>20&&pos.y<40){
      TM_ILI9341_DrawFilledRectangle(0,20,160,40,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(20,26,"0.1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 0;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(0,20,160,40,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(20,26,"0.1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);

    }
    //0.2V Button
    if (pos.y>40&&pos.y<60){
      TM_ILI9341_DrawFilledRectangle(0,40,160,60,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(20,46,"0.2V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 1;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(0,40,160,60,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(20,46,"0.2V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //0.5V Button
    if (pos.y>60&&pos.y<80){
      TM_ILI9341_DrawFilledRectangle(0,60,160,80,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(20,66,"0.5V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 2;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(0,60,160,80,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(20,66,"0.5V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
    //1V button
    if (pos.y>80&&pos.y<100){
      TM_ILI9341_DrawFilledRectangle(0,80,160,100,ILI9341_COLOR_GRAY);
      TM_ILI9341_Puts(20,86,"1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_GRAY);
      scale = 3;
    }
    else{
      TM_ILI9341_DrawFilledRectangle(0,80,160,100,ILI9341_COLOR_BLACK);
      TM_ILI9341_Puts(20,86,"1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLACK);
    }
  }
  rescale_samples(scale);
}

void drawSideMenu(void){
  TM_ILI9341_DrawRectangle(280, 20, 320, 240, ILI9341_COLOR_WHITE);
  TM_ILI9341_DrawFilledRectangle(280, 20, 320, 240, ILI9341_COLOR_BLUE2);
}

void drawWaveForm(void){

  TM_ILI9341_DrawFilledRectangle(0, 21, 1, 240, ILI9341_COLOR_BLACK);  
  for(int i=0; i<ADC_BUFFER_SIZE-1; i++){
    TM_ILI9341_DrawFilledRectangle(i+1, 21, i+2, 240, ILI9341_COLOR_BLACK);
    //TM_ILI9341_DrawPixel(i, 50 + adcMeasure.voltage[i], ILI9341_COLOR_BLUE2);
    TM_ILI9341_DrawLine(i, 50 + adcMeasure.voltage[i], i+1, 50 + adcMeasure.voltage[i+1], ILI9341_COLOR_BLUE2);
  }
}