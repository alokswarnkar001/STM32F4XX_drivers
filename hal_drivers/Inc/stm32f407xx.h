#ifndef _STM32F407XX_H_
#define _STM32F407XX_H_

#include <stdint.h>

//Base addresses of Different mem regions
#define FLASH_BA     0x08000000U
#define ROM_BA       0x1FFF0000U
#define SRAM1_BA     0x20000000U
#define SRAM2_BA     0x2001C000U

//base addresses for Bus domains
#define PERIPHERAL_BA 0x40000000U
#define APB1_BA       PERIPHERAL_BA
#define APB2_BA       0x40010000U
#define AHB1_BA       0x40020000U
#define AHB2_BA       0x50000000U
#define AHB3_BA       0x60000000U

//base Address for AHB1 Peripherals
#define GPIOA_BA    (AHB1_BA + 0x0000U)
#define GPIOB_BA    (AHB1_BA + 0x0400U)
#define GPIOC_BA    (AHB1_BA + 0x0800U)
#define GPIOD_BA    (AHB1_BA + 0x0C00U)
#define GPIOE_BA    (AHB1_BA + 0x1000U)
#define GPIOF_BA    (AHB1_BA + 0x1400U)
#define GPIOG_BA    (AHB1_BA + 0x1800U)
#define GPIOH_BA    (AHB1_BA + 0x1C00U)
#define GPIOI_BA    (AHB1_BA + 0x2000U)
#define GPIOJ_BA    (AHB1_BA + 0x2400U)
#define GPIOK_BA    (AHB1_BA + 0x2800U)
#define RCC_BA      (AHB1_BA + 0x3800U)

//base Address for APB1 Peripherals
#define SPI2_BA     (APB1_BA + 0x3800U)
#define SPI3_BA     (APB1_BA + 0x3C00U)
#define USART2_BA   (APB1_BA + 0x4400U)
#define USART3_BA   (APB1_BA + 0x4800U)
#define UART4_BA    (APB1_BA + 0x4C00U)
#define UART5_BA    (APB1_BA + 0x5000U)
#define I2C1_BA     (APB1_BA + 0x5400U)
#define I2C2_BA     (APB1_BA + 0x5800U)
#define I2C3_BA     (APB1_BA + 0x5C00U)
#define UART7_BA    (APB1_BA + 0x7800U)
#define UART8_BA    (APB1_BA + 0x7C00U)

//Base address for APB2 Peripherals
#define USART1_BA   (APB2_BA + 0x1000U)
#define USART6_BA   (APB2_BA + 0x1400U)
#define SPI1_BA     (APB2_BA + 0x3000U)
#define SPI4_BA     (APB2_BA + 0x3400U)
#define SYSCFG_BA   (APB2_BA + 0x3800U)
#define EXTI_BA     (APB2_BA + 0x3C00U)
#define SPI5_BA     (APB2_BA + 0x5000U)
#define SPI6_BA     (APB2_BA + 0x5400U)

//Base address for NVIC Peripheral
#define NVIC_ISER    (volatile uint32_t *)0xE000E100U
#define NVIC_ICER    (volatile uint32_t *)0xE000E180U
#define NVIC_ISPR    (volatile uint32_t *)0xE000E200U
#define NVIC_ICPR    (volatile uint32_t *)0xE000E280U
#define NVIC_IABR    (volatile uint32_t *)0xE000E300U
#define NVIC_IPR     (volatile uint32_t *)0xE000E400U   



/****************Peripheral Register Definitions****************/

/* GPIO Peripheral */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
}GPIO_Regdef_t;

/*RCC Peripheral*/
typedef struct {
    volatile uint32_t CR;         /* 0x00 */
    volatile uint32_t PLLCFGR;    /* 0x04 */
    volatile uint32_t CFGR;        /* 0x08 */
    volatile uint32_t CIR;         /* 0x0C */
    volatile uint32_t AHB1RSTR;    /* 0x10 */
    volatile uint32_t AHB2RSTR;    /* 0x14 */
    volatile uint32_t AHB3RSTR;    /* 0x18 */
    volatile uint32_t RESERVED0;   /* 0x1C */
    volatile uint32_t APB1RSTR;    /* 0x20 */
    volatile uint32_t APB2RSTR;    /* 0x24 */
    volatile uint32_t RESERVED1[2]; /* 0x28, 0x2C */
    volatile uint32_t AHB1ENR;     /* 0x30 */
    volatile uint32_t AHB2ENR;     /* 0x34 */
    volatile uint32_t AHB3ENR;     /* 0x38 */
    volatile uint32_t RESERVED2;   /* 0x3C */
    volatile uint32_t APB1ENR;     /* 0x40 */
    volatile uint32_t APB2ENR;     /* 0x44 */
    volatile uint32_t RESERVED3[2]; /* 0x48, 0x4C */
    volatile uint32_t AHB1LPENR;   /* 0x50 */
    volatile uint32_t AHB2LPENR;   /* 0x54 */
    volatile uint32_t AHB3LPENR;   /* 0x58 */
    volatile uint32_t RESERVED4;   /* 0x5C */
    volatile uint32_t APB1LPENR;   /* 0x60 */
    volatile uint32_t APB2LPENR;   /* 0x64 */
    volatile uint32_t RESERVED5[2]; /* 0x68, 0x6C */
    volatile uint32_t BDCR;        /* 0x70 */
    volatile uint32_t CSR;         /* 0x74 */
    volatile uint32_t RESERVED6[2]; /* 0x78, 0x7C */
    volatile uint32_t SSCGR;       /* 0x80 */
    volatile uint32_t PLLI2SCFGR;  /* 0x84 */
    volatile uint32_t PLLSAICFGR;  /* 0x88 */
    volatile uint32_t DCKCFGR;     /* 0x8C */
}RCC_Regdef_t;

/*EXTI Peripheral*/
typedef struct {
    volatile uint32_t IMR;    /* 0x00, Interrupt mask register */
    volatile uint32_t EMR;    /* 0x04, Event mask register */
    volatile uint32_t RTSR;   /* 0x08, Rising trigger selection register */
    volatile uint32_t FTSR;   /* 0x0C, Falling trigger selection register */
    volatile uint32_t SWIER;  /* 0x10, Software interrupt event register */
    volatile uint32_t PR;     /* 0x14, Pending register */
}EXTI_Regdef_t;

/*SYSCFG Peripheral*/
typedef struct {
    volatile uint32_t MEMRMP;      /* 0x00, Memory remap register */
    volatile uint32_t PMC;         /* 0x04, Peripheral mode configuration register */
    volatile uint32_t EXTICR[4];   /* 0x08-0x14, External interrupt configuration registers 1-4 */
    volatile uint32_t RESERVED[2]; /* 0x18, 0x1C */
    volatile uint32_t CMPCR;       /* 0x20, Compensation cell control register */
}SYSCFG_Regdef_t;

/*SPI Peripheral*/
typedef struct {
    volatile uint32_t CR1;      /* 0x00, Control register 1 */
    volatile uint32_t CR2;      /* 0x04, Control register 2 */
    volatile uint32_t SR;       /* 0x08, Status register */
    volatile uint32_t DR;       /* 0x0C, Data register */
    volatile uint32_t CRCPR;    /* 0x10, CRC polynomial register */
    volatile uint32_t RXCRCR;   /* 0x14, RX CRC register */
    volatile uint32_t TXCRCR;   /* 0x18, TX CRC register */
    volatile uint32_t I2SCFGR;  /* 0x1C, I2S configuration register */
    volatile uint32_t I2SPR;    /* 0x20, I2S prescaler register */
}SPI_Regdef_t;


/****************Peripheral Definitions (Peripheral base addresses typecasted)****************/

#define GPIOA   ((GPIO_Regdef_t *)GPIOA_BA)
#define GPIOB   ((GPIO_Regdef_t *)GPIOB_BA)
#define GPIOC   ((GPIO_Regdef_t *)GPIOC_BA)
#define GPIOD   ((GPIO_Regdef_t *)GPIOD_BA)
#define GPIOE   ((GPIO_Regdef_t *)GPIOE_BA)
#define GPIOF   ((GPIO_Regdef_t *)GPIOF_BA)
#define GPIOG   ((GPIO_Regdef_t *)GPIOG_BA)
#define GPIOH   ((GPIO_Regdef_t *)GPIOH_BA)
#define GPIOI   ((GPIO_Regdef_t *)GPIOI_BA)
#define GPIOJ   ((GPIO_Regdef_t *)GPIOJ_BA)
#define GPIOK   ((GPIO_Regdef_t *)GPIOK_BA)

#define RCC     ((RCC_Regdef_t *)RCC_BA)

#define EXTI    ((EXTI_Regdef_t *)EXTI_BA)

#define SYSCFG  ((SYSCFG_Regdef_t *)SYSCFG_BA)

#define SPI1    ((SPI_Regdef_t *)SPI1_BA)
#define SPI2    ((SPI_Regdef_t *)SPI2_BA)
#define SPI3    ((SPI_Regdef_t *)SPI3_BA)
#define SPI4    ((SPI_Regdef_t *)SPI4_BA)
#define SPI5    ((SPI_Regdef_t *)SPI5_BA)
#define SPI6    ((SPI_Regdef_t *)SPI6_BA)


//Generic macros
#define ENABLE  1
#define DISABLE 0
#define SET     ENABLE
#define RESET   DISABLE

#endif //_STM32F407XX_H_