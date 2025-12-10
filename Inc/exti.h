#ifndef EXTI_H
#define EXTI_H

#include "rcc.h"
#include "gpio.h"
#include "nvic.h"

#define NVIC_IRQ_EXTI0  6U

typedef enum{
    RISING_EDGE,
    FALLING_EDGE
} interrupt_edge_t;

typedef struct {
    volatile uint32_t IMR, EMR, RTSR, FTSR, SWIER, PR;
} EXTI_Typedef;

#define EXTI ((EXTI_Typedef *) 0x40010400)

void exti_init(GPIO_Typedef *port, uint8_t pinnumber, interrupt_edge_t edge);

#endif