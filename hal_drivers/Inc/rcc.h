#ifndef _RCC_H_
#define _RCC_H_

#include "stm32f407xx.h"

void RCC_PeriClockEnable(uint32_t peri_addr, uint8_t bit_position);
void RCC_PeriClockDisable(uint32_t peri_addr, uint8_t bit_position);
void RCC_PeriRst(uint32_t peri_addr, uint8_t bit_position);
#endif //_RCC_H_