#include <stdint.h>
#include "gpio.h"
#include "timer.h"
#include "spi.h"
#include "eeprom.h"


static uint8_t txDataArray[] = {1, 2, 3, 4, 5};

int main(void)
{	
	gpio_enable_port(GPIOC);
	gpio_config_pin(GPIOC, 13, GPIO_MODE_OUTPUT_10MHZ, GPIO_CNF_OUTPUT_PUSH_PULL);

	tim2_init(TIM2, COUNTER);

	spi_init(SPI1);

	
	
	for(;;){
		
		eeprom_multi_write(txDataArray, 5, 0);
		
		delay_ms(10);

		for (uint8_t i = 0;i < 5; i++){
			eeprom_read(i);
			delay_us(100);
		}
		
		delay_ms(1000);
	}
}
