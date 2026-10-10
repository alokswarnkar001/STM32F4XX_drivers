#ifndef _RCC_H_
#define _RCC_H_

#include "stm32f407xx.h"

/* RCC enable/reset register bit positions for each peripheral */
typedef enum {
    RCC_AHB1_GPIOA = 0x0,
    RCC_AHB1_GPIOB = 0x1,
    RCC_AHB1_GPIOC = 0x2,
    RCC_AHB1_GPIOD = 0x3,
    RCC_AHB1_GPIOE = 0x4,
    RCC_AHB1_GPIOF = 0x5,
    RCC_AHB1_GPIOG = 0x6,
    RCC_AHB1_GPIOH = 0x7,
    RCC_AHB1_GPIOI = 0x8,
    RCC_AHB1_GPIOJ = 0x9,
    RCC_AHB1_GPIOK = 0xA,
    RCC_APB1_SPI2  = 0xE,
    RCC_APB1_SPI3  = 0xF,
    RCC_APB2_SPI1  = 0xC,
    RCC_APB2_SPI4  = 0xD,
    RCC_APB2_SPI5  = 0x14,
    RCC_APB2_SPI6  = 0x15,
    RCC_INVALID = 0x20,
}RCC_PeriBitPos_t;

void RCC_PeriClockEnable(uint32_t peri_addr);
void RCC_PeriClockDisable(uint32_t peri_addr);
void RCC_PeriRst(uint32_t peri_addr);
#endif //_RCC_H_