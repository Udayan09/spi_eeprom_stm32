#include "exti.h"

void exti_init(GPIO_Typedef *port, uint8_t pinnumber, interrupt_edge_t edge){
    if (port == GPIOA)      gpio_enable_port(GPIOA);
    else if (port == GPIOB) gpio_enable_port(GPIOB);
    else                    gpio_enable_port(GPIOC);

    gpio_config_pin(port, pinnumber, GPIO_MODE_INPUT, GPIO_CNF_FLOATING_INPUT);

    
}