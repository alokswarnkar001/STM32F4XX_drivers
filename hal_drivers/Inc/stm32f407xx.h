#ifndef _STM32F407XX_H_
#define _STM32F407XX_H_

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

#endif //_STM32F407XX_H_