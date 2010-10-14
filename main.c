#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"


//#include "can/can.h"
//#include "can_handler.h"
//#include "can/spi.h"
//#include "can/lap.h"

#include "pwm.h"
#include "static_scripts.h"
#include "testscript.h"

#include "rc5.h"


void init(void)
{
	ACSR = _BV(ACD); // Disable Analog Comparator (power save)

	//initialize spi port
//	spi_init();
	
	//initialize can communication
	//can_init();
	//read_can_addr();
	//turn on interrupts
	init_pwm();
	rc5_init();
	sei();
}


int main(void)
{
	init();
	
	
	init_script_threads();
	script_threads[0].handler.execute = &memory_handler_eeprom;
	script_threads[0].handler.position = (uint16_t) &colorchange_red;
	script_threads[0].flags.disabled = 0;

	while (1)
	{
	//	can_handler();
		rc5_handler();
		pwm_handler();
	}
}

