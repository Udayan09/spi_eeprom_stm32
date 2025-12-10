#include <stdint.h>
#include "gpio.h"
#include "timer.h"

int main(void)
{	
	gpio_enable_port(GPIOC);
	gpio_config_pin(GPIOC, 13, GPIO_MODE_OUTPUT_10MHZ, GPIO_CNF_OUTPUT_PUSH_PULL);

	tim2_init(TIM2, COUNTER);
	tim1_pwm_init();

	uint8_t duty = 50;
	uint8_t dir = 0;
	for(;;){
		
		if (dir == 0) duty += 10;
		else duty -= 10;

		if (duty == 100) dir = 1;
		else if (duty == 0) dir = 0;

		tim1_pwm_set_duty(duty);
		gpio_toggle_pin(GPIOC, 13);
		delay_ms(100);
	}
}
