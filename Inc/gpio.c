#include "gpio.h"
#include "rcc.h"



void gpio_enable_port(GPIO_Typedef* port){
    if      (port == GPIOA) RCC->APB2ENR |= (1 << 2);
    else if (port == GPIOB) RCC->APB2ENR |= (1 << 3);
    else if (port == GPIOC) RCC->APB2ENR |= (1 << 4);
}

void gpio_config_pin(GPIO_Typedef* port, uint8_t pinnumber, gpio_mode_t mode, gpio_cnf_t cnf){

    if (pinnumber < 8){
        port->CRL &= ~(0xF << (pinnumber * 4));
        port->CRL |= (mode << (pinnumber * 4));         //Set Pin Mode
        port->CRL |= (cnf << ((pinnumber * 4) + 2));    //Set Pin Config
    }
    else{
        pinnumber -= 8;
        port->CRH &= ~(0xF << (pinnumber * 4));
        port->CRH |= (mode << (pinnumber * 4));         //Set Pin Mode
        port->CRH |= (cnf << ((pinnumber * 4) + 2));    //Set Pin Config
    }
}
