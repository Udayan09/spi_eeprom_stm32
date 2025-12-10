#include "afio.h"

void afio_enable(){
    RCC->APB2ENR |= (1 << 0);
}

void afio_exti_config(GPIO_Typedef *port, uint8_t pinnumber){
    //GPIO
    uint8_t gpio_number;
    if (port == GPIOA) gpio_number = 0;
    else if (port == GPIOB) gpio_number = 1;
    else if (port == GPIOC) gpio_number = 2;

    //EXTIi config
    if ((pinnumber >= 0) && (pinnumber < 4)){
        AFIO->EXT1CR1 &= ~(0xf << (pinnumber * 4));
        AFIO->EXT1CR1 |=  (gpio_number << (pinnumber * 4));
    }
    else if ((pinnumber >= 4) && (pinnumber < 8)){
        pinnumber -= 4;
        AFIO->EXT1CR1 &= ~(0xf << (pinnumber * 4));
        AFIO->EXT1CR1 |=  (gpio_number << (pinnumber * 4));
    }
    else if ((pinnumber >= 8) && (pinnumber < 12)){
        pinnumber -= 8;
        AFIO->EXT1CR1 &= ~(0xf << (pinnumber * 4));
        AFIO->EXT1CR1 |=  (gpio_number << (pinnumber * 4));
    }
    else if ((pinnumber >= 12) && (pinnumber < 16)){
        pinnumber -= 12;
        AFIO->EXT1CR1 &= ~(0xf << (pinnumber * 4));
        AFIO->EXT1CR1 |=  (gpio_number << (pinnumber * 4));
    }
}