#include <avr/io.h>
#include "control.h"
#include "pwm.h"
#include "static_scripts.h"

void control_handler(void) {
	if (control_cmd != CTRL_CMD_NONE) {
		switch (control_cmd) {
			case CTRL_CMD_SET_COLOR:
				control_setColor(control_param);
				break;
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

void control_setColor(uint8_t color) {
	switch (color) {
		case CTRL_COLOR_RED:
			control_setColorRGB(0xff, 0x00, 0x00);
			break;
		case CTRL_COLOR_GREEN:
			control_setColorRGB(0x00, 0xff, 0x00);
			break;
		case CTRL_COLOR_BLUE:
			control_setColorRGB(0x00, 0x00, 0xff);
			break;
	}			
}

void control_setColorRGB(uint8_t red, uint8_t green, uint8_t blue) {
	script_threads[0].flags.disabled = 1;
	global_pwm.channels[CHANNEL_RED].brightness = red;
	global_pwm.channels[CHANNEL_RED].target_brightness = red;
	global_pwm.channels[CHANNEL_GREEN].brightness = green;
	global_pwm.channels[CHANNEL_GREEN].target_brightness = green;
	global_pwm.channels[CHANNEL_BLUE].brightness = blue;
	global_pwm.channels[CHANNEL_BLUE].target_brightness = blue;
}
