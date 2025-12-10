#ifndef RCC_H
#define RCC_H

#include "stdint.h"

typedef struct
{
    volatile uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR, AHBENR, APB2ENR, APB1ENR, BDCR, CSR;
} RCC_Typedef;

#define RCC ((RCC_Typedef *) 0x40021000)	


#endif