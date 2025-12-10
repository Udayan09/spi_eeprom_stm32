#include "timer.h"

#define TIM_CLOCK_HZ   72000000UL
#define TIM_PSC_1MHZ   (TIM_CLOCK_HZ / 1000000 - 1UL)     

void tim2_init(){

    RCC->APB1ENR |= (1 << 0);    //Enable Timer2 Peripheral

    TIM2->CR1 &= ~(1 << 0);        //Counter Disabled
    TIM2->PSC = TIM_PSC_1MHZ;     //Set prescaler value
    TIM2->ARR = 0xFFFF;            //Set ARR to max value 
    TIM2->EGR |= (1 << 0);         //Updates all registers
}

void delay_us(uint16_t us){         //Uses TIM2
    TIM2->ARR = us;

    TIM2->CNT = 0;              //Reset Counter

    TIM2->SR &= ~(1 << 0);      //Clear Update interr flag

    TIM2->CR1 |= (1 << 0);      //Enable Counter

    while((TIM2->SR & (1 << 0)) == 0);  //Wait till counter reaches ARR

    TIM2->CR1 &= ~(1U << 0);    //Disable counter
}

void delay_ms(uint32_t ms){
    while (ms--) {
        delay_us(1000);         // 1000 us = 1 ms
    }
}

void tim1_pwm_init(){

    //GPIO Init
    gpio_enable_port(GPIOA);
    gpio_config_pin(GPIOA, 8, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_ALT_PUSH_PULL);

    //Timer Init
    RCC->APB2ENR |= (1 << 11);      //Timer1 Clock Enable

    TIM1->CR1 &= ~(1 << 0);         //Disable Tim1

    TIM1->PSC = TIM_PSC_1MHZ;       //Set prescaler

    TIM1->ARR = 999;                //1Khz Frequency PWM

    TIM1->CCMR1 &= ~(3 << 0);       //Set CC1 as output
    TIM1->CCMR1 |= (1 << 3);        //Auto Preload enable
    TIM1->CCMR1 |= (0x6 << 4);      //Set output comp mode > Pwm Mode1

    TIM1->CCER &= ~(1 << 1);        //Active High
    TIM1->CCER |= (1 << 0);         //Output Enabled

    TIM1->CCR1 = 0;                 //Initial Duty Cycle

    TIM1->CR1 |= (1 << 7);          //Enable ARR Preload

    TIM1->BTDR |= (1 << 15);        //Main output enabled

    TIM1->EGR |= (1 << 0);          //Update Generation

    TIM1->CR1 |= (1 << 0);          //Enable counter
}

void tim1_pwm_set_duty(uint8_t duty_cycle){
    if (duty_cycle > 100) duty_cycle = 100;

    uint32_t arr = TIM1->ARR;
    uint32_t ccr = ((arr + 1) * duty_cycle) / 100;
    TIM1->CCR1 = ccr;
    
}

