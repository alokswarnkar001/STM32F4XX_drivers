#ifndef _GPIO_DRV_H_
#define _GPIO_DRV_H_

#include "stm32f407xx.h"

typedef struct {
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinOPType;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinAltFunMode;
}GPIO_PinConfig_t;

typedef struct {
    GPIO_Regdef_t *pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig;
}GPIO_Handle_t;


/*****Register configuration enums */

/* GPIO Pin Number possible types */
typedef enum {
    GPIO_PIN_NO_0  = 0x0,
    GPIO_PIN_NO_1  = 0x1,
    GPIO_PIN_NO_2  = 0x2,
    GPIO_PIN_NO_3  = 0x3,
    GPIO_PIN_NO_4  = 0x4,
    GPIO_PIN_NO_5  = 0x5,
    GPIO_PIN_NO_6  = 0x6,
    GPIO_PIN_NO_7  = 0x7,
    GPIO_PIN_NO_8  = 0x8,
    GPIO_PIN_NO_9  = 0x9,
    GPIO_PIN_NO_10 = 0xA,
    GPIO_PIN_NO_11 = 0xB,
    GPIO_PIN_NO_12 = 0xC,
    GPIO_PIN_NO_13 = 0xD,
    GPIO_PIN_NO_14 = 0xE,
    GPIO_PIN_NO_15 = 0xF
}GPIO_PinNumber_t;

/* GPIO mode configurable values*/
typedef enum {
    GPIO_MODE_IN     = 0x0,
    GPIO_MODE_OUT    = 0x1,
    GPIO_MODE_ALTFN  = 0x2,
    GPIO_MODE_ANALOG = 0x3
}GPIO_Mode_t;

/* Configure Inerrupt mode*/
typedef enum {
    GPIO_MODE_IT_FE  = 0x1,
    GPIO_MODE_IT_RT  = 0x2,
    GPIO_MODE_IT_RFT = 0x3
}GPIO_IRQMode_t;

/*GPIO possible output types */
typedef enum {
    GPIO_OP_TYPE_PP = 0x0,
    GPIO_OP_TYPE_OD = 0x1
}GPIO_OPType_t;

/* GPIO possible speed types*/
typedef enum {
    GPIO_SPEED_LOW    = 0x0,
    GPIO_SPEED_MEDIUM = 0x1,
    GPIO_SPEED_FAST   = 0x2,
    GPIO_SPEED_HIGH   = 0x3
}GPIO_Speed_t;

/* GPIO PUPD possible types*/
typedef enum {
    GPIO_NO_PUPD = 0x0,
    GPIO_PIN_PU  = 0x1,
    GPIO_PIN_PD  = 0x2
}GPIO_PUPD_t;

/* GPIO AFR possible types*/
typedef enum {
    GPIO_AF0  = 0x0,
    GPIO_AF1  = 0x1,
    GPIO_AF2  = 0x2,
    GPIO_AF3  = 0x3,
    GPIO_AF4  = 0x4,
    GPIO_AF5  = 0x5,
    GPIO_AF6  = 0x6,
    GPIO_AF7  = 0x7,
    GPIO_AF8  = 0x8,
    GPIO_AF9  = 0x9,
    GPIO_AF10 = 0xA,
    GPIO_AF11 = 0xB,
    GPIO_AF12 = 0xC,
    GPIO_AF13 = 0xD,
    GPIO_AF14 = 0xE,
    GPIO_AF15 = 0xF
}GPIO_AltFn_t;

/* GPIO Peri RCC Bit position values*/
typedef enum {
    GPIOA_RCC_BIT        = 0x0,
    GPIOB_RCC_BIT        = 0x1,
    GPIOC_RCC_BIT        = 0x2,
    GPIOD_RCC_BIT        = 0x3,
    GPIOE_RCC_BIT        = 0x4,
    GPIOF_RCC_BIT        = 0x5,
    GPIOG_RCC_BIT        = 0x6,
    GPIOH_RCC_BIT        = 0x7,
    GPIOI_RCC_BIT        = 0x8,
    GPIOJ_RCC_BIT        = 0x9,
    GPIOK_RCC_BIT        = 0xA,
    GPIO_INVALID_RCC_BIT = 0x20
}GPIO_RCCBit_t;

/* SYSCFG EXTICR possible types*/
typedef enum {
    GPIOA_EXTICR       = 0x0,
    GPIOB_EXTICR       = 0x1,
    GPIOC_EXTICR       = 0x2,
    GPIOD_EXTICR       = 0x3,
    GPIOE_EXTICR       = 0x4,
    GPIOF_EXTICR       = 0x5,
    GPIOG_EXTICR       = 0x6,
    GPIOH_EXTICR       = 0x7,
    GPIOI_EXTICR       = 0x8,
    GPIO_INVAID_EXTICR = 0x9
}GPIO_EXTICR_t;

/*********************************APIs Supported by Driver*********************************/

/*
    GPIO Init and De-init APIs
*/
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle);
void GPIO_DeInit(GPIO_Handle_t *pGPIO_Handle);

/*
    GPIO read and write APIs
*/
uint8_t GPIO_ReadFromInputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_Regdef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_Regdef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber);

/*
    GPIO IRQ Handling APIs
*/
void GPIO_IRQConfig(GPIO_Handle_t *pGPIO_Handle, uint8_t IRQMode, uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);

#endif //_GPIO_DRV_H_