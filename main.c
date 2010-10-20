/**
*  RaumZeitLabor Moodlight 
*
**/


//#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"

//#include "can/can.h"
//#include "can_handler.h"
//#include "can/spi.h"
//#include "can/lap.h"

#include "pwm.h"
//#include "static_scripts.h"
//#include "testscript.h"

#include "rc5.h"
#include "control.h"

void init(void)
{
//	ACSR = _BV(ACD); // Disable Analog Comparator (power save)

	//initialize spi port
//	spi_init();
	
	//initialize can communication
	//can_init();
	//read_can_addr();
	//turn on interrupts
	init_pwm();
	rc5_init();
	control_init();
	sei();
}


int main(void)
{
	init();
	
	
	

//	control_cmd = CTRL_CMD_RUN_FADING;

	while (1)
	{
	//	can_handler();
		rc5_handler();
		control_handler();
		pwm_handler();
	}
}

