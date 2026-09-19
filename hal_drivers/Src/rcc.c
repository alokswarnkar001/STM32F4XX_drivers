#include "rcc.h"

void RCC_PeriClockEnable(uint32_t peri_addr, uint8_t bit_position) {
    uint32_t bus_domain_ba = peri_addr & 0xFFFF0000U;
    RCC_Regdef_t *pRCC = RCC;

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

void RCC_PeriClockDisable(uint32_t peri_addr, uint8_t bit_position) {
    uint32_t bus_domain_ba = peri_addr & 0xFFFF0000U;
    RCC_Regdef_t *pRCC = RCC;

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

void RCC_PeriRst(uint32_t peri_addr, uint8_t bit_position) {
    uint32_t bus_domain_ba = peri_addr & 0xFFFF0000U;
    RCC_Regdef_t *pRCC = RCC;

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