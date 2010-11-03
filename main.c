/**
*  RaumZeitLabor Moodlight 
*
**/

//#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"
#include "pwm.h"
#include "rc5.h"
#include "control.h"
#include "fadingengine.h"
#include "usart.h"

//#include "static_scripts.h"
//#include "testscript.h"



int main(void)
{
//	ACSR = _BV(ACD); // Disable Analog Comparator (power save)
	usart0_init();
	init_pwm();
	rc5_init();
	control_init();
	sei();	
	fe_init();

	usart0_putc('I');

//	control_cmd = CTRL_CMD_RUN_FADING;

	while (1)
	{
	//	can_handler();
		rc5_handler();
		control_handler();
		pwm_handler();
		fe_handler();
	}
}

