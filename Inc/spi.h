#ifndef SPI_H
#define SPI_H

#include "rcc.h"
#include "gpio.h"

/*SPI Driver Header
SPI1 as Master Pins
MOSI1   -> PA7
MISO1   -> PA6
SCK1    -> PA5
NSS(CS) -> PA4

SPI Mode 0 (CPHA = 0, CPOL = 0)
8-bit data, MSB first, software NSS, blocking transfer
*/

#define SPI1_GPIO       GPIOA
#define SPI1_CS_PIN     4

typedef struct {
    volatile uint32_t CR1, CR2, SR, DR, CRCPR, RXCRCR, TXCRCR, I2SCFGR, I2SPR;
} SPI_Typedef;

#define SPI1    ((SPI_Typedef *) 0x40013000)
#define SPI2    ((SPI_Typedef *) 0x40003800)

static inline void spi1_cs_disable(){
    gpio_set_pin(GPIOA, 4);
}

static inline void spi1_cs_enable(){
    gpio_reset_pin(GPIOA, 4);
}

void spi_init(SPI_Typedef* spi);

uint8_t spi1_transfer(uint8_t data);

void spi1_transmit(const uint8_t *data, uint32_t len);

uint8_t spi1_receive();

#endif