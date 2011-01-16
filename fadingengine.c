#include "fadingengine.h"
#include "pwm.h"
#include "control.h"

uint8_t fe_pos;

void fe_init() {
    control_setColorRGB(0xff, 0x00, 0x00);
    fe_disabled = 0;
    fe_pos = 0;
}

void fe_handler() {
    if (fe_disabled) return;

    if (fe_channels_finished(_BV(CHANNEL_RED)|_BV(CHANNEL_GREEN)|_BV(CHANNEL_BLUE))) {
        if (fe_pos == 0) {
            fe_fade_channel(CHANNEL_RED, 0, 0x040);
	    fe_fade_channel(CHANNEL_GREEN, 255, 0x040);
        } else if (fe_pos == 1) {
            fe_fade_channel(CHANNEL_GREEN, 0, 0x040);
	    fe_fade_channel(CHANNEL_BLUE, 255, 0x040);
        } else if (fe_pos == 2) {
            fe_fade_channel(CHANNEL_BLUE, 0, 0x040);
	    fe_fade_channel(CHANNEL_RED, 255, 0x040);
	}

        fe_pos++;
        if (fe_pos > 2) fe_pos = 0;
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
