#include <avr/io.h>

#define FADING_MODE_SMOOTH		1
#define FADING_MODE_FADE		2
#define FADING_MODE_FLASH		3
#define FADING_MODE_STROBE		4
#define FADING_MODE_DISABLED	5

#define FADING_MODE_DEFAULT		FADING_MODE_SMOOTH

uint8_t fe_mode;
uint16_t fe_speed;

void fe_init();
void fe_start();
void fe_handler();
void fe_fade_channel(uint8_t channel, uint8_t target, uint16_t speed);
uint8_t fe_channels_finished(uint8_t channels);
