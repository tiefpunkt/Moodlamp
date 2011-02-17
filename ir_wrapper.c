#include <avr/io.h>
#include <avr/interrupt.h>
#include "ir_wrapper.h"
#include "irmp.h"
#include "irmpconfig.h"
#include "control.h"

void ir_init() {
	// Init Timer
	OCR0A   =  (F_CPU / F_INTERRUPTS) - 1;                                    // compare value: 1/10000 of CPU frequency
	TCCR0B  = (1 << WGM02) | (1 << CS00);                                     // switch CTC Mode on, set prescaler to 1

	TIMSK1  = 1 << OCIE0A;                                                    // OCIE1A: Interrupt by timer compare
	
	irmp_init(); 
}

ISR(TIMER0_COMPA_vect)
{
  //(void) irmp_ISR();                                                        // call irmp ISR
  // call other timer interrupt routines...
}


void ir_handler() {
/*	IRMP_DATA irmp_data;
	
	if (irmp_get_data (&irmp_data)) {
		if ( irmp_data.protocol == 2 ) {
			switch ( irmp_data.command ) {
				case RC_RED:
					control_cmd = CTRL_CMD_SET_COLOR;
					control_param = CTRL_COLOR_RED;
					break;
				case RC_GREEN:
					control_cmd = CTRL_CMD_SET_COLOR;
					control_param = CTRL_COLOR_GREEN;
					break;
				case RC_BLUE:
					control_cmd = CTRL_CMD_SET_COLOR;
					control_param = CTRL_COLOR_BLUE;
					break;
				case RC_WHITE:
					control_cmd = CTRL_CMD_SET_COLOR;
					control_param = CTRL_COLOR_WHITE;
					break;
				case RC_RED4:
					control_cmd = CTRL_CMD_SET_COLOR;
					control_param = CTRL_COLOR_YELLOW;
					break;
				case RC_FADE:
					control_cmd = CTRL_CMD_RUN_FADING;
					break;
			}
		}
	}*/
}
