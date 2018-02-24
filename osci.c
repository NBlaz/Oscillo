#include "osci.h"

Setting OsciSetup={
		15,
		0,
		0,
		0,
		70
};
uint16_t buffer[300]={0};
uint16_t SortedADC[300]={0};


void CheckUI(void){
	 PosXY pos;
	 pos=readTouch();
	 if(pos.Touch==1)
	 {
		 //Roll menu Volt/div-------------------------------------------------------
		 if (pos.x>1&&pos.x<160&&pos.y>0&&pos.y<20)
		 {
			// Selects only when released
			 while(readTouch().Touch==1)
			 {
				 pos=readTouch();
				 //0.1V Button
				 if (pos.y>20&&pos.y<40){
					 TM_ILI9341_DrawFilledRectangle(0,20,160,40,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(20,26,"0.1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.AmpScale=0;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(0,20,160,40,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(20,26,"0.1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);

				 }
				 //0.2V Button
				 if (pos.y>40&&pos.y<60){
					 TM_ILI9341_DrawFilledRectangle(0,40,160,60,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(20,46,"0.2V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.AmpScale=1;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(0,40,160,60,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(20,46,"0.2V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //0.5V Button
				 if (pos.y>60&&pos.y<80){
					 TM_ILI9341_DrawFilledRectangle(0,60,160,80,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(20,66,"0.5V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.AmpScale=2;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(0,60,160,80,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(20,66,"0.5V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //1V button
				 if (pos.y>80&&pos.y<100){
					 TM_ILI9341_DrawFilledRectangle(0,80,160,100,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(20,86,"1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.AmpScale=3;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(0,80,160,100,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(20,86,"1V/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }

			 }
			 DrawScreen();
		 }
		 //Roll menu Time/div-------------------------------------------------------
		 if (pos.x>160&&pos.x<320&&pos.y>0&&pos.y<20)
		 {
			 // Selects only when released
			 while(readTouch().Touch==1)
			 {
				 pos=readTouch();
				 //2Seconds Button
				 if (pos.y>20&&pos.y<40){
					 TM_ILI9341_DrawFilledRectangle(160,20,320,40,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,26,"2S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=0;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,20,320,40,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,26,"2S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);

				 }
				 //1Second Button
				 if (pos.y>40&&pos.y<60){
					 TM_ILI9341_DrawFilledRectangle(160,40,320,60,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,46,"1S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=1;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,40,320,60,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,46,"1S/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //500mS Button
				 if (pos.y>60&&pos.y<80){
					 TM_ILI9341_DrawFilledRectangle(160,60,320,80,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,66,"500mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=2;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,60,320,80,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,66,"500mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //200mS button
				 if (pos.y>80&&pos.y<100){
					 TM_ILI9341_DrawFilledRectangle(160,80,320,100,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,86,"200mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=3;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,80,320,100,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,86,"200mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //100mS button
				 if (pos.y>100&&pos.y<120){
					 TM_ILI9341_DrawFilledRectangle(160,100,320,120,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,106,"100mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=4;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,100,320,120,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,106,"100mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //50mS button
				 if (pos.y>120&&pos.y<140){
					 TM_ILI9341_DrawFilledRectangle(160,120,320,140,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,126,"50mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=5;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,120,320,140,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,126,"50mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //20mS button
				 if (pos.y>140&&pos.y<160){
					 TM_ILI9341_DrawFilledRectangle(160,140,320,160,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,146,"20mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=6;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,140,320,160,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,146,"20mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //10mS button
				 if (pos.y>160&&pos.y<180){
					 TM_ILI9341_DrawFilledRectangle(160,160,320,180,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,166,"10mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=7;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,160,320,180,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,166,"10mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //5mS button
				 if (pos.y>180&&pos.y<200){
					 TM_ILI9341_DrawFilledRectangle(160,180,320,200,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,186,"5mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=8;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,180,320,200,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,186,"5mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //2mS button
				 if (pos.y>200&&pos.y<220){
					 TM_ILI9341_DrawFilledRectangle(160,200,320,220,ILI9341_COLOR_BLUE);
					 TM_ILI9341_Puts(180,206,"2mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
					 OsciSetup.TimeScale=9;
				 }
				 else{
					 TM_ILI9341_DrawFilledRectangle(160,200,320,220,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,206,"2mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
				 //2nd Roll of button
				 if (pos.y>220&&pos.y<240){
					 TM_ILI9341_DrawFilledRectangle(160,20,320,240,ILI9341_COLOR_BLUE2);
					 while(readTouch().Touch==1){
						 pos=readTouch();
						 //1mS Button
						 if (pos.y>20&&pos.y<40){
						     TM_ILI9341_DrawFilledRectangle(160,20,320,40,ILI9341_COLOR_BLUE);
						 	 TM_ILI9341_Puts(180,26,"1mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
						 	 OsciSetup.TimeScale=10;
						 }
						 else{
						     TM_ILI9341_DrawFilledRectangle(160,20,320,40,ILI9341_COLOR_BLUE2);
						 	 TM_ILI9341_Puts(180,26,"1mS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
			 				 }
		 				 //500uS Button
		 				 if (pos.y>40&&pos.y<60){
		 					 TM_ILI9341_DrawFilledRectangle(160,40,320,60,ILI9341_COLOR_BLUE);
	 					 	 TM_ILI9341_Puts(180,46,"500uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
	 					 	 OsciSetup.TimeScale=11;
		 				 }
		 				 else{
							 TM_ILI9341_DrawFilledRectangle(160,40,320,60,ILI9341_COLOR_BLUE2);
							 TM_ILI9341_Puts(180,46,"500uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
							 }
						 //200uS Button
						 if (pos.y>60&&pos.y<80){
							 TM_ILI9341_DrawFilledRectangle(160,60,320,80,ILI9341_COLOR_BLUE);
							 TM_ILI9341_Puts(180,66,"200uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
							 OsciSetup.TimeScale=12;
						 }
						 else{
							 TM_ILI9341_DrawFilledRectangle(160,60,320,80,ILI9341_COLOR_BLUE2);
							 TM_ILI9341_Puts(180,66,"200uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
						 }
						 //100µS button
						 if (pos.y>80&&pos.y<100){
						 	TM_ILI9341_DrawFilledRectangle(160,80,320,100,ILI9341_COLOR_BLUE);
						  	TM_ILI9341_Puts(180,86,"100uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
						  	OsciSetup.TimeScale=13;
						 }
						 else{
						 	 TM_ILI9341_DrawFilledRectangle(160,80,320,100,ILI9341_COLOR_BLUE2);
						 	 TM_ILI9341_Puts(180,86,"100uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
						 }
						 //50µS Button
						 if (pos.y>100&&pos.y<120){
						 	 TM_ILI9341_DrawFilledRectangle(160,100,320,120,ILI9341_COLOR_BLUE);
						 	 TM_ILI9341_Puts(180,106,"50uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
						     OsciSetup.TimeScale=14;
						 }
						 else{
						     TM_ILI9341_DrawFilledRectangle(160,100,320,120,ILI9341_COLOR_BLUE2);
						 	 TM_ILI9341_Puts(180,106,"50uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
		 				 }
		 				 //20µS Button
		 				 if (pos.y>120&&pos.y<140){
		 					 TM_ILI9341_DrawFilledRectangle(160,120,320,140,ILI9341_COLOR_BLUE);
		 					 TM_ILI9341_Puts(180,126,"20uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE);
		 					 OsciSetup.TimeScale=15;
		 				 }
		 				 else{
		 					 TM_ILI9341_DrawFilledRectangle(160,120,320,140,ILI9341_COLOR_BLUE2);
		 					 TM_ILI9341_Puts(180,126,"20uS/div",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
		 				 }

					}
				 }
				 else{
				     TM_ILI9341_DrawFilledRectangle(160,220,320,240,ILI9341_COLOR_BLUE2);
					 TM_ILI9341_Puts(180,226,"...",&TM_Font_7x10,ILI9341_COLOR_WHITE,ILI9341_COLOR_BLUE2);
				 }
			 }
			 DrawScreen();
			 ADC_change_Frq();
		 }
		 if(pos.y>21&&pos.y<80&&pos.x>260&&pos.x<320){
			 while(readTouch().Touch==1){
				 pos=readTouch();
				 if(pos.y>21&&pos.y<50&&pos.x>260&&pos.x<320)
					 TM_ILI9341_DrawFilledRectangle(260,21,320,50,ILI9341_COLOR_BLUE);
				 else
					 TM_ILI9341_DrawFilledRectangle(260,21,320,50,ILI9341_COLOR_BLUE2);
				 if(pos.y>51&&pos.y<80&&pos.x>280&&pos.x<340)
					 TM_ILI9341_DrawFilledRectangle(260,51,320,80,ILI9341_COLOR_BLUE);
				 else
					 TM_ILI9341_DrawFilledRectangle(260,51,320,80,ILI9341_COLOR_BLUE2);
			 }
			 if(pos.y>21&&pos.y<50&&pos.x>260&&pos.x<320)
				 OsciSetup.ampstart=OsciSetup.ampstart-5;
		     if(pos.y>51&&pos.y<80&&pos.x>260&&pos.x<340)
		    	 OsciSetup.ampstart=OsciSetup.ampstart+5;

		     DrawScreen();
		     ADC_change_Frq();
		 }

     }
	 return;
}

void RefreshDisplay(void){
	int i,j;

	TM_ILI9341_DrawFilledRectangle(0,21,259,240,ILI9341_COLOR_BLACK);
	for(i=0;i<=SCALE_W;i+=36) {
	    for(j=0;j<=240;j+=36) {
	      TM_ILI9341_DrawPixel(i,j+20,ILI9341_COLOR_WHITE);
	    }
	  }
	return;
}
void p_oszi_draw_adc(void)
{
  uint32_t n=0;
  int punkt=0;;
  int j;
  int16_t ch1_wert1,ch1_wert2;
  //RefreshDisplay();
  p_oszi_sort_adc();

  // startwerte
  ch1_wert1=-oszi_adc2pixel(buffer[0]);
  ch1_wert1+=SCALE_Y_MITTE+OsciSetup.ampstart;
  if(ch1_wert1<SCALE_START_Y) ch1_wert1=SCALE_START_Y;
  if(ch1_wert1>SCALE_H) ch1_wert1=SCALE_H;
  TM_ILI9341_DrawFilledRectangle(0,21,1,240,ILI9341_COLOR_BLACK);

  // komplette Kurve
  for(n=1;n<300;n++) {
	  //erase progessively
	  TM_ILI9341_DrawFilledRectangle((n+1)/1.16,21,(n+2)/1.16,240,ILI9341_COLOR_BLACK);
	  // draw scale column by column
	  if(punkt==36) {
		 for(j=0;j<=240;j+=36){
		  	  TM_ILI9341_DrawPixel(n/1.16,j+20,ILI9341_COLOR_WHITE);
		  	 }
		 punkt=1;
	  }
	  punkt++;

	  //draw the measures
      ch1_wert2=-oszi_adc2pixel(buffer[n]);
      ch1_wert2+=SCALE_Y_MITTE+OsciSetup.ampstart;
      if(ch1_wert2<SCALE_START_Y) ch1_wert2=SCALE_START_Y;
      if(ch1_wert2>SCALE_H) ch1_wert2=SCALE_H;
      TM_ILI9341_DrawLine((SCALE_START_X+n)/1.16,ch1_wert1,(SCALE_START_X+n+1)/1.16,ch1_wert2,ILI9341_COLOR_YELLOW);
      TM_ILI9341_DrawPixel((SCALE_START_X+n)/1.16,SCALE_Y_MITTE+OsciSetup.ampstart,ILI9341_COLOR_WHITE);
      ch1_wert1=ch1_wert2;
  }
  return;
}

int16_t oszi_adc2pixel(int16_t adc)
{
  int16_t ret_wert=0;

  switch(OsciSetup.AmpScale) {
    case 5 : ret_wert=adc*FAKTOR_5V;break;
    case 4 : ret_wert=adc*FAKTOR_2V;break;
    case 3 : ret_wert=adc*FAKTOR_1V;break;
    case 2 : ret_wert=adc*FAKTOR_0V5;break;
    case 1 : ret_wert=adc*FAKTOR_0V2;break;
    case 0 : ret_wert=adc*FAKTOR_0V1;break;
  }

  return(ret_wert);
}

void p_oszi_sort_adc(void)
{
  int n=0;
  uint16_t wert,wert1, wert2;
  int trigger=10;
  int trigged=0;
  int i,j;

  while(trigged==0&&n<300){
	  wert=oszi_adc2pixel(buffer[n]);

	  if(wert==0 && oszi_adc2pixel(buffer[n+1])>0)
	  {
		  trigged=1;
	  }
	  n++;
  }
  wert2=300-n;
  for(i=0;i<wert2;i++){
	  SortedADC[i]=buffer[i+n];
	  wert1=i;
  }

  for(j=0;j<n;j++){
	  SortedADC[j]=buffer[j+n-1];

  }
  return;
}
