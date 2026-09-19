#include "nvic.h"

void Enable_IRQ(uint8_t IRQNumber) {
    uint8_t reg_idx = IRQNumber/32;
    uint8_t bit_idx = IRQNumber%32;
    volatile uint32_t *pNVIC_ISER = NVIC_ISER;
    pNVIC_ISER[reg_idx] |= (1 << bit_idx);
    return;
}

void Disable_IRQ(uint8_t IRQNumber) {
    uint8_t reg_idx = IRQNumber/32;
    uint8_t bit_idx = IRQNumber%32;
    volatile uint32_t *pNVIC_ICER = NVIC_ICER;
    pNVIC_ICER[reg_idx] |= (1 << bit_idx);
    return;
}

void Configure_IRQ_Priority(uint8_t IRQNumber, uint8_t Priority) {
    uint8_t reg_idx = IRQNumber/4;
    uint8_t byte_offset = IRQNumber%4;
    volatile uint32_t *pNVIC_IPR = NVIC_IPR;
    uint8_t prio_val = (Priority << 4) & 0xF0; //Only bit7-4 are implementedin stm
    pNVIC_IPR[reg_idx] |=  (prio_val << (byte_offset*8));
}