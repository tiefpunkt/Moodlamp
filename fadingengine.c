/**
* RaumZeitLabor Moodlight 
* http://raumzeitlabor.de/wiki/Moodlamp
*
* fadingengine.c - Fading Engine with 4 different modes
**/

#include "fadingengine.h"
#include "pwm.h"
#include "control.h"
#include "config.h"
#include "usart.h"
#include <stdio.h>
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

int fe_create_random_channel_target () {
	int value;

	/* We only generate a simple random value for now.
	 * Later we can extend this to have minimum or maximum values.
	 */
	value = rand() / (RAND_MAX / 255 + 1);

	return value;

}
void fe_handler() {
	uint8_t red, green, blue;

    if (fe_mode == FADING_MODE_DISABLED) return;

	if (fe_mode == FADING_MODE_SMOOTH) {
		if (fe_channels_finished(_BV(CHANNEL_RED)|_BV(CHANNEL_GREEN)|_BV(CHANNEL_BLUE))) {
		/* slow random fading... */
			red = fe_create_random_channel_target();
			green = fe_create_random_channel_target();
			blue = fe_create_random_channel_target();

#ifdef USART_DEBUG
		sprintf(msgbuf, "Activating new FADING_MODE_SMOOTH target with RGB(%d, %d, %d)\n\r", red, green, blue);
		usart0_puts(msgbuf);
#endif

			fe_fade_channel(CHANNEL_GREEN, green	, fe_speed);
			fe_fade_channel(CHANNEL_RED,   red		, fe_speed);
			fe_fade_channel(CHANNEL_BLUE,  blue		, fe_speed);
		}
	} else if (fe_mode == FADING_MODE_FADE) {
		/**
		 * For FADING_MODE_FADE, fe_pos is either 0 or 1.
		 *
		 * If fe_pos is 0, we fade to a random generated color.
		 * If fe_pos is 1, we fade back to RGB(0,0,0)
		 */

		/* Check if the fade is finished. If yes, create new fade target */
		if (fe_channels_finished(_BV(CHANNEL_RED)|_BV(CHANNEL_GREEN)|_BV(CHANNEL_BLUE))) {
			if (fe_pos == 0) {

				/* Create random color */
				red = fe_create_random_channel_target();
				green = fe_create_random_channel_target();
				blue = fe_create_random_channel_target();

#ifdef USART_DEBUG
				sprintf(msgbuf, "Activating new FADING_MODE_FADE target with RGB(%d, %d, %d)\n\r", red, green, blue);
				usart0_puts(msgbuf);
#endif

				fe_fade_channel(CHANNEL_GREEN, 	green	, fe_speed);
				fe_fade_channel(CHANNEL_BLUE, 	blue	, fe_speed);
				fe_fade_channel(CHANNEL_RED, 	red		, fe_speed);

			} else if (fe_pos == 1) {
				/* Fade back to off */
#ifdef USART_DEBUG
				usart0_puts("Activating new FADING_MODE_FADE target with channels OFF\n\r");
#endif
				fe_fade_channel(CHANNEL_GREEN, 0, fe_speed);
				fe_fade_channel(CHANNEL_BLUE, 0, fe_speed);
				fe_fade_channel(CHANNEL_RED, 0, fe_speed);
			} else {
				/* Sanity: If fe_pos is neither 0 or 1 in FADING_MODE_FADE, set it to 0. */
#ifdef USART_DEBUG
				usart0_puts("Would have failed NOW\n\r");
#endif

				fe_pos = 0;
			}

			fe_pos = 1 - fe_pos;
		}
	} else if (fe_mode == FADING_MODE_STROBE) {
		if (fe_pos == 0) {
			global_pwm.channels[CHANNEL_RED].brightness = fe_create_random_channel_target();
			global_pwm.channels[CHANNEL_GREEN].brightness = fe_create_random_channel_target();
			global_pwm.channels[CHANNEL_BLUE].brightness = rand() / fe_create_random_channel_target();
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
