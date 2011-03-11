#include "fadingengine.h"
#include "pwm.h"
#include "control.h"

#include <stdlib.h>
#include <util/delay.h>

uint8_t fe_pos;

void fe_init() {
    srand(2342);
    fe_speed = 0x40;
    fe_mode = FADING_MODE_DISABLED;
}

void fe_start() {
    if (fe_mode == FADING_MODE_DISABLED) {
		fe_mode = FADING_MODE_DEFAULT;
	}
	
	if (fe_mode == FADING_MODE_FADE)  {
		//control_setColorRGB(0xff, 0x00, 0x00);
		control_setColorRGB(0x00, 0x00, 0x00);
		fe_pos = 0;
	} else if (fe_mode == FADING_MODE_SMOOTH) {
		control_setColorRGB(0xff, 0xff, 0xff);
	} else if (fe_mode == FADING_MODE_STROBE) {
		fe_pos = 0;
	}
}

void fe_handler() {
    if (fe_mode == FADING_MODE_DISABLED) return;

	if (fe_mode == FADING_MODE_SMOOTH) {
		if (fe_channels_finished(_BV(CHANNEL_RED)|_BV(CHANNEL_GREEN)|_BV(CHANNEL_BLUE))) {
		/* slow random fading... */
			fe_fade_channel(CHANNEL_GREEN, rand() / (RAND_MAX / 255 + 1), fe_speed);
			fe_fade_channel(CHANNEL_RED,   rand() / (RAND_MAX / 255 + 1), fe_speed);
			fe_fade_channel(CHANNEL_BLUE,  rand() / (RAND_MAX / 255 + 1), fe_speed);
		}
	} else if (fe_mode == FADING_MODE_FADE) {
/*		if (fe_channels_finished(_BV(CHANNEL_RED)|_BV(CHANNEL_GREEN)|_BV(CHANNEL_BLUE))) {
			if (fe_pos == 0) {
				fe_fade_channel(CHANNEL_RED, 0, fe_speed);
				fe_fade_channel(CHANNEL_GREEN, 255, fe_speed);
			} else if (fe_pos == 1) {
				fe_fade_channel(CHANNEL_GREEN, 0, fe_speed);
				fe_fade_channel(CHANNEL_BLUE, 255, fe_speed);
			} else if (fe_pos == 2) {
				fe_fade_channel(CHANNEL_BLUE, 0, fe_speed);
				fe_fade_channel(CHANNEL_RED, 255, fe_speed);
			}

			fe_pos++;
			if (fe_pos > 2) fe_pos = 0;
		}*/
		if (fe_channels_finished(_BV(CHANNEL_RED)|_BV(CHANNEL_GREEN)|_BV(CHANNEL_BLUE))) {
			if (fe_pos == 0) {
				fe_fade_channel(CHANNEL_GREEN, rand() / (RAND_MAX / 255 + 1), fe_speed);
				fe_fade_channel(CHANNEL_RED,   rand() / (RAND_MAX / 255 + 1), fe_speed);
				fe_fade_channel(CHANNEL_BLUE,  rand() / (RAND_MAX / 255 + 1), fe_speed);
			} else if (fe_pos == 1) {
				fe_fade_channel(CHANNEL_GREEN, 0, fe_speed);
				fe_fade_channel(CHANNEL_BLUE, 0, fe_speed);
				fe_fade_channel(CHANNEL_RED, 0, fe_speed);
			}
			fe_pos = 1 - fe_pos;
		}
	} else if (fe_mode == FADING_MODE_STROBE) {
		if (fe_pos == 0) {
			global_pwm.channels[CHANNEL_RED].brightness = rand() / (RAND_MAX / 255 + 1);
			global_pwm.channels[CHANNEL_GREEN].brightness = rand() / (RAND_MAX / 255 + 1);
			global_pwm.channels[CHANNEL_BLUE].brightness = rand() / (RAND_MAX / 255 + 1);
		} else if (fe_pos == 128) {
			global_pwm.channels[CHANNEL_RED].brightness = 0;
			global_pwm.channels[CHANNEL_GREEN].brightness = 0;
			global_pwm.channels[CHANNEL_BLUE].brightness = 0;
		}
		fe_pos += 1;
	} else if (fe_mode == FADING_MODE_FLASH) {
		if (fe_pos == 0) {
			global_pwm.channels[CHANNEL_RED].brightness = 255;
			global_pwm.channels[CHANNEL_GREEN].brightness = 255;
			global_pwm.channels[CHANNEL_BLUE].brightness = 255;
		} else if (fe_pos == 128) {
			control_setColorRGB(0x00, 0x00, 0x00);
		} 
		if (fe_pos == 129) {
			if (fe_channels_finished(_BV(CHANNEL_RED)|_BV(CHANNEL_GREEN)|_BV(CHANNEL_BLUE))) {
				fe_pos++;
			}
		} else {
			fe_pos++;
		}
	}
}

void fe_fade_channel(uint8_t channel, uint8_t target, uint16_t speed) {
    global_pwm.channels[channel].target_brightness = target;
    global_pwm.channels[channel].speed_l = LOW(speed);
    global_pwm.channels[channel].speed_h = HIGH(speed);
}

uint8_t fe_channels_finished(uint8_t channels) {
    uint8_t target_mask = 0;
    uint8_t i;

    /* check for channels which reached their targets */
    for (i=0; i<PWM_CHANNELS; i++) {
        if (global_pwm.channels[i].flags.target_reached) {
            //target_mask |= global_pwm.channels[i].mask;
            target_mask |= _BV(i);
            global_pwm.channels[i].flags.target_reached = 0;
        }
    }
	
    return (target_mask & channels);
}
