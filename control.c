#include <avr/io.h>
#include "control.h"
#include "pwm.h"

void control_handler(void) {
	if (control_cmd != CTRL_CMD_NONE) {
		switch (control_cmd) {
			case CTRL_CMD_PAUSE_TOGGLE:
				global.flags.paused = (1 - global.flags.paused);
				break;
			case CTRL_CMD_PAUSE_ON:
				global.flags.paused = 1;
				break;
			case CTRL_CMD_PAUSE_OFF:
				global.flags.paused = 1;
				break;
		}
		
		control_cmd = CTRL_CMD_NONE;
	}
};