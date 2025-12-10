#ifndef TIMER_H
#define TIMER_H

#include "rcc.h"
#include "gpio.h"

typedef struct {
    volatile uint32_t CR1, CR2, SMCR, DIER, SR, EGR, CCMR1, CCMR2, CCER, CNT, PSC, ARR, RCR, CCR1, CCR2, CCR3, CCR4, BTDR, DCR, DMAR;
} gp_timer_Typedef;

#define TIM1 ((gp_timer_Typedef* ) 0x40012C00)
#define TIM2 ((gp_timer_Typedef* ) 0x40000000)

typedef enum{
    COUNTER,
    PWM
} timer_modes_t;


void tim2_init();
void delay_us(uint16_t us);
void delay_ms(uint32_t ms);

void tim1_pwm_init();
void tim1_pwm_set_duty(uint8_t duty_cycle);

#endif