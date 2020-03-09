#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "stm32f4xx_adc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "tm_stm32f4_adc.h"


typedef struct {
	int x;
	int y;
	int Touch;
}PosXY;

PosXY readTouch(void);

#endif
