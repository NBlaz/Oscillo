#ifndef __OSCI_H__
#define __OSCI_H__

#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "tm_stm32f4_adc.h"
#include "Touch.h"
#include "menu.h"
#include "adc.h"

#define  SCALE_START_X      0   // dont change
#define  SCALE_START_Y      40    // dont change

#define  SCALE_END_X      260   // dont change
#define  SCALE_END_Y      220    // dont change

#define  SCALE_SPACE        25   // dont change
#define  SCALE_ANZ_Y        9    // dont change
#define  SCALE_ANZ_X        13   // dont change

#define  SCALE_W            260
#define  SCALE_H            180

#define  SCALE_MX_PIXEL     SCALE_START_X+SCALE_H
#define  SCALE_MY_PIXEL     SCALE_START_Y+SCALE_W

#define  SCALE_X_MITTE      130
#define  SCALE_Y_MITTE      130




//--------------------------------------------------------------
// Defines zum Umrechnen : ADC-Wert -> Pixel-Wert
//--------------------------------------------------------------
#define  FAKTOR_5V          0.5/124.12
#define  FAKTOR_2V          1.25/124.12
#define  FAKTOR_1V          2.5/124.12
#define  FAKTOR_0V5         5/124.12
#define  FAKTOR_0V2         12.5/124.12
#define  FAKTOR_0V1         25/124.12
typedef struct{
	int source;
	int mode;
	int edge;
}trigger;

typedef struct{
	int TimeScale;
	int AmpScale;
	int timestart;
	int ampstart;
	trigger trigger;
}Setting;

extern Setting OsciSetup;
extern uint16_t buffer[300];
extern uint16_t SortedADC[300];

void CheckUI(void);
void RefreshDisplay(void);
int16_t oszi_adc2pixel(int16_t adc);
void p_oszi_draw_adc(void);
void p_oszi_sort_adc(void);

#endif
