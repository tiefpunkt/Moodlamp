#include <avr/io.h>

uint8_t fe_disabled;

void fe_init();
void fe_handler();
void fe_fade_channel(uint8_t channel, uint8_t target, uint16_t speed);
uint8_t fe_channels_finished(uint8_t channels);
