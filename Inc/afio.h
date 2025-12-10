#ifndef AFIO_H
#define AFIO_H

#include "rcc.h"
#include "gpio.h"

typedef struct {
    volatile uint32_t EVCR, MAPR, EXT1CR1, EXT1CR2, EXT1CR3, EXT1CR4, MAPR2;
} AFIO_Typedef;

#define AFIO    ((AFIO_Typedef *) 0x40010000)

void afio_enable();
void afio_exti_config(GPIO_Typedef *port, uint8_t pinnumber);

#endif