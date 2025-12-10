#include "spi.h"

/*SPI Driver Header
SPI1 as Master Pins
MOSI1   -> PA7      Alt Out Push Pull 50Mhz
MISO1   -> PA6      Floating Input
SCK1    -> PA5      Alt Out Push Pull 50Mhz
NSS(CS) -> PA4      GP Output 2Mhz

SPI Mode 0 (CPHA = 0, CPOL = 0)
8-bit data, MSB first, software NSS, blocking transfer
*/

void spi_init(SPI_Typedef* spi){
    if (spi == SPI1) {
        RCC->APB2ENR |= (1 << 12);      //Clock Enable SPI1
        RCC->APB2ENR |= (1 << 0);       //Clock Enable AFIO
        gpio_enable_port(GPIOA);        //Clock Enable GPIOA
        gpio_config_pin(GPIOA, 7, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_ALT_PUSH_PULL);
        gpio_config_pin(GPIOA, 6, GPIO_MODE_INPUT, GPIO_CNF_FLOATING_INPUT);
        gpio_config_pin(GPIOA, 5, GPIO_MODE_OUTPUT_50MHZ, GPIO_CNF_ALT_PUSH_PULL);
        gpio_config_pin(GPIOA, 4, GPIO_MODE_OUTPUT_2MHZ, GPIO_CNF_OUTPUT_PUSH_PULL);

        spi1_cs_disable();

        spi->CR1 &= ~(1 << 6);          //Disable SPI1
        spi->CR1 = 0;                   //Reset SPI1_CR
        spi->CR1 |=  (2 << 3);          //Set Baudrate -> Fpclk/8
        spi->CR1 |= (1 << 2);           //Set Master   
        spi->CR1 |= (3 << 8);           //Set Software Slave Management

        spi->CR1 |= (1 << 6);           //Enable SPI1
    }
}


uint8_t spi1_transfer(uint8_t data){
    while (!(SPI1->SR & (1 << 1)));         //Wait for Tx Buffer Empty

    SPI1->DR = data;                        //Set Tx Data on DR

    while (!(SPI1->SR & (1 << 0)));         //Wait for Rx Buffer Not Empty

    return (uint8_t)(SPI1->DR);             //Read Rx Data on DR
}

void spi1_transmit(const uint8_t *data, uint32_t len){
    while (len--){
        (void)spi1_transfer(*data++);
    }

    while (SPI1->SR & (1 << 7));
}

uint8_t spi1_receive(){
    return spi1_transfer(0xFF);
}