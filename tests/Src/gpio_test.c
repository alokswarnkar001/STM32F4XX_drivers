#include "gpio.h"
#include "rcc.h"

#define EXTI0_IRQNO     6

static void gpio_led_toggling_test(void) {
    GPIO_Handle_t handle_led;
    GPIO_Handle_t handle_btn;

    //Configure Green LED at Port D - 12th Pin
    handle_led.pGPIOx = GPIOD;
    handle_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    handle_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    handle_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    handle_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    handle_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    handle_led.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF0;

    //Configure User button at Port A - 0th Pin
    handle_btn.pGPIOx = GPIOA;
    handle_btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    handle_btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    handle_btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    handle_btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    handle_btn.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF0;

    GPIO_Init(&handle_led);
    GPIO_Init(&handle_btn);

    for(uint8_t i=0; i<=10; i++) 
    {
        while(!(GPIO_ReadFromInputPin(handle_btn.pGPIOx,handle_btn.GPIO_PinConfig.GPIO_PinNumber) & 0x01));
        for(int i =0; i<=1000000; i++);
        GPIO_ToggleOutputPin(handle_led.pGPIOx, handle_led.GPIO_PinConfig.GPIO_PinNumber);
    }

    GPIO_DeInit(&handle_led);
    GPIO_DeInit(&handle_btn);

}

GPIO_Handle_t handle_led;
GPIO_Handle_t handle_btn;
static void gpio_led_toggling_intr_test(void) {
    
    //Configure Green LED at Port D - 12th Pin
    handle_led.pGPIOx = GPIOD;
    handle_led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    handle_led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    handle_led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    handle_led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    handle_led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    handle_led.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF0;

    //Configure User button at Port A - 0th Pin
    handle_btn.pGPIOx = GPIOA;
    handle_btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
    handle_btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    handle_btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
    handle_btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    handle_btn.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF0;

    GPIO_Init(&handle_led);
    GPIO_Init(&handle_btn);

    GPIO_IRQConfig(&handle_btn,GPIO_MODE_IT_FE,EXTI0_IRQNO,0x02,ENABLE);
}

void gpio_tests(void) {
    //gpio_led_toggling_test();
    gpio_led_toggling_intr_test();
}

void EXTI0_IRQHandler(void) {
    GPIO_IRQHandling(handle_btn.GPIO_PinConfig.GPIO_PinNumber);
    GPIO_ToggleOutputPin(handle_led.pGPIOx, handle_led.GPIO_PinConfig.GPIO_PinNumber);
}