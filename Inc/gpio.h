#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>


typedef struct {
    volatile uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
} GPIO_Typedef;

typedef enum {
    GPIO_MODE_INPUT, 
    GPIO_MODE_OUTPUT_10MHZ, 
    GPIO_MODE_OUTPUT_2MHZ, 
    GPIO_MODE_OUTPUT_50MHZ
} gpio_mode_t;

typedef enum {
    GPIO_CNF_ANALOG              = 0x0, 
    GPIO_CNF_FLOATING_INPUT      = 0x1, 
    GPIO_CNF_INPUT_PULL_UP_DOWN  = 0x2, 
    GPIO_CNF_OUTPUT_PUSH_PULL    = 0x0, 
    GPIO_CNF_OUTPUT_OPEN_DRAIN   = 0x1, 
    GPIO_CNF_ALT_PUSH_PULL       = 0x2, 
    GPIO_CNF_ALT_OPEN_DRAIN      = 0x3
} gpio_cnf_t;

#define GPIOA	((GPIO_Typedef *) 0x40010800)
#define GPIOB	((GPIO_Typedef *) 0x40010C00)
#define GPIOC	((GPIO_Typedef *) 0x40011000)

static inline void gpio_set_pin(GPIO_Typedef* port, uint8_t pinnumber){
    port->BSRR |= (1 << (pinnumber));
}

static inline void gpio_reset_pin(GPIO_Typedef* port, uint8_t pinnumber){
    port->BSRR |= (1 << (pinnumber + 16));
}

static inline void gpio_toggle_pin(GPIO_Typedef* port, uint8_t pinnumber){
    port->ODR ^= (1 << (pinnumber));
}

static inline uint8_t gpio_get_pin(GPIO_Typedef* port, uint8_t pinnumber){
    return (uint8_t)((port->IDR >> pinnumber) & 0x1);
}



void gpio_enable_port(GPIO_Typedef* port);
void gpio_config_pin(GPIO_Typedef* port, uint8_t pinnumber, gpio_mode_t mode, gpio_cnf_t cnf);


#endif

