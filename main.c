/**
*  RaumZeitLabor Moodlight 
*
**/

#include <avr/interrupt.h>

#include "config.h"
#include "pwm.h"
#include "ir_wrapper.h"
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
	ir_init();
	control_init();
	fe_init();
	
	sei();

#ifdef USART_DEBUG
	usart0_putc('I');
#endif

	while (1) {
		ir_handler();
		control_handler();
		pwm_handler();
		fe_handler();
	}
}

