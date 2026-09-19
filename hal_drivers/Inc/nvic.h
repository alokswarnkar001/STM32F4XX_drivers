#ifndef _NVIC_H_
#define _NVIC_H_

#include "stm32f407xx.h"


void Enable_IRQ(uint8_t IRQNumber);
void Disable_IRQ(uint8_t IRQNumber);
void Configure_IRQ_Priority(uint8_t IRQNumber, uint8_t Priority);
#endif //_NVIC_H_

