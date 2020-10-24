# RaumZeitLabor Moodlamp
AVR ATmega328p based RGB lamp, which can be controlled by IR remote controls.

## Inspiration
* PWM-coding from [Labor Licht](http://das-labor.org/wiki/Labor_Licht) project by [Das Labor](http://das-labor.org/)
* [IRMP library](http://www.mikrocontroller.net/articles/IRMP) for remote controls with patch to run on an 8bit timer
* USART library from [this library](http://www.wiki.elektronik-projekt.de/mikrocontroller/avr/avr-gcc-library/start)

## Flashing the binary
We maintain a binary version of the code, since some people don't have an appropiriate toolchain for avr. You can find it on the GitHub page under [Downloads]section or by using this link (https://github.com/tiefpunkt/Moodlamp/archives/master). It could be that the binary is a bit out of date; if you want an up-to-date binary, please build it yourself.

In order to flash the binary, you need to have avrdude installed. Call it with:

	avrdude -c usbasp -p atmega328p -U flash:w:image.hex -U eeprom:w:image_eeprom.hex

## Website
For more information, visit [http://raumzeitlabor.de/wiki/Moodlamp](http://raumzeitlabor.de/wiki/Moodlamp).
