#include "eeprom.h"

#define EEPROM_READ_CMD 0x03
#define EEPROM_WRITE_CMD 0x02

void eeprom_enable_write(){
    spi1_cs_enable();
    spi1_transfer(0x06);
    spi1_cs_disable();
}

void eeprom_write(uint8_t data_byte, uint16_t address){
    uint8_t addr_high = (address >> 8) & 0xff;
    uint8_t addr_low = (address) & 0xff;
    uint8_t dataArray[] = {0x02, addr_high, addr_low, data_byte};

    eeprom_enable_write();

    spi1_cs_enable();
    spi1_transmit(dataArray, 4);
    spi1_cs_disable();
}

void eeprom_multi_write(uint8_t *data_array, uint8_t data_len, uint16_t address){
    uint8_t addr_high = (address >> 8) & 0xff;
    uint8_t addr_low = (address) & 0xff;
    uint8_t byte_count = data_len + 3;
    uint8_t Txdata[byte_count];
    Txdata[0] = 0x02;
    Txdata[1] = addr_high;
    Txdata[2] = addr_low;
    for (uint8_t i = 3; i < byte_count; i++){
        Txdata[i] = data_array[i - 3];
    }

    eeprom_enable_write();
    spi1_cs_enable();
    spi1_transmit(Txdata, byte_count);
    spi1_cs_disable();
}

uint8_t eeprom_read(uint16_t address){
    uint8_t addr_high = (address >> 8) & 0xff;
    uint8_t addr_low = (address) & 0xff;
    uint8_t dataArray[] = {0x03, addr_high, addr_low};
    uint8_t data_rx;

    spi1_cs_enable();
    spi1_transmit(dataArray, 3);
    data_rx = spi1_receive();
    spi1_cs_disable();
}

