//--------------------------------------------------------------
// File     : adc.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __ADC_H
#define __ADC_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "Touch.h"
#include "osci.h"










//--------------------------------------------------------------
// Adressen der ADCs
// (siehe Seite 66+427 vom Referenz Manual)
//--------------------------------------------------------------
#define ADC_BASE_ADR        ((uint32_t)0x40012000)
#define ADC_COM_OFFSET      ((uint32_t)0x00000300)


//--------------------------------------------------------------
// Adressen der Register
// (siehe Seite 427+428 vom Referenz Manual)
//--------------------------------------------------------------
#define ADC_REG_CDR_OFFSET         0x4C

#define ADC1_CDR_ADDRESS    (ADC_BASE_ADR | ADC_COM_OFFSET | ADC_REG_CDR_OFFSET)




//--------------------------------------------------------------
// ADC-Clock
// Max-ADC-Frq = 36MHz
// Grundfrequenz = APB2 (APB2=84MHz @ Sysclock=168MHz)
// M�gliche Vorteiler = 2,4,6,8
//
// Max-Conversion-Time @ 21MHz : (with minimum SampleTime)
//   12bit Resolution : 3+12=15 TCycles => 714ns
//   10bit Resolution : 3+10=13 TCycles => 619ns
//    8bit Resolution : 3+8 =11 TCycles => 523ns
//    6bit Resolution : 3+6 =9  TCycles => 428ns
//--------------------------------------------------------------

//#define ADC1d_VORTEILER     ADC_Prescaler_Div2 // Frq = 42 MHz
#define ADC1d_VORTEILER     ADC_Prescaler_Div4   // Frq = 21 MHz
//#define ADC1d_VORTEILER     ADC_Prescaler_Div6 // Frq = 14 MHz
//#define ADC1d_VORTEILER     ADC_Prescaler_Div8 // Frq = 10.5 MHz


//--------------------------------------------------------------
// Timer-2
//
// Grundfreq = 2*APB1 (APB1=42MHz @ Sysclock=168MHz) => TIM_CLK=84MHz
//
// ADC-FRQ = 84MHz / (PRESCALE+1) / (PERIODE+1)
//
//--------------------------------------------------------------
#define OSZI_TIM2_PERIODE      299
#define OSZI_TIM2_PRESCALE     83




//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
void ADC_change_Frq(void);
void DMA2_Stream0_IRQHandler(void);
void NVIC_Configuration(void);
void TIM2_Configuration(void);
void DMA_Configuration(void);
void ADC_Configuration(void);
void GPIO_Configuration(void);
void RCC_Configuration(void);
void TIM2_IRQHandler() ;



//--------------------------------------------------------------
#endif // __STM32F4_UB_ADC_H
