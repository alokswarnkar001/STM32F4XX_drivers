#include "rcc.h"

//Maps a peripheral base address to its RCC enable/reset register bit position
uint8_t RCC_GetPeriBitPos(uint32_t peri_addr) {
    switch(peri_addr) {
        case GPIOA_BA:
            return RCC_AHB1_GPIOA;

        case GPIOB_BA:
            return RCC_AHB1_GPIOB;

        case GPIOC_BA:
            return RCC_AHB1_GPIOC;

        case GPIOD_BA:
            return RCC_AHB1_GPIOD;

        case GPIOE_BA:
            return RCC_AHB1_GPIOE;

        case GPIOF_BA:
            return RCC_AHB1_GPIOF;

        case GPIOG_BA:
            return RCC_AHB1_GPIOG;

        case GPIOH_BA:
            return RCC_AHB1_GPIOH;

        case GPIOI_BA:
            return RCC_AHB1_GPIOI;

        case GPIOJ_BA:
            return RCC_AHB1_GPIOJ;

        case GPIOK_BA:
            return RCC_AHB1_GPIOK;

        case SPI1_BA:
            return RCC_APB2_SPI1;

        case SPI2_BA:
            return RCC_APB1_SPI2;

        case SPI3_BA:
            return RCC_APB1_SPI3;

        case SPI4_BA:
            return RCC_APB2_SPI4;

        case SPI5_BA:
            return RCC_APB2_SPI5;

        case SPI6_BA:
            return RCC_APB2_SPI6;

        default:
            return RCC_INVALID;
    }
}

void RCC_PeriClockEnable(uint32_t peri_addr) {
    uint32_t bus_domain_ba = peri_addr & 0xFFFF0000U;
    RCC_Regdef_t *pRCC = RCC;
    uint8_t bit_position = RCC_GetPeriBitPos(peri_addr);

    switch(bus_domain_ba) {
        case AHB1_BA:
            pRCC->AHB1ENR |= (1U << bit_position);
            break;

        case AHB2_BA:
            pRCC->AHB2ENR |= (1U << bit_position);
            break;

        case APB1_BA:
            pRCC->APB1ENR |= (1U << bit_position);
            break;

        case APB2_BA:
            pRCC->APB2ENR |= (1U << bit_position);
            break;

        default:
            break;
    }
}

void RCC_PeriClockDisable(uint32_t peri_addr) {
    uint32_t bus_domain_ba = peri_addr & 0xFFFF0000U;
    RCC_Regdef_t *pRCC = RCC;
    uint8_t bit_position = RCC_GetPeriBitPos(peri_addr);

    switch(bus_domain_ba) {
        case AHB1_BA:
            pRCC->AHB1ENR &= ~(1U << bit_position);
            break;

        case AHB2_BA:
            pRCC->AHB2ENR &= ~(1U << bit_position);
            break;

        case APB1_BA:
            pRCC->APB1ENR &= ~(1U << bit_position);
            break;

        case APB2_BA:
            pRCC->APB2ENR &= ~(1U << bit_position);
            break;

        default:
            break;
    }
}

void RCC_PeriRst(uint32_t peri_addr) {
    uint32_t bus_domain_ba = peri_addr & 0xFFFF0000U;
    RCC_Regdef_t *pRCC = RCC;
    uint8_t bit_position = RCC_GetPeriBitPos(peri_addr);
    //To reset an peripheral registers first set the respective bit and immediately clear the bit
    //otherwise, the Peripheral will remain always in reset state
    switch(bus_domain_ba) {
        case AHB1_BA:
            pRCC->AHB1RSTR |= (1U << bit_position);
            pRCC->AHB1RSTR &= ~(1U << bit_position);
            break;

        case AHB2_BA:
            pRCC->AHB2RSTR |= (1U << bit_position);
            pRCC->AHB2RSTR &= ~(1U << bit_position);
            break;

        case APB1_BA:
            pRCC->APB1RSTR |= (1U << bit_position);
            pRCC->APB1RSTR &= ~(1U << bit_position);
            break;

        case APB2_BA:
            pRCC->APB2RSTR |= (1U << bit_position);
            pRCC->APB2RSTR &= ~(1U << bit_position);
            break;

        default:
            break;
    }
}