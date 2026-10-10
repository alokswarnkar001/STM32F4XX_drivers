#include "gpio.h"
#include "rcc.h"
#include "nvic.h" 

static uint8_t getSyscfgPortVal(GPIO_Regdef_t *pGPIO) {
    uint32_t peri_addr = (uint32_t)pGPIO;
    switch(peri_addr) {
        case GPIOA_BA:
            return GPIOA_EXTICR;

        case GPIOB_BA:
            return GPIOB_EXTICR;

        case GPIOC_BA:
            return GPIOC_EXTICR;

        case GPIOD_BA:
            return GPIOD_EXTICR;

        case GPIOE_BA:
            return GPIOE_EXTICR;

        case GPIOF_BA:
            return GPIOF_EXTICR;

        case GPIOG_BA:
            return GPIOG_EXTICR;

        case GPIOH_BA:
            return GPIOH_EXTICR;

        case GPIOI_BA:
            return GPIOI_EXTICR;

        default:
            return GPIO_INVAID_EXTICR;
    }
}

/*
    GPIO Clock Control APIs
*/
static void GPIO_PeriClockControl(GPIO_Handle_t *pGPIO_Handle, uint8_t EnorDi) {
    uint32_t peri_addr = (uint32_t)pGPIO_Handle->pGPIOx;

    if(EnorDi) {
        RCC_PeriClockEnable(peri_addr);
    }
    else {
        RCC_PeriClockDisable(peri_addr);
    }
}

/*
    GPIO Init and De-init APIs
*/
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle) {
    //Enable the Peripheral clock
    GPIO_PeriClockControl(pGPIO_Handle, ENABLE);

    //Configure mode
    GPIO_Regdef_t *pGPIO = pGPIO_Handle->pGPIOx;
    GPIO_PinConfig_t GPIO_Pincfg = pGPIO_Handle->GPIO_PinConfig;
    uint8_t pin_no = GPIO_Pincfg.GPIO_PinNumber;

    pGPIO->MODER |= (GPIO_Pincfg.GPIO_PinMode << (pin_no*2));

    //Configure ospeed
    pGPIO->OSPEEDR |= (GPIO_Pincfg.GPIO_PinSpeed << (pin_no*2));
    
    //Configure PUPD
    pGPIO->PUPDR |= (GPIO_Pincfg.GPIO_PinPuPdControl << (pin_no*2));

    //Configure Optype
    pGPIO->OTYPER |= (GPIO_Pincfg.GPIO_PinOPType << pin_no);

    //Configure Alternate functionality
    uint8_t afr_idx = pin_no / 8;
    uint8_t pin_offset = pin_no % 8;
    pGPIO->AFR[afr_idx] |= (GPIO_Pincfg.GPIO_PinAltFunMode << (pin_offset*4));
}

void GPIO_DeInit(GPIO_Handle_t *pGPIO_Handle) {
    //Reset the Peripheral Regisers using AHB1RSTR register of RCC
    uint32_t peri_addr = (uint32_t)pGPIO_Handle->pGPIOx;
    RCC_PeriRst(peri_addr);

    //Disable the Peripheral Clock
    GPIO_PeriClockControl(pGPIO_Handle, DISABLE);
}

/*
    GPIO read and write APIs
*/
uint8_t GPIO_ReadFromInputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber) {
    return pGPIOx->IDR & (1 << PinNumber);
}

uint16_t GPIO_ReadFromInputPort(GPIO_Regdef_t *pGPIOx) {
    return pGPIOx->IDR & 0xFFFF;
}

void GPIO_WriteToOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if(Value) {
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else {
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}

void GPIO_WriteToOutputPort(GPIO_Regdef_t *pGPIOx, uint16_t Value) {
    pGPIOx->ODR &= ~0xFFFF;
    pGPIOx->ODR |= (Value & 0xFFFF);
}

void GPIO_ToggleOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1 << PinNumber);
}

/*
    GPIO IRQ Handling APIs
*/
void GPIO_IRQConfig(GPIO_Handle_t *pGPIO_Handle, uint8_t IRQMode, uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi) {
    /*INTR On GPIO Can only be configured if it is input mode using following steps:
        1. Configure Intr as Rising edge or falling edge or both using EXTI RTSR for 
        rising edge, FTSR for falling edge, and RTSR and FTSR (for both rising and falling edge)
        
        2. Select the port using EXTICR register of SYSCFG for the respective pin no
        
        3. Unmask the interrupt on the respective pin no in EXTI ->IMR register
        
        4. Enable the particular EXTI line Intr in NVIC using ISER register
        
        5. Configure the priority using ISPR register of NVIC
    */
    EXTI_Regdef_t *pEXTI = EXTI;
    GPIO_Regdef_t *pGPIO = pGPIO_Handle->pGPIOx;
    GPIO_PinConfig_t GPIO_Pincfg = pGPIO_Handle->GPIO_PinConfig;
    uint8_t pin_no = GPIO_Pincfg.GPIO_PinNumber;
    if(IRQMode == GPIO_MODE_IT_FE) {
        //Configure FTSR of EXTI
        pEXTI->FTSR |= (1 << pin_no);
    } else if(IRQMode == GPIO_MODE_IT_RT) {
        //Configure RTSR of EXTI
        pEXTI->RTSR |= (1 << pin_no);
    } else if(IRQMode == GPIO_MODE_IT_RFT) {
        //Configure Both FTSR and RTSR of EXTI
        pEXTI->FTSR |= (1 << pin_no);
        pEXTI->RTSR |= (1 << pin_no);
    }

    //Configure Port selection using SYSCFG EXTICR Register
    SYSCFG_Regdef_t *pSYSCFG = SYSCFG;
    uint8_t exticr_idx = pin_no / 4;
    uint8_t offset = pin_no % 4;
    uint8_t port_val = getSyscfgPortVal(pGPIO);
    pSYSCFG->EXTICR[exticr_idx] |=  (port_val << (offset*4));

    //Enable Interrupt using EXTI IMR Register
    pEXTI->IMR |= (1 << pin_no);
    
    //Enable/Disable IRQ using NVIC ISER/ICER
    if(EnorDi) {
        Enable_IRQ(IRQNumber);
    }
    else {
        Disable_IRQ(IRQNumber);
    }

    //Set Priority using NVIC IPR
    Configure_IRQ_Priority(IRQNumber,IRQPriority);
}

void GPIO_IRQHandling(uint8_t PinNumber) {
    EXTI_Regdef_t *pEXTI = EXTI;
    if(pEXTI->PR & (1 << PinNumber)) {
        pEXTI->PR |= (1 << PinNumber);
    }
    return;
}
