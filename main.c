/**
*  RaumZeitLabor Moodlight 
*
**/

#include <avr/interrupt.h>

#include "config.h"
#include "pwm.h"
#include "rc5.h"
#include "control.h"
#include "fadingengine.h"

#ifdef USART_DEBUG
#include "usart.h"
#endif

int main(void) {

#ifdef USART_DEBUG
	usart0_init();
#endif

	init_pwm();
	rc5_init();
	control_init();
	sei();	
	fe_init();

#ifdef USART_DEBUG
	usart0_putc('I');
#endif

	while (1) {
		rc5_handler();
		control_handler();
		pwm_handler();
		fe_handler();
	}
}

